const char* BasicVertexShader = STRINGIFY(

attribute vec2 texcoord_slot;                                          
attribute vec4 vertex_slot;
attribute vec4 color_slot;
varying vec4 DestinationColor;
varying vec2 texcoord_slot_out;                                          
uniform mat4 mProjection;
uniform mat4 mWorld;
                                          
void main(void)
{
    DestinationColor = color_slot;
    gl_Position = mProjection * mWorld * vertex_slot;
    texcoord_slot_out = texcoord_slot;
}
);
