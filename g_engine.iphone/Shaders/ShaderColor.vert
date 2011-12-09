const char* ShaderColorV = STRINGIFY(

attribute vec3 u_in_slot_vertex;
attribute vec2 u_in_slot_textcoord;
attribute vec3 u_in_slot_normal;
attribute vec3 u_in_slot_tangent;

varying vec3   v_v_out_view;
varying vec3   v_v_out_light;
varying vec3   v_v_out_normal;                                     
varying vec2   v_out_slot_textcoord;

uniform vec3   u_v_view;
uniform vec3   u_v_light;
                                       
uniform mat4   u_m_projection;
uniform mat4   u_m_view;                                          
uniform mat4   u_m_world;
                                          
void main(void)
{
    gl_Position = u_m_projection * u_m_view * u_m_world * vec4(u_in_slot_vertex, 1.0);
}
);
