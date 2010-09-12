// COLOR TEXTURES
// Sand
Texture Texture_1;
sampler textureColorLayer0Sampler = sampler_state 
{ 
	Texture = <Texture_1>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Grass
Texture Texture_2;
sampler textureColorLayer1Sampler = sampler_state 
{ 
	Texture = <Texture_2>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Rock
Texture Texture_3;
sampler textureColorLayer2Sampler = sampler_state
{ 
	Texture = <Texture_3>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR;
	MipFilter = LINEAR; 
};
// Snow
Texture textureColorLayer3;
sampler textureColorLayer3Sampler = sampler_state 
{ 
	Texture = <textureColorLayer3>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Road
/*Texture textureColorLayer4;
sampler textureColorLayer4Sampler = sampler_state 
{ 
	Texture = <textureColorLayer4>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};*/
//  NORMAL TEXTURES 
// Sand
Texture Texture_4;
sampler textureNormalLayer0Sampler = sampler_state 
{ 
	Texture = <Texture_4>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Grass
Texture Texture_5;
sampler textureNormalLayer1Sampler = sampler_state 
{ 
	Texture = <Texture_5>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Rock
Texture Texture_6;
sampler textureNormalLayer2Sampler = sampler_state
{ 
	Texture = <Texture_6>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR;
	MipFilter = LINEAR; 
};
// Snow
Texture textureNormalLayer3;
sampler textureNormalLayer3Sampler = sampler_state 
{ 
	Texture = <textureNormalLayer3>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};
// Road
/*Texture textureNormalLayer4;
sampler textureNormalLayer4Sampler = sampler_state 
{ 
	Texture = <textureNormalLayer4>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};*/


Texture ShadowMapTexture;
sampler shadowMapSampler = sampler_state 
{ 
	Texture = <ShadowMapTexture>; 
	MagFilter = LINEAR; 
	MinFilter = LINEAR; 
	MipFilter = LINEAR; 
};

float4x4 mWorld;
float4x4 mView;
float4x4 mProjection;
float4x4 mWorldView;
float4x4 mWorldViewInverse;
float4x4 mShadowMap;

float4 light_direction;
float3 camera_position;
float3 targetPosition;

struct VS_Input
{
   float3 Position			    : POSITION;
   float3 Normal				: NORMAL;
   float2 Texture				: TEXCOORD0;
   float3 Tangent			    : TANGENT;
   float3 Binormal			    : BINORMAL;
   float4 TextureMask		    : TEXCOORD1;
   float4 TextureDecoration     : TEXCOORD2;
};

struct Vs_Output
{
   float4 Position   			: POSITION;
   float2 Texture				: TEXCOORD0;
   float4 TextureMask		    : TEXCOORD1;
   float3 Light                 : TEXCOORD2;
   float3 View                  : TEXCOORD3;
   float4 ShadowMapTexCoord	    : TEXCOORD4;
};

struct Ps_Output
{
	float4 Color      : COLOR;
};

Vs_Output vs_main(VS_Input IN)
{
   Vs_Output OUT = (Vs_Output)0;
   
   OUT.TextureMask = IN.TextureMask;
	
   float4x4 mWorldViewProjection = mul(mWorld,mul(mView,mProjection));
   OUT.Position = mul(float4(IN.Position,1.0f), mWorldViewProjection);
   
   OUT.ShadowMapTexCoord = mul(float4(IN.Position,1.0f), mShadowMap);

   OUT.Texture = IN.Texture;
   
   float3x3 TangentSpace;
   TangentSpace[0] = mul(IN.Tangent, mWorld);
   TangentSpace[1] = mul(-IN.Binormal, mWorld);
   TangentSpace[2] = mul(-IN.Normal, mWorld);
   TangentSpace = transpose(TangentSpace);
   
   OUT.Light = mul(light_direction,TangentSpace);  
   
   float4 temp = mul(float4(IN.Position.xyz, 1.0f), mWorldView);
   float3 vpos = mul(temp.xyz, mWorldViewInverse);
   OUT.View = mul(-vpos, TangentSpace);
 
   return OUT;
}

Ps_Output ps_main(Vs_Output IN)
{
   IN.Light = normalize(IN.Light);
   IN.View = normalize(IN.View);
   
   Ps_Output OUT = (Ps_Output)0;
   float texture_height_layer_01 = tex2D(textureNormalLayer0Sampler, IN.Texture).a*IN.TextureMask.r;
   float texture_height_layer_02 = tex2D(textureNormalLayer1Sampler, IN.Texture).a*IN.TextureMask.g;
   float texture_height_layer_03 = tex2D(textureNormalLayer2Sampler, IN.Texture).a*IN.TextureMask.b;
   float height_color = texture_height_layer_01 + texture_height_layer_02 + texture_height_layer_03;  
   
   float height = height_color* 0.06;
   float2 new_texture = IN.Texture +  height * -IN.View.xy;

   float3 texture_normal_layer_01 = tex2D(textureNormalLayer0Sampler, new_texture).rgb*IN.TextureMask.x;
   float3 texture_normal_layer_02 = tex2D(textureNormalLayer1Sampler, new_texture).rgb*IN.TextureMask.y;
   float3 texture_normal_layer_03 = tex2D(textureNormalLayer2Sampler, new_texture).rgb*IN.TextureMask.z;
   float3 normal_color = texture_normal_layer_01 + texture_normal_layer_02 + texture_normal_layer_03;
   
   normal_color = normalize(2*(normal_color) - 1);
   
   float4 texture_color_layer_01 = tex2D(textureColorLayer0Sampler, new_texture)*IN.TextureMask.x;
   float4 texture_color_layer_02 = tex2D(textureColorLayer1Sampler, new_texture)*IN.TextureMask.y;
   float4 texture_color_layer_03   = tex2D(textureColorLayer2Sampler, new_texture)*IN.TextureMask.z;
   float4 color = texture_color_layer_01 + texture_color_layer_02 + texture_color_layer_03; 
   
   float diffuse = dot(normal_color, IN.Light);
   float3 reflect_vector = reflect(-IN.View,normal_color);
   float specular = pow(max(dot(reflect_vector, IN.View),0), 128); 
   float4 specular_color = specular*float4(1.0f,1.0f,1.0f,1.0f);
   float4 ambient_color = color*0.8f;
	
   OUT.Color = (ambient_color + specular_color + color*diffuse)*min((max(light_direction.y,-0.4f) + 0.5f),0.9f);
   OUT.Color.rgb /= 1.0f + tex2Dproj(shadowMapSampler, IN.ShadowMapTexCoord).r*3.0f;
   OUT.Color.a = 1.0f;

   return OUT;
}

technique ground
{
   pass Pass0
   {
      VertexShader = compile vs_2_0 vs_main();
      PixelShader  = compile ps_2_0 ps_main();
   }
}