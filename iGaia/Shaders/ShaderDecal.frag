const char* ShaderDecalF = STRINGIFY(                                    
                                                    varying lowp    vec2   OUT_TexCoord;
                                                    varying highp   vec3   OUT_Position;
                                                    uniform highp   vec3   EXT_Center;
                                                    uniform highp   float  EXT_Angle;
                                                    uniform sampler2D EXT_TEXTURE_01;                                
void main(void)
{
    lowp float fRadius = 2.0;
    lowp vec3 UVector = vec3(1.0, 0.0, 0.0) / (fRadius);
    lowp vec3 VVector = vec3(0.0, 0.0, 1.0) / (fRadius);
    lowp vec2 vTexCoord;
    vTexCoord.x = dot(OUT_Position - EXT_Center, UVector);
    vTexCoord.y = dot(OUT_Position - EXT_Center, VVector);
    
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
    gl_FragColor = texture2D(EXT_TEXTURE_01, vTransformTexCoord.xy);
}
);
