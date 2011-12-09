const char* ShaderTexturePixelDiffuseSpecularTextureF = STRINGIFY(

varying mediump vec2 v_out_slot_textcoord;
varying mediump vec3 v_v_out_view;
varying mediump vec3 v_v_out_light;
varying mediump vec3 v_v_out_normal;    
uniform lowp vec4 u_v_color;
uniform sampler2D u_s_texture_01;
uniform sampler2D u_s_texture_02;
uniform sampler2D u_s_texture_03;
uniform sampler2D u_s_texture_04;
                                       
void main(void)
{
    mediump vec3 v_light = normalize(v_v_out_light);
    mediump vec3 v_view  = normalize(v_v_out_view);
    
    mediump vec4 normal_color = texture2D(u_s_texture_02, v_out_slot_textcoord) * 2.0 - 1.0;
    normal_color = normalize(normal_color);
    mediump vec4 specular_color = texture2D(u_s_texture_03, v_out_slot_textcoord) * pow(dot(normalize(-reflect(v_view,normal_color.xyz)), v_light), 4.0);
    gl_FragColor = texture2D(u_s_texture_01, v_out_slot_textcoord) * dot(v_light,normal_color.xyz) + specular_color * dot(v_light,normal_color.xyz);
}
);
