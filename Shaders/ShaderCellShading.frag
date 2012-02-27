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
    highp vec4  vDiffuseColor = vec4( 0.0, 0.0, 0.5, 1.0 );
    highp float fDiffuseFactor = 0.2 + max ( dot ( OUT_Normal, OUT_Light ), 0.0 );
    
    if ( fDiffuseFactor < 0.3 )
        vDiffuseColor = vDiffuseColor * 0.1;
    else
    if ( fDiffuseFactor < 0.7 )
        vDiffuseColor = vDiffuseColor * 0.5;
    else
    if ( fDiffuseFactor < 0.8 )
        vDiffuseColor = vDiffuseColor;
    else
        vDiffuseColor = vDiffuseColor * 1.3;
    
    gl_FragColor = vDiffuseColor;
}
);
