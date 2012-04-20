const char* ShaderPreNormalDepthUnitF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                                   varying lowp vec2 OUT_TexCoord;
                                       
void main(void)
{
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
);
