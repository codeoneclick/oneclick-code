const char* ShaderWaterV = STRINGIFY(
                                              
                                              attribute vec3 IN_SLOT_Position;
                                              attribute vec2 IN_SLOT_TexCoord;
                                              
                                              varying vec4   OUT_TexCoordProj;
                                              varying vec2   OUT_TexCoord;  
                                              
                                              uniform mat4   EXT_MATRIX_Projection;
                                              uniform mat4   EXT_MATRIX_View;                                          
                                              uniform mat4   EXT_MATRIX_World;
                                    
void main(void)
{
    vec4 vWorldPosition = vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    
    OUT_TexCoord = IN_SLOT_TexCoord;
    OUT_TexCoordProj = gl_Position;
}
);
