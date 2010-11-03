float4x4 mWorldViewProjection;

float fDiscardHeight = 0.0f;
float fDiscardUp = 0.0f;

float3 vCameraEye;
float3 vLightDir;

float fParallaxHeight = 0.04f;
float fParallaxStep = 1.0f;

const float fAmbientFactor = 0.75f;

const float4 vSpecularColor = float4(1.0f,1.0f,1.0f,1.0f);

const float fSpecularPower = 16.0f;

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
	float3 vNormal		  : NORMAL;
	float3 vTangent		  : TEXCOORD1;
	float3 vBinormal	  : TEXCOORD2;
	float4 vSplatting     : TEXCOORD3;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
   float3 vDiscardPosition : TEXCOORD1;
   float4 vSplatting       : TEXCOORD2;
   float3 vCameraEye       : TEXCOORD3;
   float3 vLightDir        : TEXCOORD4;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vDiscardPosition = IN.vPosition;
   OUT.vSplatting = IN.vSplatting;
   
   float3x3 mTangentSpace = float3x3(-IN.vTangent,-IN.vBinormal,-IN.vNormal);
   OUT.vLightDir = mul(mTangentSpace,vLightDir);
   OUT.vCameraEye = mul(mTangentSpace,vCameraEye - IN.vPosition);
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
   if(IN.vDiscardPosition.y > fDiscardHeight && fDiscardUp < 0.0f)
		discard;
   if(IN.vDiscardPosition.y < fDiscardHeight && fDiscardUp > 0.0f)
		discard;

    IN.vCameraEye = normalize(IN.vCameraEye);
    IN.vLightDir = normalize(IN.vLightDir);
   
    float fHeightPower = 0.0f;
    float2 vDisplaceTexCoord = IN.vTexCoord;
    for(int i = 0; i < 4; i++)
    {
		 fHeightPower = tex2D(Texture_01_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.x + 
					    tex2D(Texture_02_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.y + 
					    tex2D(Texture_03_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.z;
		 fHeightPower *= fParallaxHeight / fParallaxStep;
		 vDisplaceTexCoord = vDisplaceTexCoord + (-IN.vCameraEye.xy * fHeightPower);
    }
    
    float3 vNormalColor = tex2D(Texture_01_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.x + 
						  tex2D(Texture_02_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.y + 
						  tex2D(Texture_03_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.z;
	
	vNormalColor = vNormalColor * 2 - 1;
	
	float4 vDiffuseColor =  tex2D( Texture_01_Sampler, vDisplaceTexCoord )*IN.vSplatting.x + 
							tex2D( Texture_02_Sampler, vDisplaceTexCoord )*IN.vSplatting.y + 
							tex2D( Texture_03_Sampler, vDisplaceTexCoord )*IN.vSplatting.z;
	
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