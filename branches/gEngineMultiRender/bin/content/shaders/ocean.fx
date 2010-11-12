float4x4 mWorldViewProjection;

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

	float2 vTexCoord_01 = float2(IN.vTexCoord.x + sin(fTimer)*0.05f,
								 IN.vTexCoord.y + cos(fTimer)*0.07f);
	
	float2 vTexCoord_02 = float2(IN.vTexCoord.x - sin(fTimer)*0.07f,
								 IN.vTexCoord.y - cos(fTimer)*0.05f);

    float3 vNormalColor = normalize((tex2D( Texture_01_Sampler, vTexCoord_01 ) * 2.0f - 1.0f) + 
						  (tex2D( Texture_01_Sampler, vTexCoord_02 ) * 2.0f - 1.0f));
    
    
	//////////////////////////////////// REFLECTION //////////////////////////////////////
	float2 vTexCoordReflectionProj = IN.vTexCoordProj.xy;
	vTexCoordReflectionProj += vNormalColor*1.5f;
	vTexCoordReflectionProj.x = 0.5f + 0.5f * vTexCoordReflectionProj.x/IN.vTexCoordProj.w;
	vTexCoordReflectionProj.y = 0.5f + 0.5f * vTexCoordReflectionProj.y/IN.vTexCoordProj.w;
	vTexCoordReflectionProj = clamp(vTexCoordReflectionProj, 0.001, 0.999); 
	float4 vReflectionColor = tex2D(Texture_02_Sampler,vTexCoordReflectionProj);	
	
	float2 vTexCoordRefractionProj = IN.vTexCoordProj.xy;
	vTexCoordRefractionProj += vNormalColor.xz * 4.0f;
	vTexCoordRefractionProj.x = 0.5f + 0.5f * vTexCoordRefractionProj.x/IN.vTexCoordProj.w;
	vTexCoordRefractionProj.y = 0.5f - 0.5f * vTexCoordRefractionProj.y/IN.vTexCoordProj.w;
	vTexCoordRefractionProj = clamp(vTexCoordRefractionProj, 0.001f, 0.999f); 
	float4 vRefractionColor = tex2D(Texture_03_Sampler,vTexCoordRefractionProj);
									
    float4 vColor = vRefractionColor + vReflectionColor;
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