
float4x4 mWorld;
float4x4 mView;
float4x4 mProjection;

struct VSOUTPUT_SHADOW
{
	float4 vPosition	: POSITION;
	float  fDepth		: TEXCOORD0;
};

// Shadow generation vertex shader
VSOUTPUT_SHADOW VS_Shadow( float3 inPosition : POSITION )
{
	// Output struct
	VSOUTPUT_SHADOW OUT = (VSOUTPUT_SHADOW)0;

	float4x4 mWorldViewProjection = mul(mWorld,mul(mView,mProjection));
	OUT.vPosition     = mul(float4(inPosition,1.0f), mWorldViewProjection);

	OUT.fDepth = OUT.vPosition.z;

	return OUT;
}

//--------------------------------------------
// Pixel shaders
//--------------------------------------------
float4  PS_Shadow( VSOUTPUT_SHADOW IN ) : COLOR0
{
	// Output the scene depth
	return float4(IN.fDepth/(2560.0f*1.7f),IN.fDepth/(2560.0f*1.7f),IN.fDepth/(2560.0f*1.7f),1.0f);
}
	
//--------------------------------------------
// Techniques
//--------------------------------------------
technique techShadow
{
	pass p0
	{
		//Lighting	= False;
		CullMode	= NONE;
		
		VertexShader = compile vs_2_0 VS_Shadow();
		PixelShader  = compile ps_2_0 PS_Shadow();
	}
}