float4x4 matrix_world_view_projection;

float blend_near = 1024.0f;
float blend_far  = 1536.0f;

float4 light_direction;

float3 camera_position;

float timer = 0.0f;

texture grassTexture_01;
sampler grassSampler_01 = sampler_state {
	Texture = <grassTexture_01>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture grassTexture_02;
sampler grassSampler_02 = sampler_state {
	Texture = <grassTexture_02>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture grassTexture_03;
sampler grassSampler_03 = sampler_state {
	Texture = <grassTexture_03>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture grassTexture_04;
sampler grassSampler_04 = sampler_state {
	Texture = <grassTexture_04>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT {
	float3 Position : POSITION;
	float3 Normal   : NORMAL;
	float2 Texture  : TEXCOORD0;
};

struct VS_OUTPUT {
	float4 VS_Position : POSITION;
	float2 Texture     : TEXCOORD0;
	float3 Normal      : TEXCOORD1;
	float4 Position    : TEXCOORD2;
	float  GrassType   : TEXCOORD3;
	float3 Light       : TEXCOORD4;
    float3 View        : TEXCOORD5;
};


VS_OUTPUT vs_main(VS_INPUT IN) {
	VS_OUTPUT OUT;
	float angleX = IN.Position.z*IN.Position.y - (int)IN.Position.z*IN.Position.y;
	float angleZ = IN.Position.x - (int)IN.Position.x;
	if( IN.Texture.y == 0.0f )  
	{
		IN.Position.x += sin(timer*angleX/100.0f)*2.0f;
		IN.Position.z += cos(timer*angleZ/100.0f)*6.0f;
	}

	OUT.VS_Position = mul(float4(IN.Position,1.0f), matrix_world_view_projection);
	OUT.Position = float4(IN.Position,1.0f);
	OUT.Normal = IN.Normal;
	OUT.Texture = IN.Texture;	
	OUT.GrassType = IN.Position.y;
	OUT.Light = light_direction.xyz;
    OUT.View = camera_position - IN.Position;
	return OUT;
}


float4 ps_main(VS_OUTPUT IN) : COLOR 
{	
   float4 color = float4(0.0f,0.0f,0.0f,0.0f);// = tex2D(grassSampler_01 , IN.Texture); 
   //if(IN.GrassType < 144.0f)
   color = tex2D(grassSampler_02,IN.Texture);
   //if(IN.GrassType >= 144.0f && IN.GrassType < 160.0f)
	//	color = tex2D(grassSampler_03,IN.Texture);
   //if(IN.GrassType >= 160.0f && IN.GrassType < 176.0f)
	//	color = tex2D(grassSampler_02,IN.Texture);
   //if(IN.GrassType >= 176.0f)
	//	color = tex2D(grassSampler_01,IN.Texture);
		
		
   IN.Light = normalize(IN.Light);
   IN.View = normalize(IN.View);
   
   float4 OUTcolor;
   
   float diffuse = dot(IN.Normal, IN.Light);
   float3 reflect_vector = reflect(-IN.View,IN.Normal);//normalize(2 * diffuse * IN.Normal - IN.Light); 
   float specular = pow(max(dot(reflect_vector, IN.View),0), 128); 
   float4 specular_color = specular*float4(1.0f,1.0f,1.0f,1.0f);
   float4 ambient_color = color;
   
   //float sun_angle = light_direction.y;
   
   //if(sun_angle < 0.1f)
  // {
	//	sun_angle = 0.1f;
  // }
   
   OUTcolor = color*min((max(light_direction.y,-0.4f) + 0.5f),0.9f);//(ambient_color + specular_color + color*diffuse)*sun_angle;
   OUTcolor.a = color.a;  
   
   
  
   //float diffuse = (saturate(dot(-IN.Normal, light_direction)) + 0.15f)*light_direction.y;
   
   //float4 ambient_color = float4(0.1f, 0.1f, 0.1f, 1.0f);
   
   //color.rgb *= diffuse;
  // color.rgb += ambient_color.rgb;
   
  // float blend_distance = length(IN.Position-camera_position);
  // if ((blend_distance > blend_near) && (color.a > 0.5))
	//   color.a = 1.0f - (blend_distance - blend_near)/(blend_far - blend_near);
   
   //color.g = 1.0f;
    
   return OUTcolor;
}

technique grass {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}