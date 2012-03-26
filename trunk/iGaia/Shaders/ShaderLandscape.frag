const char* ShaderLandscapeF = STRINGIFY(

                                                    varying lowp vec3   OUT_View;
                                                    varying lowp vec3   OUT_Light;                                    
                                                    varying lowp vec2   OUT_TexCoord;
                                                    varying lowp vec2   OUT_SplattingTexCoord;
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
    lowp float fAmbientFactor = 0.33;
    
    lowp vec4 vSplattingColor = texture2D(EXT_TEXTURE_07, OUT_SplattingTexCoord);
    
    lowp vec4 vDiffuseColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * vSplattingColor.x + texture2D(EXT_TEXTURE_03, OUT_TexCoord) * vSplattingColor.y + texture2D(EXT_TEXTURE_05, OUT_TexCoord) * vSplattingColor.z;
    lowp vec4 vAmbientColor = vDiffuseColor * fAmbientFactor;
    lowp vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    lowp vec3 vNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord).xyz * vSplattingColor.x + texture2D(EXT_TEXTURE_04, OUT_TexCoord).xyz * vSplattingColor.y + texture2D(EXT_TEXTURE_06, OUT_TexCoord).xyz * vSplattingColor.z;
    vNormalColor = normalize(vNormalColor * 2.0 - 1.0);
    
    lowp float fSelfShadow = clamp( 3.0 * OUT_Light.z, 0.0, 1.0);
    
    vDiffuseColor = vDiffuseColor * max(dot(vNormalColor, OUT_Light), 0.0);
    
    //lowp vec3 vReflect = reflect(-vView, vNormalColor);
    //vSpecularColor = vSpecularColor * pow(max(dot(vLight, vReflect), 0.0), 8.0);
    lowp vec4 vColor = vDiffuseColor * fSelfShadow + vAmbientColor;
    vColor.a = 1.0;
    gl_FragColor = vColor;// + vSpecularColor;
}
);
