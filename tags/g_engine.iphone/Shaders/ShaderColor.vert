const char* ShaderColorV = STRINGIFY(

attribute vec3 u_in_slot_vertex;
attribute vec2 u_in_slot_textcoord;                                          
varying vec2   u_out_slot_textcoord;                                          
uniform mat4   u_m_projection;
uniform mat4   u_m_view;                                          
uniform mat4   u_m_world;
                                          
void main(void)
{
    gl_Position = u_m_projection * u_m_view * u_m_world * vec4(u_in_slot_vertex, 1.0);
    u_out_slot_textcoord = u_in_slot_textcoord;
}
);
