float4x4 mWorld;
float4x4 mView;
float4x4 mProjection;
float4x4 mWorldView;
float4x4 mWorldViewInverse;

float4 lightDirection;

float3 cameraEyePosition;

texture texture_color;
sampler sampler_color = sampler_state {
	Texture = <texture_color>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT 
{
	float3 Position		 : POSITION;
	float3 Normal		 : NORMAL;
	float2 Texture       : TEXCOORD0;
	float3 Tangent		 : TANGENT;
	float3 Binormal	     : BINORMAL;
};

struct VS_OUTPUT 
{
	float4 VS_Position : POSITION;
	float2 Texture     : TEXCOORD0;
	float3 Light       : TEXCOORD2;
    float3 View        : TEXCOORD3;
    float3 Normal	   : TEXCOORD4;
};


VS_OUTPUT vs_main(VS_INPUT IN) {
	VS_OUTPUT OUT;
	float4x4 mWorldViewProjection = mul(mWorld,mul(mView,mProjection));
	OUT.VS_Position = mul(float4(IN.Position,1.0f), mWorldViewProjection);
	OUT.Texture = IN.Texture;	
	
	OUT.Normal = IN.Normal;

    float3x3 TangentSpace = float3x3(IN.Tangent,-IN.Binormal, -IN.Normal);
    TangentSpace = transpose(TangentSpace);
    OUT.Light = mul(lightDirection,TangentSpace);  
   
    float4 temp = mul(float4(IN.Position.xyz, 1.0f), mWorldView);
    float3 vpos = mul(temp.xyz, mWorldViewInverse);
    OUT.View = mul(-vpos, TangentSpace);
    return OUT;
}


float4 ps_main(VS_OUTPUT IN) : COLOR {	
   IN.Light				 = normalize(IN.Light);
   IN.View				 = normalize(IN.View); 
  
   float4 Color			 = tex2D(sampler_color, IN.Texture);
   
   float  lightAmount	 = dot(IN.Normal, IN.Light);
   float3 vReflect		 = reflect(-IN.View,IN.Normal);
   float  specularAmount = pow(max(dot(vReflect, IN.View),0), 256); 
   float4 specularColor  = specularAmount*float4(1.0f,1.0f,1.0f,1.0f);
   Color				 = (Color + specularColor + Color*saturate(lightAmount))*min((max(lightDirection.y,-0.4f) + 0.5f),0.9f);
   Color.a				 = 1.0f; 
   return Color;
}

technique GUI {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}