const char* ShaderUnitF = STRINGIFY(

                                                    varying lowp    vec3   OUT_View;
                                                    varying lowp    vec3   OUT_Light;
                                                    varying lowp    vec3   OUT_Normal;                                     
                                                    varying lowp    vec2   OUT_TexCoord;
                                                    varying lowp    float  OUT_BlendFactor;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    lowp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    lowp float fDiffuseFactor = max(dot(OUT_Normal, OUT_Light), 0.0);

    vDiffuseColor.rgb = vDiffuseColor.rgb * fDiffuseFactor + vDiffuseColor.rgb * 0.66;
    gl_FragColor = vDiffuseColor;
}
);
