string description = "CryEngine2"; 

float3 vEye;
float3 vSunPos;
float3 vInvWavelength;


float3 vHG;
float3 Tex;
float fKrESun;
float fKmESun;

float4x4 worldViewProj : WorldViewProjection;

float Exposure = -2.0;
float c = 0.002f; // height falloff
float b = 0.002f; // global density

Texture tSkyBuffer;

sampler SkyBuffer = sampler_state 
{
    Texture = <tSkyBuffer>;
    AddressU  = WRAP;        
    AddressV  = CLAMP;
    MIPFILTER = NONE;
    MINFILTER = POINT;
    MAGFILTER = POINT;
};

// Vertex Shader
struct vertexInput {
    float3 pos      : POSITION;
    float2 t0       : TEXCOORD0;
};

struct vertexOutput {
	float4 pos : POSITION;
	float2 t0 : TEXCOORD0;
    float3 t1 : TEXCOORD1;
};

vertexOutput SkyFromGround_VS(vertexInput In ) 
{
	vertexOutput Out;
	Out.t0 = In.t0;
	Out.t1 = vEye - In.pos; 
	Out.pos = mul( float4(In.pos.xyz, 1.0), worldViewProj);
	return Out;
} 

// Calculates the Mie phase function
float getMiePhase(float fCos, float fCos2)
{
	return vHG.x * (1.0 + fCos2) / pow(vHG.y - vHG.z * fCos, 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
	return 0.75 + 0.75 * fCos2;
}

//Pixel Shader
struct pixelOutput {
    float4 color  : COLOR0;
};  

pixelOutput SkyFromGround_PS( vertexOutput In)
{
pixelOutput  Out;

float2 interp = frac( In.t0 * Tex.x );

float4 S00 = tex2D( SkyBuffer, In.t0 ).rgba;
float4 S10 = tex2D( SkyBuffer, In.t0 + float2(Tex.y, 0.0f) ).rgba;
float4 S01 = tex2D( SkyBuffer, In.t0 + float2(0.0f, Tex.y) ).rgba;
float4 S11 = tex2D( SkyBuffer, In.t0 + float2(Tex.y, Tex.y) ).rgba;

float4 Dx1 = lerp(S00, S10, interp.x);
float4 Dx2 = lerp(S01, S11, interp.x);

float4 vSamples = lerp(Dx1, Dx2, interp.y);

float3 c0 = vSamples.rgb * (vInvWavelength * fKrESun);
float3 c1 = vSamples.rgb * fKmESun;

float fCos = dot(vSunPos, In.t1) /length(In.t1);
float fCos2 = fCos * fCos;

float3 Mie = getMiePhase(fCos, fCos2) * c1;
Out.color.a = 1.0f;

Out.color.rgb = getRayleighPhase(fCos2) * c0 + Mie;
return Out;
}

technique Sky_dx9 
{
	pass pRenderSky
	{	 
		ZEnable = true;
		ZWriteEnable = false;
		AlphaBlendEnable = false;
    	FVF = XYZ | TEX1;
    
    	VertexShader = compile vs_2_0 SkyFromGround_VS( );
    	PixelShader = compile ps_2_0 SkyFromGround_PS( );
	}
}