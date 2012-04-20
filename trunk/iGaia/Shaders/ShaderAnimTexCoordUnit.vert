const char* ShaderAnimTexCoordUnitV = STRINGIFY(
                                                    
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Normal;
                                                    attribute vec4 IN_SLOT_Tangent;
                                                    
                                                    varying vec3   OUT_View;
                                                    varying vec3   OUT_Light;
                                                    varying vec3   OUT_Normal;                                     
                                                    varying vec2   OUT_TexCoord;
                                                    varying float  OUT_BlendFactor;
                                                    
                                                    uniform vec3   EXT_View;
                                                    uniform vec3   EXT_Light;
                                                    uniform vec2   EXT_Texcoord_Offset;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                                    uniform mat4   EXT_MATRIX_MVP_INV;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    OUT_TexCoord = vec2(IN_SLOT_TexCoord.x + EXT_Texcoord_Offset.x, IN_SLOT_TexCoord.y + EXT_Texcoord_Offset.y);
}
);
