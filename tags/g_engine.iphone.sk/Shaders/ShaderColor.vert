const char* ShaderColorV = STRINGIFY(

                                     attribute vec3 IN_SLOT_Position;
                                     attribute vec2 IN_SLOT_TexCoord;
                                     attribute vec3 IN_SLOT_Normal;
                                     attribute vec4 IN_SLOT_Color;
                                     
                                     varying vec3   OUT_View;
                                     varying vec3   OUT_Light;
                                     varying vec3   OUT_Normal;                                     
                                     varying vec2   OUT_TexCoord;
                                     varying vec4   OUT_Color;
                                     
                                     uniform vec3   EXT_View;
                                     uniform vec3   EXT_Light;
                                     
                                     uniform mat4   EXT_MATRIX_Projection;
                                     uniform mat4   EXT_MATRIX_View;                                          
                                     uniform mat4   EXT_MATRIX_World;
                                          
void main(void)
{
    OUT_Color = IN_SLOT_Color;
    vec4 vPosition = EXT_MATRIX_Projection * EXT_MATRIX_View * EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = vPosition;
}
);