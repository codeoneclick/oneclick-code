const char* ShaderPreNormalDepthUnitF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                                   varying highp vec2 OUT_TexCoord;
                                       
void main(void)
{
    lowp float fAlpha = texture2D(EXT_TEXTURE_01, OUT_TexCoord).a;
    /*if(fAlpha < 0.5)
    {
        discard;
    }
    else
    {
        fAlpha = 1.0;
    }*/
    
    gl_FragColor = vec4(1.0, 1.0, 1.0, fAlpha);
}
);
