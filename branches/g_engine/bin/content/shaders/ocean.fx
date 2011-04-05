float4x4 mWorldViewProjection;
float fTimer;
float fDarkEffect = 0.77f;
float fSpecularFactor = 128.0f;
float fNormalmapTile = 32.0f;

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

texture Texture_04;
sampler Texture_04_Sampler = sampler_state {
	Texture = <Texture_04>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};


struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
   float4 vTexCoordProj    : TEXCOORD1;
   float3 vCameraEye       : TEXCOORD2;
   float3 vLightDir        : TEXCOORD3;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vTexCoordProj = OUT.vPosition;
   
   float3 vBinormal = float3( 1.0f,  0.0f, 0.0f );
   float3 vTangent  = float3( 0.0f,  0.0f, 1.0f );
   float3 vNormal   = float3( 0.0f,  1.0f, 0.0f );
   
   float3x3 mTangentSpace = float3x3(vTangent,vBinormal,vNormal);
   OUT.vLightDir = mul(mTangentSpace,vLightDir);
   OUT.vCameraEye = mul(mTangentSpace,vCameraEye - IN.vPosition);
   
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	IN.vLightDir = normalize(IN.vLightDir);
	IN.vCameraEye = normalize(IN.vCameraEye);

	IN.vTexCoord *= fNormalmapTile;
	float2 vTexCoord_01 = float2(IN.vTexCoord.x + sin(fTimer)*0.07f,
								 IN.vTexCoord.y - cos(fTimer)*0.09f);
	
	float2 vTexCoord_02 = float2(IN.vTexCoord.x - sin(fTimer)*0.07f,
								 IN.vTexCoord.y + cos(fTimer)*0.09f);

    float3 vNormalColor = normalize((tex2D( Texture_01_Sampler, vTexCoord_01) * 2.0f - 1.0f) + 
						  (tex2D( Texture_01_Sampler, vTexCoord_02 ) * 2.0f - 1.0f));
    
    
    float2 vTexCoordRefractionProj = 0.5f + 0.5f * IN.vTexCoordProj.xy / IN.vTexCoordProj.w * float2(1.0f,-1.0f);
    float4 vRefractionColor = tex2D(Texture_03_Sampler,vTexCoordRefractionProj);
	
	vTexCoordRefractionProj = 0.5f + 0.5f * (IN.vTexCoordProj.xy + vNormalColor * (1.0f - vRefractionColor.a) * 4.0f) / IN.vTexCoordProj.w * float2(1.0f,-1.0f);
	vTexCoordRefractionProj = clamp(vTexCoordRefractionProj, 0.001f, 0.999f); 
	vRefractionColor = tex2D(Texture_03_Sampler,vTexCoordRefractionProj);
	
	float2 vTexCoordReflectionProj = 0.5f + 0.5f * (IN.vTexCoordProj.xy + vNormalColor) / IN.vTexCoordProj.w;
	vTexCoordReflectionProj = clamp(vTexCoordReflectionProj, 0.001f, 0.999f);
	float4 vReflectionColor = tex2D(Texture_02_Sampler,vTexCoordReflectionProj);	
	
	float4 vDeepColor = float4(0.35f, 0.60f, 0.77f, 1.0f);
	float fReflectionFactor = vReflectionColor.r + vReflectionColor.g + vReflectionColor.b;
	vRefractionColor = lerp(vRefractionColor, vDeepColor * (fDarkEffect + vRefractionColor.a), (1.0f - vRefractionColor.a));
	
	float3 vLightReflect = reflect(IN.vLightDir, vNormalColor);
	float vSpecularFactor = pow(max(0.0f, dot(vLightReflect, IN.vCameraEye) ), fSpecularFactor);
	
    float4 vColor = lerp(vRefractionColor, vReflectionColor, fReflectionFactor) + float4(vSpecularFactor,vSpecularFactor,vSpecularFactor,1.0f);
    return vColor;
}

technique ocean
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}