const char* ShaderWaterF = STRINGIFY(
varying highp vec4   OUT_TexCoordProj;
varying highp vec2   OUT_TexCoord;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
varying lowp vec3   OUT_View;
varying lowp vec3   OUT_Light;
                                       
void main(void)
{
    highp vec2 vTexCoordProj = OUT_TexCoordProj.xy;
	vTexCoordProj.x = 0.5 - 0.5 * vTexCoordProj.x / OUT_TexCoordProj.w;
	vTexCoordProj.y = 0.5 + 0.5 * vTexCoordProj.y / OUT_TexCoordProj.w;
	vTexCoordProj = clamp(vTexCoordProj, 0.001, 0.999);
    lowp vec4 vReflectionColor = texture2D(EXT_TEXTURE_01, vTexCoordProj);
    
    vTexCoordProj = OUT_TexCoordProj.xy;
    vTexCoordProj.x = 0.5 + 0.5 * vTexCoordProj.x / OUT_TexCoordProj.w;
    vTexCoordProj.y = 0.5 + 0.5 * vTexCoordProj.y / OUT_TexCoordProj.w;
    vTexCoordProj = clamp(vTexCoordProj, 0.001, 0.999);
    lowp vec4 vRefractionColor = texture2D(EXT_TEXTURE_02, vTexCoordProj);
    
    //lowp vec3 vNormalColor = texture2D(EXT_TEXTURE_03, OUT_TexCoord * 8.0).xyz;
    //lowp vec3 vFakeLight = vec3(0.0, 1.0, 0.0);
	//lowp vec4 vSpecularColor = vec4(pow(dot(vNormalColor, vFakeLight), 16.0));
    
    gl_FragColor = mix(mix(vReflectionColor, vRefractionColor, 0.5), vec4(0.27, 0.35, 0.77, 1.0), 0.5);// + vSpecularColor;
}
);
