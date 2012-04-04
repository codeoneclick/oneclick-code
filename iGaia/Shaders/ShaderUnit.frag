const char* ShaderUnitF = STRINGIFY(

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
    
    mediump vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    mediump vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    mediump vec3 vNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord).xyz;
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    vDiffuseColor = vDiffuseColor * max(dot(vNormalColor, vLight), 0.33);
    
    mediump vec3 vReflect = reflect(-vView, vNormalColor);
    vSpecularColor = vSpecularColor * pow(max(dot(vLight, vReflect),0.0),8.0);
    
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);//vDiffuseColor + vSpecularColor;
}
);
