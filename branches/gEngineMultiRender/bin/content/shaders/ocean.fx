float4x4 mWorldViewProjection;

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

struct VS_INPUT {
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
};

struct VS_OUTPUT {
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
   float4 vTexCoordProj    : TEXCOORD1;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vTexCoordProj = OUT.vPosition;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
	float2 vTexCoordReflectionProj = IN.vTexCoordProj.xy;
	vTexCoordReflectionProj.x = 0.5f + 0.5f * vTexCoordReflectionProj.x/IN.vTexCoordProj.w;
	vTexCoordReflectionProj.y = 0.5f + 0.5f * vTexCoordReflectionProj.y/IN.vTexCoordProj.w;
	vTexCoordReflectionProj = clamp(vTexCoordReflectionProj, 0.001, 0.999); 
	float4 vReflectionColor = tex2D(Texture_02_Sampler,vTexCoordReflectionProj);									
    float4 vColor = vReflectionColor;
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