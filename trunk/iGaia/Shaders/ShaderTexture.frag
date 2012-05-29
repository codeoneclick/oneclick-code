const char* ShaderTextureF = STRINGIFY(

                                       varying mediump vec3   OUT_View;
                                       varying mediump vec3   OUT_Light;
                                       varying mediump vec3   OUT_Normal;                                     
                                       varying highp   vec2   OUT_TexCoord;
                                       uniform sampler2D EXT_TEXTURE_01;
                                       uniform sampler2D EXT_TEXTURE_02;
                                       uniform sampler2D EXT_TEXTURE_03;
                                       uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
}
);
