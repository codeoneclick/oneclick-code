const char* ShaderWaterV = STRINGIFY(
                                              
                                              attribute vec3 IN_SLOT_Position;
                                              attribute vec2 IN_SLOT_TexCoord;
                                              
                                              varying vec4   OUT_TexCoordProj;
varying vec2   OUT_TexCoord;
                                              varying vec3   OUT_View;
                                              varying vec3   OUT_Light;
                                                
uniform vec3   EXT_View;
uniform vec3   EXT_Light;
                                              
                                              uniform mat4   EXT_MATRIX_Projection;
                                              uniform mat4   EXT_MATRIX_View;                                          
                                              uniform mat4   EXT_MATRIX_World;
                                              uniform mat4   EXT_MATRIX_MVP_INV;
                                       
void main(void)
{
    vec4 vWorldPosition = vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    
    mat3 mTangentSpace = mat3(0.0, 1.0, 0.0,
                              0.0, 0.0, 1.0,
                              1.0, 0.0, 0.0);
    
    vec3 vLightDirection = EXT_Light - vec3(vWorldPosition);
    vec3 vViewDirection = EXT_View - vec3(vWorldPosition);
    
    OUT_View = normalize(mTangentSpace * vViewDirection);
    OUT_Light = normalize(mTangentSpace * vLightDirection);
    
    OUT_TexCoord = IN_SLOT_TexCoord;
    OUT_TexCoordProj = gl_Position;
}
);
