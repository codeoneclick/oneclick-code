float4x4 mWorldViewProjection;

float3 vCameraEye;
float3 vLightDir;

float fParallaxHeight = 0.04f;
float fParallaxStep = 4.0f;

float fAmbientFactor = 0.75f;

float4 vSpecularColor = float4(1.0f,1.0f,1.0f,1.0f);

float fSpecularPower = 16.0f;

texture Texture_01;
sampler Texture_01_Sampler = sampler_state {
	Texture = <Texture_01>;
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

struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
	float3 vNormal		  : NORMAL;
	float3 vTangent		  : TEXCOORD1;
	float3 vBinormal	  : TEXCOORD2;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
   float3 vCameraEye       : TEXCOORD1;
   float3 vLightDir        : TEXCOORD2;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   
   float3x3 mTangentSpace = float3x3(-IN.vTangent,-IN.vBinormal,-IN.vNormal);
   OUT.vLightDir = mul(mTangentSpace,vLightDir);
   OUT.vCameraEye = mul(mTangentSpace,vCameraEye - IN.vPosition);
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
    IN.vCameraEye = normalize(IN.vCameraEye);
    IN.vLightDir = normalize(IN.vLightDir);
   
    float fHeightPower = 0.0f;
    float2 vDisplaceTexCoord = IN.vTexCoord;
    for(int i = 0; i < 0; i++)
    {
		 fHeightPower = tex2D(Texture_01_NH_Sampler, IN.vTexCoord).a;
		 fHeightPower *= 0.04f;
		 vDisplaceTexCoord = vDisplaceTexCoord + (-IN.vCameraEye.xy * fHeightPower);
    }
    
    float3 vNormalColor = tex2D(Texture_01_NH_Sampler, vDisplaceTexCoord).rgb;
	
	vNormalColor = vNormalColor * 2 - 1;
	
	float4 vDiffuseColor =  tex2D( Texture_01_Sampler, vDisplaceTexCoord);
	
	float4 vAmbientColor = vDiffuseColor;						
	
	float vDiffuseFactor = saturate(dot(vNormalColor, IN.vLightDir));
	float3 vLightReflect = reflect(IN.vLightDir, vNormalColor);
	float vSpecularFactor = pow(max(0.0f, dot(vLightReflect, IN.vCameraEye) ), fSpecularPower);
  
    float4 vColor = vDiffuseColor * vDiffuseFactor + vAmbientColor * fAmbientFactor + vSpecularFactor * vSpecularColor;
    return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}