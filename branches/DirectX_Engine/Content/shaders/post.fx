texture renderTargetTexture_01;

sampler renderTargetSampler_01 = sampler_state
{
    Texture = <renderTargetTexture_01>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

texture renderTargetTexture_02;

sampler renderTargetSampler_02 = sampler_state
{
    Texture = <renderTargetTexture_02>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

float BloomThreshold = 0.3f;

struct VS_Output{
    float4 Position:POSITION;
    float2 Texture:TEXCOORD0;
};

VS_Output VS( float3 Position:POSITION,  float2 Texture:TEXCOORD0 ){
    VS_Output OUT;
    OUT.Position = float4(Position,1.0f);
	OUT.Texture  = Texture;
    return OUT;
}


float4 PS_BLOOM_EXTRACT(VS_Output IN) : COLOR0
{
    float4 c = tex2D(renderTargetSampler_01, IN.Texture);
    return saturate((c - BloomThreshold) / (1 - BloomThreshold));
}

technique BloomExtract
{
    pass p0
    {
	    VertexShader = compile vs_2_0 VS();
        PixelShader  = compile ps_2_0 PS_BLOOM_EXTRACT();
    }
}

float BlurDistance = 0.001f;

float4 PS_GAUS_BLUR_VR(VS_Output IN) : COLOR0
{

	float4 Color;
    // Get the texel from ColorMapSampler using a modified texture coordinate. This
    // gets the texels at the neighbour texels and adds it to Color.
	Color  = tex2D( renderTargetSampler_01, float2(IN.Texture.x+BlurDistance, IN.Texture.y+BlurDistance));
	Color += tex2D( renderTargetSampler_01, float2(IN.Texture.x-BlurDistance, IN.Texture.y-BlurDistance));
	Color += tex2D( renderTargetSampler_01, float2(IN.Texture.x+BlurDistance, IN.Texture.y-BlurDistance));
	Color += tex2D( renderTargetSampler_01, float2(IN.Texture.x-BlurDistance, IN.Texture.y+BlurDistance));
    // We need to devide the color with the amount of times we added
    // a color to it, in this case 4, to get the avg. color
    Color = Color / 4; 
 
    // returned the blurred color
    return Color;
   /* float4 c = 0;
    float blurSize = 1.0/4096.0f;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x - 4.0*blurSize, IN.Texture.y)) * 1.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x - 3.0*blurSize, IN.Texture.y)) * 2.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x - 2.0*blurSize, IN.Texture.y)) * 3.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x - blurSize, IN.Texture.y)) * 4.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y)) * 5.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x + blurSize, IN.Texture.y)) * 4.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x + 2.0*blurSize, IN.Texture.y)) * 3.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x + 3.0*blurSize, IN.Texture.y)) * 2.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x + 4.0*blurSize, IN.Texture.y)) * 1.0/25.0;
    return c;*/
}


float4 PS_GAUS_BLUR_HR(VS_Output IN) : COLOR0
{
    float4 c = 0;
    float blurSize = 1.0/4096.0f;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y - 4.0*blurSize)) * 1.0/25.0;
	c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y - 3.0*blurSize)) * 2.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y - 2.0*blurSize)) * 3.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y - blurSize)) * 4.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y)) * 5.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y + blurSize)) * 4.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y + 2.0*blurSize)) * 3.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y + 3.0*blurSize)) * 2.0/25.0;
    c += tex2D(renderTargetSampler_01, float2(IN.Texture.x, IN.Texture.y + 4.0*blurSize)) * 1.0/25.0;
    return c;
}

technique GaussianBlurVr
{
    pass p0
    {
	    VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_GAUS_BLUR_VR();
    }
}

technique GaussianBlurHr
{
    pass p0
    {
	    VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_GAUS_BLUR_HR();
    }
}


float BloomIntensity = 0.0f;
float BaseIntensity = 1.0f;

float BloomSaturation = 1.0f;
float BaseSaturation = 1.0f;

float4 AdjustSaturation(float4 color, float saturation)
{
    float grey = dot(color, float3(0.2126f,0.7152f,0.0722f));
    return lerp(grey, color, saturation);
}


float4 PS_BLOOM_COMBINE(VS_Output IN) : COLOR0
{
    
    float4 bloom = tex2D(renderTargetSampler_01, IN.Texture);
    float4 base = tex2D(renderTargetSampler_02, IN.Texture);

   
    bloom = AdjustSaturation(bloom, BloomSaturation) * BloomIntensity;
    base = AdjustSaturation(base, BaseSaturation) * BaseIntensity;
    
    base *= (1 - saturate(bloom));
    
    return base + bloom;
}


technique BloomCombine
{
    pass p0
    {
	    VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_BLOOM_COMBINE();
    }
}

float4x4 g_matLightViewProj;

struct VSOUTPUT_SHADOW
{
	float4 vPosition	: POSITION;
	float  fDepth		: TEXCOORD0;
};

// Shadow generation vertex shader
VSOUTPUT_SHADOW VS_Shadow( float4 inPosition : POSITION )
{
	// Output struct
	VSOUTPUT_SHADOW OUT = (VSOUTPUT_SHADOW)0;

	// Output the transformed position
	OUT.vPosition = mul( inPosition, g_matLightViewProj );

	// Output the scene depth
	OUT.fDepth = OUT.vPosition.z;

	return OUT;
}

//--------------------------------------------
// Pixel shaders
//--------------------------------------------
float4  PS_Shadow( VSOUTPUT_SHADOW IN ) : COLOR0
{
	// Output the scene depth
	return float4( 1.0f, 0.0f, IN.fDepth, 1.0f );
}
	
//--------------------------------------------
// Techniques
//--------------------------------------------
technique techShadow
{
	pass p0
	{
		Lighting	= False;
		CullMode	= CCW;
		
		VertexShader = compile vs_2_0 VS_Shadow();
		PixelShader  = compile ps_2_0 PS_Shadow();
	}
}
