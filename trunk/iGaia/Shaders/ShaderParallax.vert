const char* ShaderParallaxV = STRINGIFY(
                                                    
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Normal;
                                                    attribute vec4 IN_SLOT_Tangent;
                                                    
                                                    varying vec3   OUT_View;
                                                    varying vec3   OUT_Light;
                                                    varying vec3   OUT_Normal;                                     
                                                    varying vec2   OUT_TexCoord;
                                                    
                                                    uniform vec3   EXT_View;
                                                    uniform vec3   EXT_Light;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                                    uniform mat4   EXT_MATRIX_MVP_INV;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    
    vec3 vNormal = IN_SLOT_Normal.xyz / 127.0 - 1.0;
    vec3 vTangent = IN_SLOT_Tangent.xyz / 127.0 - 1.0;
    vec3 vBinormal = cross(vNormal, vTangent);
    
    vNormal = mat3(EXT_MATRIX_World) * vNormal;
    vTangent = mat3(EXT_MATRIX_World) * vTangent; 
    vBinormal = mat3(EXT_MATRIX_World) * vBinormal;
    
    mat3 mTangentSpace = mat3(vTangent.x, vBinormal.x, vNormal.x,
                              vTangent.y, vBinormal.y, vNormal.y,
                              vTangent.z, vBinormal.z, vNormal.z);

    vec3 vLightDirection = EXT_Light - vec3(vWorldPosition);
    vec3 vViewDirection = EXT_View - vec3(vWorldPosition);
    
    OUT_View = mTangentSpace * vViewDirection;
    OUT_Light = mTangentSpace * vLightDirection;
    
    OUT_TexCoord = IN_SLOT_TexCoord;
   
}
);
