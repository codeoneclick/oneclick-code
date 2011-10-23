float4x4 mWorldViewProjection;
float4x4 mWorld;

float fTimer;

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

float3 vCameraEye;
float3 vLightDir;

struct VS_INPUT 
{
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
};

struct VS_OUTPUT 
{
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
   OUT.vCameraEye = vCameraEye - IN.vPosition;
   OUT.vLightDir = vLightDir;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	IN.vCameraEye = normalize(IN.vCameraEye);
	IN.vLightDir = normalize(IN.vLightDir);
	
	float diff = dot(IN.vLightDir, IN.vCameraEye);	
	float YAngle = max(0.0f, IN.vCameraEye.y);	
	
	float4 fogColorDay = tex2D( Texture_01_Sampler, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	float4 fogColorSunset = tex2D( Texture_03_Sampler, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	float4 fogColorNight = tex2D( Texture_02_Sampler, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	
	
	float4 color;
	
	if (IN.vLightDir.y > 0)
	{
		color = lerp(fogColorDay, fogColorSunset, min(1, pow(1 - IN.vLightDir.y, 1.5f)));
	}
	else
	{
		color = lerp(fogColorSunset, fogColorNight, min(1, -IN.vLightDir.y));
	}
	
	return float4(1.0f,0.0f,0.0f,1.0f);
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}