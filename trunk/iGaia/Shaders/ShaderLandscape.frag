const char* ShaderLandscapeF = STRINGIFY(
                                                    varying lowp  vec3  OUT_Light;                                    
                                                    varying highp vec2  OUT_TexCoord;
                                                    varying highp vec2  OUT_SplattingTexCoord;
                                                    varying lowp float  OUT_Clip;
                                                    uniform lowp sampler2D EXT_TEXTURE_01;
                                                    uniform lowp sampler2D EXT_TEXTURE_02;
                                                    uniform lowp sampler2D EXT_TEXTURE_03;
                                                    uniform lowp sampler2D EXT_TEXTURE_04;
                                                    uniform lowp sampler2D EXT_TEXTURE_05;
                                                    uniform lowp sampler2D EXT_TEXTURE_06;
                                                    uniform lowp sampler2D EXT_TEXTURE_07;
                                                    uniform lowp sampler2D EXT_TEXTURE_08;
                                       
void main(void)
{
    if(OUT_Clip < 0.0)
          discard;

    lowp float fAmbientFactor = 0.66;
    
    lowp vec4 vSplattingColor = texture2D(EXT_TEXTURE_07, OUT_SplattingTexCoord);
    
    lowp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * vSplattingColor.x + texture2D(EXT_TEXTURE_03, OUT_TexCoord) * vSplattingColor.y + texture2D(EXT_TEXTURE_05, OUT_TexCoord) * vSplattingColor.z;
    
    lowp vec4 vAmbientColor = vDiffuseColor * fAmbientFactor;
    
    lowp vec3 vNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord).xyz * vSplattingColor.x + texture2D(EXT_TEXTURE_04, OUT_TexCoord).xyz * vSplattingColor.y + texture2D(EXT_TEXTURE_06, OUT_TexCoord).xyz * vSplattingColor.z;
    
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    lowp float fSelfShadow = clamp( 3.0 * OUT_Light.z, 0.0, 1.0);
 
    lowp float fDiffuseFactor = max(dot(vNormalColor, OUT_Light), 0.0);
    vDiffuseColor = vDiffuseColor * fDiffuseFactor;

    lowp vec4 vColor = vDiffuseColor * fSelfShadow + vAmbientColor;
    vColor.a = 1.0;
    gl_FragColor = vColor;
}
);
