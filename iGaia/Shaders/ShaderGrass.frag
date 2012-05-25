const char* ShaderGrassF = STRINGIFY(                                    
                                                    varying lowp    vec2   OUT_TexCoord;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
}
);
