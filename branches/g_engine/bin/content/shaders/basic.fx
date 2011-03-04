float4x4 mWorldViewProjection;

float3 vCameraEye;
float3 vLightDir;

float fParallaxHeight = 0.07f;
float fParallaxStep = 1.0f;

float fAmbientFactor = 0.75f;

float4 vSpecularColor = float4(1.0f,1.0f,1.0f,1.0f);

float fSpecularPower = 16.0f;

float fOceanLevel = 12.0f;

float fRimStart = 0.8f;
float fRimEnd = 1.0f;

float fRimFactor = 4.0f;

float4 vRimColor = float4(0.5f,0.5f,0.0f,1.0f);

float fGridMaskFactor = 16.0f;

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

texture Texture_grid_mask;
sampler Texture_grid_mask_Sampler = sampler_state {
	Texture = <Texture_grid_mask>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
	float4 vNormal		  : COLOR0;
	float4 vTangent		  : COLOR1;
	float4 vSplatting     : COLOR2;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float4 vSplatting       : COLOR0;
   float2 vTexCoord	       : TEXCOORD0;
   float3 vNormal          : TEXCOORD1;
   float3 vTangent		   : TEXCOORD2;
   float3 vWorldPosition   : TEXCOORD3;
   float  fReflectFactor   : TEXCOORD4;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vSplatting = IN.vSplatting;
   
   float3 vTangent = IN.vTangent.yzw * 2.0f - 1.0f;
   float3 vNormal = IN.vNormal.yzw * 2.0f - 1.0f;
   
   OUT.vTangent = vTangent;
   OUT.vNormal = vNormal;
   OUT.vWorldPosition = IN.vPosition;
   OUT.fReflectFactor = IN.vPosition.y;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	IN.vTangent = normalize(IN.vTangent);
	IN.vNormal = normalize(IN.vNormal);
	
	float3x3 mTangentSpace = float3x3(IN.vTangent,cross(IN.vTangent,IN.vNormal),IN.vNormal);
	float3 vCameraEyeTangentSpace = normalize(mul(mTangentSpace,vCameraEye - IN.vWorldPosition)); 
	float3 vCameraEyeWorldSpace = normalize(vCameraEye - IN.vWorldPosition);
	float3 vLightDirTangentSpace = normalize(mul(mTangentSpace,vLightDir));
   
    float fHeightPower = 0.0f;
    float2 vDisplaceTexCoord = IN.vTexCoord;
    fHeightPower = tex2D(Texture_01_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.x + 
				   tex2D(Texture_02_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.y + 
				   tex2D(Texture_03_NH_Sampler, IN.vTexCoord).a * IN.vSplatting.z;
    fHeightPower *= 0.04f;
	vDisplaceTexCoord = vDisplaceTexCoord + (vCameraEyeTangentSpace.xy * fHeightPower);
    
    float3 vNormalColor = tex2D(Texture_01_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.x + 
						  tex2D(Texture_02_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.y + 
						  tex2D(Texture_03_NH_Sampler, vDisplaceTexCoord).rgb * IN.vSplatting.z;
	
	vNormalColor = vNormalColor * 2 - 1;
	vNormalColor = normalize(vNormalColor);
	
	float4 vDiffuseColor =  tex2D( Texture_01_Sampler, vDisplaceTexCoord )*IN.vSplatting.x + 
							tex2D( Texture_02_Sampler, vDisplaceTexCoord )*IN.vSplatting.y + 
							tex2D( Texture_03_Sampler, vDisplaceTexCoord )*IN.vSplatting.z;
	
	float4 vAmbientColor = vDiffuseColor;						
	
	float vDiffuseFactor = saturate(dot(vNormalColor, vLightDirTangentSpace) * 0.5f + 0.75f);
    
	float3 vLightReflect = reflect(vLightDirTangentSpace, vNormalColor);
	float vSpecularFactor = pow(max(0.0f, dot(vLightReflect, vCameraEyeTangentSpace) ), fSpecularPower);
	
	float fRimPower = smoothstep(fRimStart , fRimEnd ,1.0f - dot(normalize(IN.vNormal),-vCameraEyeWorldSpace));
	
	float4 vGridColor = tex2D( Texture_grid_mask_Sampler, IN.vTexCoord * fGridMaskFactor) * float4(IN.vSplatting.x,IN.vSplatting.y,IN.vSplatting.z,1.0f);
	
    float4 vColor = vDiffuseColor * vDiffuseFactor + vSpecularFactor * vSpecularColor + fRimPower * vDiffuseColor * fRimFactor;// + vGridColor;
    vColor.a = IN.fReflectFactor / fOceanLevel;
    return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}