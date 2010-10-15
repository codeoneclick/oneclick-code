float4x4 mWorldViewProjection;

float fDiscardHeight = 0.0f;
float fDiscardUp = 0.0f;

float3 vCameraEye;
float3 vLightDir;

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
   
   float3x3 TangentSpace = float3x3(IN.vTangent,IN.vBinormal,IN.vNormal);
   OUT.vLightDir = mul(TangentSpace,vLightDir);
   OUT.vCameraEye = mul(TangentSpace,vCameraEye - IN.vPosition);
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
    IN.vCameraEye = normalize(IN.vCameraEye);
    IN.vLightDir = normalize(IN.vLightDir);
   
    float fHeightPower = 0.0f;
    float2 vDisplaceTexCoord = IN.vTexCoord;
    for(int i = 0; i < 8; i++)
    {
		 fHeightPower = tex2D(Texture_01_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.x + 
					    tex2D(Texture_02_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.y + 
					    tex2D(Texture_03_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.z;
		 fHeightPower *= 0.08f / 8.0f;
		 vDisplaceTexCoord = vDisplaceTexCoord + (-IN.vCameraEye.xy * fHeightPower);
    }
    
    float3 vNormalColor = tex2D(Texture_01_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.x + 
						  tex2D(Texture_02_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.y + 
						  tex2D(Texture_03_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.z;
	
	vNormalColor = vNormalColor * 2 - 1;
	
	float4 vDiffuceColor =  tex2D( Texture_01_Sampler, vDisplaceTexCoord )*IN.vSplatting.x + 
							tex2D( Texture_02_Sampler, vDisplaceTexCoord )*IN.vSplatting.y + 
							tex2D( Texture_03_Sampler, vDisplaceTexCoord )*IN.vSplatting.z;
							
	float4 vAmbientColor = vDiffuceColor;
	
	vDiffuceColor *= dot(vNormalColor, IN.vLightDir);
	float3 vLightReflection = normalize( reflect(IN.vLightDir, vNormalColor) );	
	float vSpecularColor = pow(max(0.0, dot(vLightReflection, IN.vCameraEye) ), 128.0f);
   
   if(IN.vDiscardPosition.y > fDiscardHeight && fDiscardUp < 0.0f)
		discard;
   if(IN.vDiscardPosition.y < fDiscardHeight && fDiscardUp > 0.0f)
		discard;
   float4 vColor = vDiffuceColor + vAmbientColor;
   vColor.a = 1.0f;
   return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}