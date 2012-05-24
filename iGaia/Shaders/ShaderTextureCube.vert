const char* ShaderTextureCubeV = STRINGIFY(
                                                    
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Normal;
                                                    attribute vec4 IN_SLOT_Tangent;
                                                                                         
                                                    varying vec3   OUT_TexCoord;
                                                    
                                                    uniform vec3   EXT_View;
                                                    uniform vec3   EXT_Light;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                                    uniform mat4   EXT_MATRIX_MVP_INV;
  
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    OUT_TexCoord = IN_SLOT_TexCoord;
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
}
);