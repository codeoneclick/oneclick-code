const char* ShaderColorF = STRINGIFY(

                                     varying mediump vec3   OUT_View;
                                     varying mediump vec3   OUT_Light;
                                     varying mediump vec3   OUT_Normal;                                     
                                     varying mediump vec2   OUT_TexCoord;
                                     varying mediump vec4   OUT_Color;
                                     uniform sampler2D EXT_TEXTURE_01;
                                     uniform sampler2D EXT_TEXTURE_02;
                                     uniform sampler2D EXT_TEXTURE_03;
                                     uniform sampler2D EXT_TEXTURE_04;
                                     
void main(void)
{
    lowp vec4 vColor = OUT_Color;
    vColor.w = 0.33;
    gl_FragColor = vColor;
}
);
