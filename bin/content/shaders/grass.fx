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

struct VS_INPUT 
{
	float3 vPosition      : POSITION;
	float2 vTexCoord      : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 vPosition		   : POSITION;
   float2 vTexCoord	       : TEXCOORD0;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   if( IN.vTexCoord.y == 0.0f )  
   {
	  IN.vPosition.x += sin(fTimer*(IN.vPosition.x + IN.vPosition.y) * 0.01f)*0.1f;
	  IN.vPosition.z += cos(fTimer*(IN.vPosition.z + IN.vPosition.x) * 0.01f)*0.3f;
   }
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
    float4 vColor = tex2D( Texture_01_Sampler, IN.vTexCoord);
    return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}