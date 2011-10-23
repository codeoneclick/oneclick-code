float4x4 matrix_world;
float4x4 matrix_view;
float4x4 matrix_projection;
float4x4 matrix_world_inverse_transponse;
float4x4 matrix_view_inverse;

struct VS_INPUT_SKY
{
	float3 Position				: POSITION;
	float4 Normal				: NORMAL;
	float2 Texture				: TEXCOORD0;
};

struct VS_OUTPUT_SKY
{
	float4 Position		 		: POSITION;
	float2 Texture				: TEXCOORD0;
	float3 Light				: TEXCOORD1;
	float3 Normal		    	: TEXCOORD2;
	float3 View					: TEXCOORD3;
};

float4 LightDirection = {100.0f, 100.0f, 100.0f, 1.0f};
float4 LightColor = {1.0f, 1.0f, 1.0f, 1.0f};
float4 LightColorAmbient = {0.0f, 0.0f, 0.0f, 1.0f};

float4 FogColor = {1.0f, 1.0f, 1.0f, 1.0f};

float SunLightness = 0.05; 

float sunRadiusAttenuation = 64;

float largeSunLightness = 0.1;
float largeSunRadiusAttenuation = 1;
float dayToSunsetSharpness = 1.5;
float hazeTopAltitude = 20; 

float time;
float numTiles = 16;

float CloudCover = -0.1;
float CloudSharpness = 0.1;

float4 SunColor = float4(0.8f,0.8f,0.8f,1.0f);

texture permTexture;

sampler permSampler = sampler_state
{
	Texture = <permTexture>;
	MinFilter = Linear;
	MipFilter = Linear;
	MagFilter = Linear;
	ADDRESSU = WRAP;
	ADDRESSV = WRAP;
};

struct VS_INPUT_CLOUDS
{
    float3 Position : POSITION0;
    float2 Texture  : TEXCOORD0;
};

struct VS_OUTPUT_CLOUDS
{
    float4 Position : POSITION0;
    float2 Texture  : TEXCOORD0;
};

texture SkyTextureNight;

sampler SurfSamplerSkyTextureNight = sampler_state
{
	Texture = <SkyTextureNight>;
	MinFilter = Linear;
	MipFilter = Linear;
	MagFilter = Linear;
	AddressU = mirror; 
	AddressV = mirror;
};

texture SkyTextureSunset;

sampler SurfSamplerSkyTextureSunset = sampler_state
{
	Texture = <SkyTextureSunset>;
	MinFilter = Linear;
	MipFilter = Linear;
	MagFilter = Linear;
	AddressU = mirror; 
	AddressV = mirror;
};

texture SkyTextureDay;

sampler SurfSamplerSkyTextureDay = sampler_state
{
	Texture = <SkyTextureDay>;
	MinFilter = Linear;
	MipFilter = Linear;
	MagFilter = Linear;
	AddressU = mirror; 
	AddressV = mirror;
};

VS_OUTPUT_SKY SKY_VS(VS_INPUT_SKY IN)
{
	VS_OUTPUT_SKY OUT;
	float4x4 matrix_world_view_projection = mul(matrix_world,matrix_view);
	matrix_world_view_projection = mul(matrix_world_view_projection,matrix_projection);
	
	OUT.Position = mul(float4(IN.Position,1.0f), matrix_world_view_projection);
	
	OUT.Normal = IN.Normal;//mul(IN.Normal, matrix_world_inverse_transponse).xyz;

	OUT.Light = -LightDirection;
	
	float3 world_position = mul(float4(IN.Position,1.0f), matrix_world).xyz;
	
	OUT.View = matrix_view_inverse[3].xyz - world_position;

	OUT.Texture = IN.Texture;
	return OUT;
}

