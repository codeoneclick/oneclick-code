const char* ShaderPreShadowMapV = STRINGIFY(
                                              
                                              attribute vec3 IN_SLOT_Position;
                                              attribute vec2 IN_SLOT_TexCoord;
                                              attribute vec4 IN_SLOT_Normal;
                                              attribute vec4 IN_SLOT_Tangent;
                                              
                                              varying vec2   OUT_TexCoord;
                                              varying float  OUT_Depth;
                                              
                                              uniform mat4   EXT_MATRIX_Projection;
                                              uniform mat4   EXT_MATRIX_View;                                          
                                              uniform mat4   EXT_MATRIX_World;
                                              uniform mat4   EXT_MATRIX_MVP_INV;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    OUT_Depth = gl_Position.z;
}
);
