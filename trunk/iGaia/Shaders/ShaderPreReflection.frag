const char* ShaderPostNormalDepthF = STRINGIFY(                                    
                                                   varying mediump vec4   OUT_Color;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    gl_FragColor = OUT_Color;
}
);
