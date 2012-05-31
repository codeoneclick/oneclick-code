const char* ShaderTextureVertexDiffuseV = STRINGIFY(
                                                    
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec3 IN_SLOT_Normal;
                                                    
                                                    varying vec3   OUT_View;
                                                    varying vec3   OUT_Light;
                                                    varying vec3   OUT_Normal;                                     
                                                    varying vec2   OUT_TexCoord;
                                                    
                                                    uniform vec3   EXT_View;
                                                    uniform vec3   EXT_Light;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    OUT_Light = normalize(EXT_Light);
    OUT_View = normalize(EXT_View - vec3(vWorldPosition));
    OUT_Normal = (EXT_MATRIX_World * vec4(IN_SLOT_Normal, 1.0)).xyz;
    OUT_TexCoord = IN_SLOT_TexCoord;
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
}
);