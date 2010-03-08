float4x4 mWorld;
float4x4 mView;
float4x4 mProjection;
float4x4 mWorldView;
float4x4 mWorldViewInverse;

float4 lightDirection;
float3 cameraEyePosition;

texture textureColor;
sampler textureColorSampler = sampler_state {
	Texture = <textureColor>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture textureNormal;
sampler textureNormalSampler = sampler_state {
	Texture = <textureNormal>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT {
	float3 Position      : POSITION;
	float3 Normal		 : NORMAL;
	float2 TextureCoord  : TEXCOORD0;
	float3 Tangent		 : TANGENT;
	float3 Binormal	     : BINORMAL;
};

struct VS_OUTPUT {
   float4 Position				: POSITION;
   float2 TextureCoord			: TEXCOORD0;
   float3 Light                 : TEXCOORD1;
   float3 View                  : TEXCOORD2;
   float3 Normal				: TEXCOORD3;
   float3 Fog    				: TEXCOORD4;
};


VS_OUTPUT vs_main(VS_INPUT IN) {
 
   VS_OUTPUT OUT = (VS_OUTPUT)0;
   float4x4 mWorldViewProjection = mul(mWorld,mul(mView,mProjection));
   OUT.Position     = mul(float4(IN.Position,1.0f), mWorldViewProjection);
   OUT.TextureCoord = IN.TextureCoord;
   
   float4 d = mul(float4(IN.Position,1.0f), mul(mWorld,mView));
   float f = (768.0f - d.z)/(768.0f - 2048.0f);
   OUT.Fog = clamp(f, 0.0f, 1.0f);

   float3x3 TangentSpace;
   TangentSpace[0] = mul(IN.Tangent, mWorld);
   TangentSpace[1] = mul(-IN.Binormal, mWorld);
   TangentSpace[2] = mul(-IN.Normal, mWorld);
   TangentSpace = transpose(TangentSpace);
   OUT.Light = mul(lightDirection,TangentSpace);  
   
   float4 temp = mul(float4(IN.Position.xyz, 1.0f), mWorldView);
   float3 vpos = mul(temp.xyz, mWorldViewInverse);
   OUT.View = mul(-vpos, TangentSpace);

   return OUT;
}


float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
   IN.Light				 = normalize(IN.Light);
   IN.View				 = normalize(IN.View); 
   
   float heightColor = tex2D(textureNormalSampler, IN.TextureCoord).a;
   
   float height = heightColor* 0.06;
   float2 newTextureCoord = IN.TextureCoord +  height * -IN.View;
  
   float4 Color			 = tex2D(textureColorSampler, newTextureCoord);
  
   float3 normalColor    = tex2D(textureNormalSampler, newTextureCoord).rgb; 
   normalColor           = normalize(2*(normalColor) - 1);
   
   float  lightAmount	 = dot(normalColor, IN.Light);
   float3 vReflect		 = reflect(-IN.View,normalColor);
   float  specularAmount = pow(max(dot(vReflect, IN.View),0), 256); 
   float4 specularColor  = specularAmount*float4(1.0f,1.0f,1.0f,1.0f);
   Color				 = (Color + specularColor + Color*saturate(lightAmount))*min((max(lightDirection.y,-0.4f) + 0.5f),0.9f);
   Color.a				 = 1.0f; 
   float3 fogColor = float3(1.0f,1.0f,1.0f)*IN.Fog;
   Color.a -= fogColor;
   Color.rgb *= 0.7f; 
   return Color;
}

technique mesh {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0  ps_main();
	}
}