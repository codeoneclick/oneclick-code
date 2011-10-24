const char* SimpleVertexShader = STRINGIFY(

attribute vec4 vertex_slot;
attribute vec4 color_slot;
varying vec4 DestinationColor;
uniform mat4 Projection;
uniform mat4 Modelview;

void main(void)
{
    DestinationColor = color_slot;
    gl_Position = Projection * Modelview * vertex_slot;
}
);
