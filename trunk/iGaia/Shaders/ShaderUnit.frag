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
    highp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    
    /*if(vDiffuseColor.a == 0.0)
    {
        discard;
    }*/
    
    lowp float fOffsetA = 0.33;
    lowp float fOffsetB = 0.66;
    lowp float fOffsetC = 0.99;
    //lowp float fOffsetD = 0.8;
 
    /*lowp float fDiffuseFactor = max(dot(OUT_Normal, OUT_Light), 0.0);
    
    if (fDiffuseFactor < fOffsetA) fDiffuseFactor = 0.0;
    else if (fDiffuseFactor < fOffsetB) fDiffuseFactor = fOffsetB;
    else fDiffuseFactor = fOffsetC;
    //else fDiffuseFactor = fOffsetD;
    
    vDiffuseColor.rgb = vDiffuseColor.rgb * fDiffuseFactor + vDiffuseColor.rgb * 0.75;*/
    gl_FragColor = vDiffuseColor;
}
);
