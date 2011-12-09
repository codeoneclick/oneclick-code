const char* ShaderTexturePixelDiffuseSpecularColorV = STRINGIFY(
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
    mat3 mTangentSpace = mat3(u_in_slot_tangent,cross(u_in_slot_tangent,u_in_slot_normal),u_in_slot_normal);
    mTangentSpace = mat3(u_m_world[0].xyz, u_m_world[1].xyz, u_m_world[2].xyz) * mTangentSpace;
    v_v_out_view = mTangentSpace * (u_v_view - u_in_slot_vertex);
    v_v_out_light = mTangentSpace * u_v_light;
    v_out_slot_textcoord = u_in_slot_textcoord;
}
);
