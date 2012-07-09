const char* ShaderLandscapeF = STRINGIFY(
                                                    varying highp vec3  OUT_Light;                                    
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

    /*lowp float fAmbientFactor = 0.33;
    
    lowp vec4 vSplattingColor = texture2D(EXT_TEXTURE_07, OUT_SplattingTexCoord);
    
    lowp vec4 vDiffuseColor = vec4(0.0, 0.0, 0.0, 1.0);
    lowp vec3 vNormalColor = vec3(0.0, 0.0, 0.0);
    
    if(vSplattingColor.x > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_01, OUT_TexCoord) * vSplattingColor.x;
        vNormalColor = vNormalColor + texture2D(EXT_TEXTURE_02, OUT_TexCoord).xyz * vSplattingColor.x;
    }
    if(vSplattingColor.y > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_03, OUT_TexCoord) * vSplattingColor.y;
        vNormalColor = vNormalColor + texture2D(EXT_TEXTURE_04, OUT_TexCoord).xyz * vSplattingColor.y;
    }
    if(vSplattingColor.z > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_05, OUT_TexCoord) * vSplattingColor.z;
        vNormalColor = vNormalColor + texture2D(EXT_TEXTURE_06, OUT_TexCoord).xyz * vSplattingColor.z;
    }
    
    lowp vec4 vAmbientColor = vDiffuseColor * fAmbientFactor;
    
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    lowp float fSelfShadow = clamp( 3.0 * OUT_Light.z, 0.0, 1.0);
 
    lowp float fDiffuseFactor = max(dot(vNormalColor, OUT_Light), 0.0);
    vDiffuseColor = vDiffuseColor * fDiffuseFactor;

    lowp vec4 vColor = vDiffuseColor * fSelfShadow + vAmbientColor;
    gl_FragColor = vColor;*/
    gl_FragColor = texture2D(EXT_TEXTURE_07, OUT_SplattingTexCoord);
}
);
