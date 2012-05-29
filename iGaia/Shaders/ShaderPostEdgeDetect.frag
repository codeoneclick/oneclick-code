const char* ShaderPostEdgeDetectF = STRINGIFY(                                    
                                                   varying highp vec2   OUT_TexCoord;
                                                   varying highp vec4   OUT_TexCoord_01;
                                                   varying highp vec4   OUT_TexCoord_02;
                                                   varying highp vec4   OUT_TexCoord_03;
                                                   varying highp vec4   OUT_TexCoord_04;

                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    highp vec4 n1 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.xy);
    highp vec4 n2 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.zw);
    highp vec4 n3 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.xy);
    highp vec4 n4 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.zw);
    
    highp vec4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);
    
    highp float normalDelta = dot(diagonalDelta.xyz, vec3(1.0));
    highp float edgeAmount = clamp(normalDelta, 0.0, 1.0);
    
    highp vec4 vColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    gl_FragColor = mix(vColor, vec4(0.1, 0.1, 0.1, 1.0), edgeAmount);
}
);
