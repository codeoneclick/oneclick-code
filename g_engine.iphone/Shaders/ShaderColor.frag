const char* ShaderColorF = STRINGIFY(

varying mediump vec2 v_out_slot_textcoord;
varying mediump vec3 v_v_out_view;
varying mediump vec3 v_v_out_light;
varying mediump vec3 v_v_out_normal;    
uniform mediump vec4 u_v_color;
uniform sampler2D u_s_texture_01;
uniform sampler2D u_s_texture_02;
uniform sampler2D u_s_texture_03;
uniform sampler2D u_s_texture_04;
                                     
void main(void)
{
    gl_FragColor = vec4(u_v_color.x, u_v_color.y, u_v_color.z, 1.0);
}
);
