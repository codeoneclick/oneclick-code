const char* ShaderTexturePixelDiffuseSpecularColorF = STRINGIFY(

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
    highp vec3  vDiffuceColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord).xyz;
    highp vec3  vWarmColor = vec3 ( 0.6, 0.6, 0.0 );
    highp vec3  vColdColor = vec3 ( 0.0, 0.0, 0.6 );
    highp float fDiffuseWarm  = 0.45;
    highp float fDiffuseCold  = 0.45;
    
    highp vec3  vCold  = min ( vColdColor + fDiffuseCold * vDiffuceColor, 1.0 );
    highp vec3  vWarm  = min ( vWarmColor + fDiffuseWarm * vDiffuceColor, 1.0 );
    highp float fDiffucePower =  max ( dot ( OUT_Normal, OUT_Light ), 0.0);
    highp vec3  vFinal = mix ( vCold, vWarm, fDiffucePower );
    highp vec3  vReflect = reflect(-OUT_View, OUT_Normal);
    highp float fSpecularFactor = pow ( max ( dot ( vReflect, OUT_View ), 0.0 ), 32.0 );
    
    gl_FragColor = vec4 ( min ( vFinal + fSpecularFactor, 1.0 ), 1.0 );
}
);
