const char* BasicVertexShader = STRINGIFY(

attribute vec3 vertex_slot;
attribute vec2 texcoord_slot;                                          
attribute vec4 color_slot;
varying vec4 DestinationColor;
varying vec2 texcoord_slot_out;                                          
uniform mat4 mProjection;
uniform mat4 mView;                                          
uniform mat4 mWorld;
                                          
void main(void)
{
    DestinationColor = color_slot;
    gl_Position = mProjection * mView * mWorld * vec4(vertex_slot, 1.0);
    texcoord_slot_out = texcoord_slot;
}
);
