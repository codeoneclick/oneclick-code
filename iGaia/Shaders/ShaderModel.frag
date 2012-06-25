const char* ShaderModelF = STRINGIFY(
                                                    varying lowp     vec3   OUT_Light;
                                                    varying lowp     vec3   OUT_Normal;                                     
                                                    varying highp    vec2   OUT_TexCoord;
                                                    uniform sampler2D EXT_TEXTURE_01;
void main(void)
{
    lowp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    lowp float fDiffuseFactor = max(dot(OUT_Normal, OUT_Light), 0.0);

    vDiffuseColor.rgb = vDiffuseColor.rgb * fDiffuseFactor + vDiffuseColor.rgb * 0.66;
    gl_FragColor = vDiffuseColor;
}
);
