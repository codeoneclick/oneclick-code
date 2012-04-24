const char* ShaderLandscapeF = STRINGIFY(

                                                    varying lowp vec3   OUT_View;
                                                    varying lowp vec3   OUT_Light;                                    
                                                    varying highp vec2  OUT_TexCoord;
                                                    varying highp vec2  OUT_SplattingTexCoord;
                                                    varying highp vec4  OUT_ProjTexCoord;
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
    lowp vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    lowp vec3 vNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord).xyz * vSplattingColor.x + texture2D(EXT_TEXTURE_04, OUT_TexCoord).xyz * vSplattingColor.y + texture2D(EXT_TEXTURE_06, OUT_TexCoord).xyz * vSplattingColor.z;
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    lowp float fSelfShadow = clamp( 3.0 * OUT_Light.z, 0.0, 1.0);
    
    lowp float fOffsetA = 0.15;
    lowp float fOffsetB = 0.30;
    lowp float fOffsetC = 0.45;
    lowp float fOffsetD = 0.60;
 
    lowp float fDiffuseFactor = max(dot(vNormalColor, OUT_Light), 0.0);
    
    if (fDiffuseFactor < fOffsetA) fDiffuseFactor = 0.0;
    else if (fDiffuseFactor < fOffsetB) fDiffuseFactor = fOffsetB;
    else if (fDiffuseFactor < fOffsetC) fDiffuseFactor = fOffsetC;
    else fDiffuseFactor = fOffsetD;
    
    vDiffuseColor = vDiffuseColor * fDiffuseFactor;
    
    highp vec2 vTexCoordProj = OUT_ProjTexCoord.xy;
    vTexCoordProj.x = 0.5 + 0.5 * vTexCoordProj.x / OUT_ProjTexCoord.w;
    vTexCoordProj.y = 0.5 + 0.5 * vTexCoordProj.y / OUT_ProjTexCoord.w;
    vTexCoordProj = clamp(vTexCoordProj, 0.001, 0.999);

    lowp vec4 vShadowMapColor = texture2D(EXT_TEXTURE_08, vTexCoordProj);

    lowp vec4 vColor = vDiffuseColor * fSelfShadow + vAmbientColor;
    vColor.a = 1.0;
    gl_FragColor = vColor;
}
);
