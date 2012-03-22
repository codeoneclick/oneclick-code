const char* ShaderLambertF = STRINGIFY(

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
    highp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    vDiffuseColor = vDiffuseColor * max ( dot ( OUT_Normal, OUT_Light ), 0.33 );
    gl_FragColor = vec4(1.0,0.0,0.0,1.0); //vDiffuseColor;
}
);
