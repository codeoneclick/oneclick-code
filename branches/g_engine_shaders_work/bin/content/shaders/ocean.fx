float4x4 mWorldViewProjection;
float4x4 mWorld;
float fTimer;
float fDarkEffect = 0.77f;
float fSpecularFactor = 128.0f;
float fTileFactor = 32.0f;
float fFogStart = 256.0f;
float fFogEnd = 512.0f;
float4 vDeepColor = { 0.05f, 0.15f, 0.20f, 1.0f };
float3 vOceanCenter = { 128.0f, 0.0f, 128.0f };
float3 vLuminanceColor = { 0.27f, 0.67f, 0.06f };

float3 vCameraEye;
float3 vLightDir;
float3 vFogColor;

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

struct VS_INPUT 
{
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
   float4 vTexCoordProj    : TEXCOORD1;
   float3 vWorldPosition   : TEXCOORD2;
   float3x3 mTangentSpace  : TEXCOORD3;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vTexCoordProj = OUT.vPosition;
   
   OUT.vWorldPosition = mul(float4(IN.vPosition,1.0f), mWorld).xyz;
   
   float3 vBinormal = float3( 1.0f,  0.0f, 0.0f );
   float3 vTangent  = float3( 0.0f,  0.0f, 1.0f );
   float3 vNormal   = float3( 0.0f,  1.0f, 0.0f );
   
   float3x3 mTangentSpace = float3x3(vTangent,vBinormal,vNormal);
   OUT.mTangentSpace = mTangentSpace;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	float3 vLightDirPix = normalize(mul(IN.mTangentSpace,vLightDir));
	float3 vCameraEyePix = normalize(mul(IN.mTangentSpace,vCameraEye - IN.vWorldPosition));

	IN.vTexCoord *= fTileFactor;
	float2 vTexCoord_01 = float2(IN.vTexCoord.x + sin(fTimer)*0.07f,
								 IN.vTexCoord.y - cos(fTimer)*0.09f);
	
	float2 vTexCoord_02 = float2(IN.vTexCoord.x - sin(fTimer)*0.09f,
								 IN.vTexCoord.y + cos(fTimer)*0.07f);

    float3 vNormalColor = normalize((tex2D( Texture_01_Sampler, vTexCoord_01 ) * 2.0f - 1.0f ) + 
								    (tex2D( Texture_01_Sampler, vTexCoord_02 ) * 2.0f - 1.0f ));
						  
	float3 vNormalColorWS = vNormalColor;					  
						  
	vNormalColor = normalize(mul(IN.mTangentSpace, vNormalColor));
	
    float2 vTexCoordRefractionProj = 0.5f + 0.5f * IN.vTexCoordProj.xy / IN.vTexCoordProj.w * float2(1.0f,-1.0f);
    float4 vRefractionColor = tex2D(Texture_03_Sampler,vTexCoordRefractionProj);
	
	vTexCoordRefractionProj = 0.5f + 0.5f * (IN.vTexCoordProj.xy + vNormalColorWS * (1.0f - vRefractionColor.a)) / IN.vTexCoordProj.w * float2(1.0f,-1.0f);
	vTexCoordRefractionProj = clamp(vTexCoordRefractionProj, 0.001f, 0.999f); 
	vRefractionColor = tex2D(Texture_03_Sampler,vTexCoordRefractionProj);
	
	float2 vTexCoordReflectionProj = 0.5f + 0.5f * (IN.vTexCoordProj.xy + vNormalColorWS) / IN.vTexCoordProj.w;
	vTexCoordReflectionProj = clamp(vTexCoordReflectionProj, 0.001f, 0.999f);
	float4 vReflectionColor = tex2D(Texture_02_Sampler,vTexCoordReflectionProj);	
	
	float3 vLightReflect = normalize(reflect(vCameraEyePix,vNormalColor));
	float vSpecularFactor = pow(max(0.0f,dot(vLightReflect, vLightDirPix)), fSpecularFactor);
	
	float fReflectionFactor = vReflectionColor.r + vReflectionColor.g + vReflectionColor.b;
	vRefractionColor = lerp(vRefractionColor + vDeepColor * fDarkEffect, vDeepColor * (fDarkEffect + vRefractionColor.a) , (1.0f - vRefractionColor.a));
    float4 vColor = lerp(vRefractionColor, vReflectionColor, fReflectionFactor) + float4(vSpecularFactor,vSpecularFactor,vSpecularFactor,1.0f);
    
    float fDistance = length( vOceanCenter - IN.vWorldPosition );
	float fFogFactor = saturate((fDistance - fFogStart) / fFogEnd);
	float fLuminanceFactor = dot(vLuminanceColor, vFogColor.rgb );
	float4 vLuminanceFogColor = float4(fLuminanceFactor,fLuminanceFactor,fLuminanceFactor,1.0f);
    vColor = lerp(vColor, vLuminanceFogColor, fFogFactor);
    vColor.a = max(0.5f - fFogFactor, 0.0f);
    return vColor;
}

technique ocean
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0  ps_main();
	}
}