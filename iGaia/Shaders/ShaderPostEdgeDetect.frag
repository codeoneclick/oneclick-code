const char* ShaderPostEdgeDetectF = STRINGIFY(                                    
                                                   varying lowp vec2   OUT_TexCoord;
                                                   varying lowp vec4   OUT_TexCoord_01;
                                                   varying lowp vec4   OUT_TexCoord_02;
                                                   varying lowp vec4   OUT_TexCoord_03;
                                                   varying lowp vec4   OUT_TexCoord_04;

                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
	/*lowp vec4 vSourceColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord);
    lowp vec4 vMainColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    
    lowp float fTexCoordOffset = 0.001;
    lowp vec4 vEdgeColor = (texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2(-fTexCoordOffset, -fTexCoordOffset)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2(-fTexCoordOffset, 0.0)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2(-fTexCoordOffset, fTexCoordOffset)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2( 0.0, fTexCoordOffset)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2( fTexCoordOffset, fTexCoordOffset)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2( fTexCoordOffset, 0.0)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2( fTexCoordOffset, -fTexCoordOffset)) +
    texture2D(EXT_TEXTURE_02, OUT_TexCoord + vec2( 0.0, -fTexCoordOffset))) * 0.125;

    if(abs((vEdgeColor.r + vEdgeColor.g + vEdgeColor.b) - (vSourceColor.r + vSourceColor.g + vSourceColor.b)) > 0.01)
    {
        vMainColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    
    gl_FragColor = vMainColor;*/
    
    /*lowp float fThreshold = 0.1;
    
    lowp vec4 vScreenSpaceNormalColor;
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.xy); lowp float  fEdgeFactor_01 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.zw); lowp float  fEdgeFactor_02 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.xy); lowp float  fEdgeFactor_03 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.zw); lowp float  fEdgeFactor_04 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_03.xy); lowp float  fEdgeFactor_05 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_03.zw); lowp float  fEdgeFactor_06 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_04.xy); lowp float  fEdgeFactor_07 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
	vScreenSpaceNormalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord_04.zw); lowp float  fEdgeFactor_08 = dot(vScreenSpaceNormalColor.rgb,(vec3(0.2,0.7,0.1)));
    
    lowp float sx = 0.0;
	sx -= fEdgeFactor_01;
	sx -= fEdgeFactor_02 * 2.0;
	sx -= fEdgeFactor_03;
	sx += fEdgeFactor_06;
	sx += fEdgeFactor_07 * 2.0;
	sx += fEdgeFactor_08;
	lowp float sy = 0.0;
	sy -= fEdgeFactor_01;
	sy += fEdgeFactor_03;
	sy -= fEdgeFactor_04 * 2.0;
	sy += fEdgeFactor_05 * 2.0;
	sy -= fEdgeFactor_06;
	sy += fEdgeFactor_07;

    lowp float fDistance = sqrt(sx * sx + sy * sy);
    lowp float fEdgeNormal = 0.0;
    if (fDistance > fThreshold) 
    { 
        fEdgeNormal = 1.0; 
    }
    
    fThreshold = 0.01;
    
    fEdgeFactor_01 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.xy).a; 
	fEdgeFactor_02 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.zw).a;
	fEdgeFactor_03 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.xy).a;
	fEdgeFactor_04 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.zw).a; 
	fEdgeFactor_05 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_03.xy).a;
	fEdgeFactor_06 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_03.zw).a; 
	fEdgeFactor_07 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_04.xy).a; 
	fEdgeFactor_08 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_04.zw).a; 
    
    
    sx = 0.0;
	sx -= fEdgeFactor_01;
	sx -= fEdgeFactor_02 * 2.0;
	sx -= fEdgeFactor_03;
	sx += fEdgeFactor_06;
	sx += fEdgeFactor_07 * 2.0;
	sx += fEdgeFactor_08;
	sy = 0.0;
	sy -= fEdgeFactor_01;
	sy += fEdgeFactor_03;
	sy -= fEdgeFactor_04 * 2.0;
	sy += fEdgeFactor_05 * 2.0;
	sy -= fEdgeFactor_06;
	sy += fEdgeFactor_07;
    
    fDistance = sqrt(sx * sx + sy * sy);
    lowp float fEdgeDepth = 0.0;
    if (fDistance > fThreshold) 
    { 
        fEdgeDepth = 1.0; 
    }

    
    lowp vec4 vMainColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * vec4(1.0 - fEdgeNormal * fEdgeDepth) ;
    gl_FragColor = vMainColor;*/
    
    
    
    lowp vec4 n1 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.xy);
    lowp vec4 n2 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.zw);
    lowp vec4 n3 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.xy);
    lowp vec4 n4 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.zw);
    
    lowp vec4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);
    
    lowp float normalDelta = dot(diagonalDelta.xyz, vec3(1.0));
    lowp float depthDelta = diagonalDelta.w;
    
    normalDelta = clamp((normalDelta - 0.2), 0.0, 1.0);
    //depthDelta = clamp((depthDelta - 0.04) * 10.0, 0.0, 1.0);
    
    lowp float edgeAmount = clamp(normalDelta, 0.0, 1.0);
    
    lowp vec4 vOriginalColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord);
    if(vOriginalColor.r > 0.85 && vOriginalColor.g > 0.85 && vOriginalColor.b > 0.85)
    {
        edgeAmount = 0.0;
    }
    
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * (1.0 - edgeAmount);
}
);
