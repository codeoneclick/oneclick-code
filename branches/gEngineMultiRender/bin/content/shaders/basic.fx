float4x4 mWorldViewProjection;

texture Texture_01;
sampler Texture_01_Sampler = sampler_state {
	Texture = <Texture_01>;
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
   float4 vPosition		  : POSITION;
   float2 vTexCoord	      : TEXCOORD0;
   float  vTemp           : TEXCOORD1;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vTemp = IN.vPosition.y;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
   float4 vColor = tex2D(Texture_01_Sampler, IN.vTexCoord);
   if(IN.vTemp < -64.0f) discard;
   return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}