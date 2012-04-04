const char* ShaderParallaxF = STRINGIFY(

                                                    varying highp   vec3   OUT_View;
                                                    varying highp   vec3   OUT_Light;
                                                    varying highp   vec3   OUT_Normal;                                     
                                                    varying mediump vec2   OUT_TexCoord;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform sampler2D EXT_TEXTURE_02;
                                                    uniform sampler2D EXT_TEXTURE_03;
                                                    uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    mediump vec3 vLight = normalize(OUT_Light);
    mediump vec3 vView = normalize(OUT_View);
    
    mediump float fHeight = texture2D(EXT_TEXTURE_03, OUT_TexCoord).r;
    fHeight = fHeight * 0.03;
    mediump vec2 vTexCoord = OUT_TexCoord + fHeight * vView.xy;
    
    mediump vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, vTexCoord);
    mediump vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    mediump vec3 vNormalColor = texture2D(EXT_TEXTURE_02, vTexCoord).xyz;
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    vDiffuseColor = vDiffuseColor * max(dot(vNormalColor, vLight), 0.33);
    
    mediump vec3 vReflect = reflect(-vView, vNormalColor);
    vSpecularColor = vSpecularColor * pow(max(dot(vLight, vReflect),0.0),8.0);
    
    gl_FragColor = vDiffuseColor;// + vSpecularColor;
}
);
