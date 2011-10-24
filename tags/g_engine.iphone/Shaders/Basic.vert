const char* BasicVertexShader = STRINGIFY(

attribute vec4 vertex_slot;
attribute vec4 color_slot;
varying vec4 DestinationColor;
uniform mat4 mProjection;
uniform mat4 mWorld;

void main(void)
{
    DestinationColor = color_slot;
    gl_Position = mProjection * mWorld * vertex_slot;
}
);
