const char* ShaderColorF = STRINGIFY(

varying mediump vec2 u_out_slot_textcoord;
uniform lowp vec4 u_v_color;
                                     
void main(void)
{
   gl_FragColor = u_v_color;
}
);