float4 SKY_PS(VS_OUTPUT_SKY IN) : COLOR0
{	
	float4 colorOutput = float4(0,0,0,1);
	IN.View = normalize(IN.View);
	//IN.Normal = normalize(IN.Normal);
	IN.Light = normalize(IN.Light);
	
	float NdotL = max( dot( IN.Normal, -IN.Light), 0);
	
	float4 colorDiffuse  = (NdotL * LightColor) + LightColorAmbient;
	colorOutput += colorDiffuse;		
	colorOutput.a = 1.0f;
	
	float sunHighlight = pow(max(0, dot(IN.Light, -IN.View)), sunRadiusAttenuation) * SunLightness;	
	float largeSunHighlight = pow(max(0, dot(IN.Light, -IN.View)), largeSunRadiusAttenuation) * largeSunLightness;
	
	float3 flatLightVec = normalize(float3(IN.Light.x, 0, IN.Light.z));
	float3 flatEyeVec = normalize(float3(IN.View.x, 0, IN.View.z));
	float diff = dot(flatLightVec, -flatEyeVec);	
	float YAngle = pow(max(0, -IN.View.y), 1.25f );	
	
	float4 fogColorDay =    tex2D( SurfSamplerSkyTextureDay, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	float4 fogColorSunset = tex2D( SurfSamplerSkyTextureSunset, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	float4 fogColorNight =  tex2D( SurfSamplerSkyTextureNight, float2( 1 - (diff + 1) * 0.5, 1-YAngle));
	
	float4 fogColor;
	
	if (IN.Light.y > 0)
	{
		fogColor = lerp(fogColorDay, fogColorSunset, min(1, pow(1 - IN.Light.y, dayToSunsetSharpness)));
	}
	else
	{
		fogColor = lerp(fogColorSunset, fogColorNight, min(1, -IN.Light.y * 4));
	}
	
	fogColor += sunHighlight + largeSunHighlight;
	
	colorOutput = fogColor + sunHighlight/2;
		
	return colorOutput*0.8f;
}

//////////////////////////////////////////////////////////////////////////////


VS_OUTPUT_CLOUDS CLOUDS_VS(VS_INPUT_CLOUDS IN)
{
    VS_OUTPUT_CLOUDS OUT;

    float4 worldPosition = mul(float4(IN.Position,1.0f), matrix_world);
    float4 viewPosition = mul(worldPosition, matrix_view);
    OUT.Position = mul(viewPosition, matrix_projection);
    OUT.Texture = (IN.Texture * numTiles);
    return OUT;
}


#define ONE 0.00390625
#define ONEHALF 0.001953125
// The numbers above are 1/256 and 0.5/256, change accordingly
// if you change the code to use another texture size.

float fade(float t) 
{
  return t*t*t*(t*(t*6.0-15.0)+10.0);
}


float noise(float2 P)
{
  float2 Pi = ONE*floor(P)+ONEHALF;
  float2 Pf = frac(P);

  float2 grad00 = tex2D(permSampler, Pi).rg * 4.0 - 1.0;
  float n00 = dot(grad00, Pf);

  float2 grad10 = tex2D(permSampler, Pi + float2(ONE, 0.0)).rg * 4.0 - 1.0;
  float n10 = dot(grad10, Pf - float2(1.0, 0.0));

  float2 grad01 = tex2D(permSampler, Pi + float2(0.0, ONE)).rg * 4.0 - 1.0;
  float n01 = dot(grad01, Pf - float2(0.0, 1.0));

  float2 grad11 = tex2D(permSampler, Pi + float2(ONE, ONE)).rg * 4.0 - 1.0;
  float n11 = dot(grad11, Pf - float2(1.0, 1.0));

  float2 n_x = lerp(float2(n00, n01), float2(n10, n11), fade(Pf.x));

  float n_xy = lerp(n_x.x, n_x.y, fade(Pf.y));

  return n_xy;
}

float4 CLOUDS_PS(VS_OUTPUT_CLOUDS IN) : COLOR0
{

	float n =  noise(IN.Texture + time);  
	float n2 = noise(IN.Texture * 2 + time);
	float n3 = noise(IN.Texture * 4 + time);
	
	float nFinal = n + (n2 / 2) + (n3 / 4);
 
    float CloudDensity = 1.0 - pow(CloudSharpness,max(CloudCover - nFinal,0.0f));
    
    float4 retColor = CloudDensity;
    retColor *= SunColor;
    retColor *= float4(4.0f,4.0f,16.0f,0.5f);
    return retColor;

}

technique CLOUDS
{
    pass pass0
    {
        VertexShader = compile vs_2_0 CLOUDS_VS();
        PixelShader = compile ps_2_b CLOUDS_PS();
    }
}

technique SKY 
{
	pass pass0
	{
		VertexShader = compile vs_2_0 SKY_VS();
		PixelShader = compile ps_2_0 SKY_PS();
	}
}
