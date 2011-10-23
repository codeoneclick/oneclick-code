float3 vEye;
float3 vSunPos;
float3 vInvWavelength;


float3 vHG;
float3 Tex;
float fKrESun;
float fKmESun;

float4x4 worldViewProj : WorldViewProjection;

texture Texture_01;
sampler Texture_01_Sampler = sampler_state {
	Texture = <Texture_01>;
	AddressU  = WRAP;        
    AddressV  = CLAMP;
	MinFilter = NONE;
	MagFilter = POINT;
	MipFilter = POINT;
};

struct VS_INPUT 
{
   float3 vPosition  : POSITION;
   float2 vTexCoord  : TEXCOORD0;
};

struct VS_OUTPUT 
{
	float4 vPosition    : POSITION;
	float2 vTexCoord_01 : TEXCOORD0;
    float3 vTexCoord_02 : TEXCOORD1;
};

VS_OUTPUT main_vs(VS_INPUT IN ) 
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;
	OUT.vTexCoord_01 = IN.vTexCoord;
	OUT.vTexCoord_02 = vEye - IN.vPosition; 
	OUT.vPosition = mul( float4(IN.vPosition, 1.0f), worldViewProj);
	return OUT;
} 

float getMiePhase(float fCos, float fCos2)
{
	return vHG.x * (1.0f + fCos2) / pow(vHG.y - vHG.z * fCos, 1.5);
}
float getRayleighPhase(float fCos2)
{
	return 0.75f + 0.75f * fCos2;
}

float4 main_ps( VS_OUTPUT IN) : COLOR 
{

	float2 interp = frac( IN.vTexCoord_01 * Tex.x );

	float4 S00 = tex2D( Texture_01_Sampler, IN.vTexCoord_01 );
	float4 S10 = tex2D( Texture_01_Sampler, IN.vTexCoord_01 + float2(Tex.y, 0.0f));
	float4 S01 = tex2D( Texture_01_Sampler, IN.vTexCoord_01 + float2(0.0f, Tex.y));
	float4 S11 = tex2D( Texture_01_Sampler, IN.vTexCoord_01 + float2(Tex.y, Tex.y));

	float4 Dx1 = lerp(S00, S10, interp.x);
	float4 Dx2 = lerp(S01, S11, interp.x);

	float4 vSamples = lerp(Dx1, Dx2, interp.y);

	float3 c0 = vSamples.rgb * (vInvWavelength * fKrESun);
	float3 c1 = vSamples.rgb * fKmESun;

	float fCos = dot(vSunPos, IN.vTexCoord_02) /length(IN.vTexCoord_02);
	float fCos2 = fCos * fCos;

	float3 Mie = getMiePhase(fCos, fCos2) * c1;
	
	float4 vColor;

	vColor.rgb = getRayleighPhase(fCos2) * c0 + Mie;
	vColor.a = 1.0f;
	return vColor;
}

technique sky 
{
	pass p0
	{	 
    	VertexShader = compile vs_2_0 main_vs( );
    	PixelShader = compile ps_2_0 main_ps( );
	}
}