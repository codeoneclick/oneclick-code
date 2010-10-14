float4x4 mWorldViewProjection;

float fDiscardHeight = 0.0f;
float fDiscardUp = 0.0f;

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
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vTexCoord = IN.vTexCoord;
   OUT.vDiscardPosition = IN.vPosition;
   OUT.vSplatting = IN.vSplatting;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
   float4 vColor_01 = tex2D(Texture_01_Sampler, IN.vTexCoord) * IN.vSplatting.x;
   float4 vColor_02 = tex2D(Texture_02_Sampler, IN.vTexCoord) * IN.vSplatting.y;
   float4 vColor_03 = tex2D(Texture_03_Sampler, IN.vTexCoord) * IN.vSplatting.z;
   
   float4 vColor = vColor_01 + vColor_02 + vColor_03;
   
   if(IN.vDiscardPosition.y > fDiscardHeight && fDiscardUp < 0.0f)
		discard;
   if(IN.vDiscardPosition.y < fDiscardHeight && fDiscardUp > 0.0f)
		discard;
   return vColor;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}