const char* ShaderUnitV = STRINGIFY(
                                                    
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
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                                    uniform mat4   EXT_MATRIX_MVP_INV;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    
    OUT_Normal = IN_SLOT_Normal.xyz / 127.0 - 1.0;

    OUT_Light = normalize(EXT_Light - vec3(vWorldPosition));
    OUT_View = normalize(EXT_View - vec3(vWorldPosition));
    
    OUT_TexCoord = IN_SLOT_TexCoord;
    
	float fBlendLength = length(vWorldPosition.xyz - EXT_View);
	float fBlendFactor = (8.0 - fBlendLength) / (8.0 - 16.0);
    OUT_BlendFactor = clamp(fBlendFactor, 0.0, 1.0);
}
);
