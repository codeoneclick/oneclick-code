const char* ShaderPreNormalDepthParticleEmitterF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                                   varying highp vec2 OUT_TexCoord;
                                                   varying highp vec4 OUT_Color;
                                       
void main(void)
{
    gl_FragColor = vec4(1.0, 1.0, 1.0, texture2D(EXT_TEXTURE_01, OUT_TexCoord).a) * OUT_Color;
}
);
