const char* ShaderShadowPlaneF = STRINGIFY(

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
    
    /*lowp float fOffsetA = 0.33;
    lowp float fOffsetB = 0.66;
    lowp float fOffsetC = 0.99;
 
    lowp float fDiffuseFactor = max(dot(OUT_Normal, OUT_Light), 0.0);
    
    if (fDiffuseFactor < fOffsetA) fDiffuseFactor = 0.0;
    else if (fDiffuseFactor < fOffsetB) fDiffuseFactor = fOffsetB;
    else fDiffuseFactor = fOffsetC;
    
    vDiffuseColor.rgb = vDiffuseColor.rgb * fDiffuseFactor + vDiffuseColor.rgb * 0.75;*/
    vDiffuseColor.rgb = vDiffuseColor.rgb / 4.0;
    vDiffuseColor.a = vDiffuseColor.a * 4.0;
    gl_FragColor = vDiffuseColor;
}
);
