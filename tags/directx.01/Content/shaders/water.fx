float timer;
float4x4 matrix_world_view_projection;
float4x4 matrix_world;
float4x4 matrix_reflection;

float bump_heigth = 4.0f;

float2 tile_scale = { 3.0f, 3.0f };

//float3 light_position;
float4 light_direction;
float3 camera_position;

Texture normalMap;
sampler2D samplerNormal = sampler_state {
	Texture = (normalMap);
	MipFilter 	= Linear;
	MinFilter 	= Linear;
	MagFilter 	= Linear;
};

Texture models_reflection_texture;
sampler2D samplerModels = sampler_state {
	Texture = (models_reflection_texture);
	MinFilter 	= Linear;
	MagFilter 	= Linear;
	MipFilter 	= Linear;
};

struct VS_INPUT {
	float3 Position : POSITION;
	float2 Texture  : TEXCOORD0;
};

struct VS_OUTPUT {
	float4   Position	          : POSITION;
	float2   Texture	          : TEXCOORD0;
	float4   ReflectTexture	      : TEXCOORD2;
	float3x3 TangentSpace         : TEXCOORD3;
	float3   View		          : TEXCOORD6;
	float3   Light	              : TEXCOORD7;
};

 
VS_OUTPUT vs_main(VS_INPUT IN) {
	
	VS_OUTPUT OUT;
		
	OUT.Position =  mul(float4(IN.Position,1.0f), matrix_world_view_projection );

	OUT.Texture = IN.Texture;
	
	OUT.ReflectTexture = mul(mul(float4(IN.Position,1.0f), matrix_world), matrix_reflection);

    float3 Binormal = float3( 1.0f,  0.0f, 0.0f );
    float3 Tangent  = float3( 0.0f,  0.0f, 1.0f );
    float3 Normal   = float3( 0.0f,  1.0f, 0.0f );
    
	float3x3 matrix_tangent = float3x3(bump_heigth * Tangent,bump_heigth * Binormal, Normal );
	
	OUT.TangentSpace[0].xyz = mul( matrix_tangent, matrix_world[0].xyz );
	OUT.TangentSpace[1].xyz = mul( matrix_tangent, matrix_world[1].xyz );
	OUT.TangentSpace[2].xyz = mul( matrix_tangent, matrix_world[2].xyz );
	
	float4 world_position = mul(IN.Position, matrix_world);
    OUT.View  = mul(OUT.TangentSpace, float4(camera_position,1.0f) - world_position);
    OUT.Light = mul(OUT.TangentSpace, light_direction);
	return OUT;
}		

float4 ps_main( VS_OUTPUT IN ) : COLOR0 {

	IN.Light = normalize(IN.Light);
	IN.View = normalize(IN.View);
	
	float2 textcoord_01 = float2(IN.Texture.x*8.0f + sin(timer+IN.Texture.x*8.0f)*0.05f,
								 IN.Texture.y*8.0f + cos(timer+IN.Texture.y*8.0f)*0.07f);
	
	float2 textcoord_02 = float2(IN.Texture.x*8.0f - sin(timer+IN.Texture.x*8.0f)*0.07f,
								 IN.Texture.y*8.0f - cos(timer+IN.Texture.y*8.0f)*0.05f);
	
	//IN.Texture.x += sin(timer+IN.Texture.x*32.0f)*0.1f;
	//IN.Texture.y += cos(timer+IN.Texture.y*32.0f)*0.1f;


	float3 normal_color_01 = tex2D( samplerNormal, textcoord_01 ) * 2.0f - 1.0f;
    float3 normal_color_02 = tex2D( samplerNormal, textcoord_02 ) * 2.0f - 1.0f;

    float3 normal_color = normal_color_01 + normal_color_02;
    
    normal_color = mul(IN.TangentSpace, normal_color);
	normal_color = normalize(normal_color);

	IN.ReflectTexture.xy += normal_color*1.48f;

	float4 reflect_color = tex2Dproj( samplerModels, IN.ReflectTexture); 

    float Facing  = 1.0 - max(dot(IN.View, normal_color),0.0f);

	normal_color.g = -normal_color.g;
	
	float Diffuse = saturate(dot(normal_color.rgb, IN.Light));
	float4 water_color = float4(0.27f, 0.35f, 0.77f, 1.0f)*Diffuse;
	
	float sun_angle = light_direction.y;

    if(sun_angle < 0.0f)
		sun_angle = 0.0f;
	
	float Specular = pow(saturate(dot(normal_color.rgb, float3(0.0f,-1.0f,0.0f))), 256.0f);//*sun_angle;

    float4 Color = reflect_color + Specular;
	Color.a = 0.7f;

	return Color;
}

technique techDefault {
	pass Pass0 {
		VertexShader	= compile vs_2_0 vs_main();
		PixelShader		= compile ps_2_0 ps_main();
	}
}
