const char* ShaderPreShadowMapF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                                   varying lowp float OUT_Depth;
                                       
void main(void)
{
    gl_FragColor = vec4(OUT_Depth, 0.0, 0.0, 1.0);
}
);
