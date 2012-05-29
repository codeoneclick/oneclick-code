const char* ShaderUnitF = STRINGIFY(

                                                    varying highp    vec3   OUT_View;
                                                    varying highp    vec3   OUT_Light;
                                                    varying highp    vec3   OUT_Normal;                                     
                                                    varying highp    vec2   OUT_TexCoord;
                                                    varying highp    float  OUT_BlendFactor;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    highp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    highp float fDiffuseFactor = max(dot(OUT_Normal, OUT_Light), 0.0);

    vDiffuseColor.rgb = vDiffuseColor.rgb * fDiffuseFactor + vDiffuseColor.rgb * 0.66;
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
}
);
