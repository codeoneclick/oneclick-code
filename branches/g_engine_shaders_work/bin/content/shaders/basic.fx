float4x4 mWorldViewProjection;
float4x4 mWorld;

float3 vCameraEye;
float3 vLightDir;

float fAmbientFactor = 0.75f;

float4 vSpecularColor = float4(1.0f,1.0f,1.0f,1.0f);

float fSpecularPower = 16.0f;

float fOceanLevel = 12.0f;

float fRimStart = 0.8f;
float fRimEnd = 1.0f;

float fRimFactor = 1.33f;

float4 vRimColor = float4(0.5f,0.5f,0.0f,1.0f);

texture Texture_01;
sampler Texture_01_Sampler = sampler_state {
	Texture = <Texture_01>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_02;
sampler Texture_02_Sampler = sampler_state {
	Texture = <Texture_02>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_03;
sampler Texture_03_Sampler = sampler_state {
	Texture = <Texture_03>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_01_NH;
sampler Texture_01_NH_Sampler = sampler_state {
	Texture = <Texture_01_NH>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_02_NH;
sampler Texture_02_NH_Sampler = sampler_state {
	Texture = <Texture_02_NH>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture Texture_03_NH;
sampler Texture_03_NH_Sampler = sampler_state {
	Texture = <Texture_03_NH>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
	float4 vNormal		  : TEXCOORD1;
	float4 vTangent		  : TEXCOORD2;
	float4 vSplatting     : COLOR0;
};

struct VS_OUTPUT 
{
   float4 vPosition		   : POSITION;
   float4 vSplatting       : COLOR0;
   float2 vTexCoord	       : TEXCOORD0;
   float3 vNormal          : TEXCOORD1;
   float3 vTangent		   : TEXCOORD2;
   float3 vBinormal		   : TEXCOORD3;
   float3 vwPosition	   : TEXCOORD4;
};

VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vSplatting = IN.vSplatting;
   
   float3 vTangent = IN.vTangent;
   float3 vNormal = IN.vNormal;
   float3 vBinormal = cross( vTangent, vNormal );
   
   OUT.vTangent = vTangent;
   OUT.vNormal = vNormal;
   OUT.vBinormal = vBinormal;
   
   OUT.vwPosition = mul( float4( IN.vPosition, 1.0f ), mWorld ).xyz;
   
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	float3x3 mTangentSpace = float3x3( IN.vTangent, IN.vBinormal, IN.vNormal );
	
	float3 vEyeTS = mul( mTangentSpace, normalize( vCameraEye - IN.vwPosition ) ); 
	float3 vEyeWS = normalize( vCameraEye - IN.vwPosition );
	float3 vLightTS = normalize( mul( mTangentSpace, vLightDir ) );
   
    float4 vReliefTexture = tex2D( Texture_01_NH_Sampler, IN.vTexCoord ) * IN.vSplatting.x + 
							tex2D( Texture_02_NH_Sampler, IN.vTexCoord ) * IN.vSplatting.y + 
							tex2D( Texture_03_NH_Sampler, IN.vTexCoord ) * IN.vSplatting.z;
   
    float fHeight = vReliefTexture.w * 0.06f - 0.03f;
	float2 vDisTexCoord = IN.vTexCoord - vEyeTS.xy * fHeight;
	
	float3 vNormalColor = vReliefTexture.xyz * 2.0f - 1.0f;
	vNormalColor = normalize( vNormalColor );
	
	float4 vDiffuseColor = tex2D( Texture_01_Sampler, vDisTexCoord ) * IN.vSplatting.x + 
						   tex2D( Texture_02_Sampler, vDisTexCoord ) * IN.vSplatting.y + 
						   tex2D( Texture_03_Sampler, vDisTexCoord ) * IN.vSplatting.z;
	
	float4 vAmbientColor = vDiffuseColor;						
	
	float vDiffuseFactor = saturate( dot ( vNormalColor, vLightTS ) * 0.5f + 0.5f);
    
	float3 vLightReflect = reflect( vLightTS, vNormalColor );
	float vSpecularFactor = pow( max( 0.0f, dot( vLightReflect, vEyeTS ) ), fSpecularPower );
	
	float fRimPower = smoothstep( fRimStart , fRimEnd , 1.0f - dot( IN.vNormal , vEyeWS ) );
	
    float4 vColor = vDiffuseColor * vDiffuseFactor + /*vSpecularFactor * vSpecularColor + */ fRimPower * vDiffuseColor * fRimFactor;
    vColor.a = IN.vwPosition.y / fOceanLevel;
	//vColor.rgb = IN.vNormal;
    return vColor;
}

technique main 
{
	pass p0 
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0  ps_main();
	}
}