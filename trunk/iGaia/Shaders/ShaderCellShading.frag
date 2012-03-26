const char* ShaderCellShadingF = STRINGIFY(

                                                   varying mediump vec3   OUT_View;
                                                   varying mediump vec3   OUT_Light;
                                                   varying mediump vec3   OUT_Normal;                                     
                                                   varying mediump vec2   OUT_TexCoord;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    mediump float fOffsetA = 0.1;
    mediump float fOffsetB = 0.3;
    mediump float fOffsetC = 0.6;
    mediump float fOffsetD = 1.0;
    
    mediump vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    mediump vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    
    mediump vec3 vNormal = normalize(OUT_Normal);
    mediump vec3 vLight = normalize(OUT_Light);
    mediump vec3 vView = normalize(OUT_View);
    mediump vec3 vHalf = normalize(vLight + vView);
 
    mediump float fDiffuseFactor  = max(0.0, dot(vNormal, vLight));
    
    if (fDiffuseFactor < fOffsetA) fDiffuseFactor = 0.0;
    else if (fDiffuseFactor < fOffsetB) fDiffuseFactor = fOffsetB;
    else if (fDiffuseFactor < fOffsetC) fDiffuseFactor = fOffsetC;
    else fDiffuseFactor = fOffsetD;

    mediump float fSpecularFactor = max(0.0, dot(vNormal, vHalf));
    fSpecularFactor = pow(fSpecularFactor, 128.0);
    fSpecularFactor = fSpecularFactor < 0.5 ? 0.0 : 1.0;
 
    mediump vec4 vColor = vDiffuseColor * 0.33 + fDiffuseFactor * vDiffuseColor + fSpecularFactor * vDiffuseColor;
    vColor.w = 1.0;
    gl_FragColor = vColor;
}
);
