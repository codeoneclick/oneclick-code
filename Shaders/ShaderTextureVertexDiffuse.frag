const char* ShaderTextureVertexDiffuseF = STRINGIFY(

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
    highp vec4 vSpecularColor = vec4(0.7, 0.7, 0.7, 1.0);
    highp vec3 vReflect = reflect(-OUT_View, OUT_Normal);
    
    vDiffuseColor = vDiffuseColor * max ( dot ( OUT_Normal, OUT_Light ), 0.0 );
    vSpecularColor = vSpecularColor * pow ( max ( dot ( OUT_Light, vReflect ), 0.0 ), 16.0 );
    
    gl_FragColor = vDiffuseColor + vSpecularColor;
}
);
