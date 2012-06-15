const char* ShaderParticleEmitterF = STRINGIFY(                                  
                                                    varying highp    vec2   OUT_TexCoord;
                                                    uniform highp    float  EXT_Alpha;
                                                    varying highp    vec4   OUT_Color;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    highp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * OUT_Color;
}
);
