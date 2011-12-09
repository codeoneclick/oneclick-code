const char* ShaderTextureF = STRINGIFY(

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
    gl_FragColor = texture2D(u_s_texture_01, v_out_slot_textcoord);
}
);
