const char* ShaderDecalF = STRINGIFY(

                                                    varying lowp    vec3   OUT_View;
                                                    varying lowp    vec3   OUT_Light;
                                                    varying lowp    vec3   OUT_Normal;                                     
                                                    varying lowp    vec2   OUT_TexCoord;
                                                    varying highp   vec3   OUT_WorldPosition;
                                                    uniform highp   vec3   EXT_CenterPosition;
                                                    uniform highp   float  EXT_Angle;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    lowp float fRadius = 2.0;
    lowp vec3 UVector = vec3(1.0, 0.0, 0.0) / (2.0 * fRadius);
    lowp vec3 VVector = vec3(0.0, 0.0, 1.0) / (2.0 * fRadius);
    lowp vec2 vTexCoord;
    vTexCoord.x = dot(OUT_WorldPosition - EXT_CenterPosition, UVector);
    vTexCoord.y = dot(OUT_WorldPosition - EXT_CenterPosition, VVector);
    
    lowp mat3 mRotationMatrix = mat3(cos(EXT_Angle), -sin(EXT_Angle), 0.0,
                                     sin(EXT_Angle),  cos(EXT_Angle), 0.0,
                                     0.0           ,  0.0           , 1.0);
    
    lowp mat3 mTranslationMatrix = mat3(1.0, 0.0, 0.5,
                                        0.0, 1.0, 0.5,
                                        0.0, 0.0, 1.0);
    
    lowp mat3 mScaleMatrix = mat3(0.5, 0.0, 0.0,
                                  0.0, 0.5, 0.0,
                                  0.0, 0.0, 1.0);
    
    lowp vec3 vTransformTexCoord = vec3(vTexCoord.x, vTexCoord.y, 1.0);
    
    vTransformTexCoord = vTransformTexCoord * mScaleMatrix * mRotationMatrix * mTranslationMatrix;
    lowp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, vTransformTexCoord.xy);
    gl_FragColor = vDiffuseColor;
}
);
