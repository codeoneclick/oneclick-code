float4x4 mWorldViewProjection;

struct VS_INPUT 
{
	float3 vPosition      : POSITION;
	float2 vExtValue      : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 vPosition		   : POSITION;
   float2 vExtValue	       : TEXCOORD0;
};


VS_OUTPUT vs_main(VS_INPUT IN) 
{
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   OUT.vPosition = mul( float4(IN.vPosition,1.0f) ,mWorldViewProjection);
   OUT.vExtValue = IN.vExtValue;
   return OUT;
}

float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
    float4 vColor = float4(0.0f,1.0f,0.0f,IN.vExtValue.x);
    return vColor;
}

technique mesh
{
	pass p0 
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}