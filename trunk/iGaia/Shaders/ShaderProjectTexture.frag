const char* ShaderProjectTextureF = STRINGIFY(                                    
                                                   varying mediump vec4   OUT_TexCoord;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    lowp vec2 vTexCoordProj = OUT_TexCoord.xy;
	vTexCoordProj.x = 0.5 - 0.5 * vTexCoordProj.x / OUT_TexCoord.w;
	vTexCoordProj.y = 0.5 + 0.5 * vTexCoordProj.y / OUT_TexCoord.w;
	vTexCoordProj = clamp(vTexCoordProj, 0.001, 0.999); 
    gl_FragColor = texture2D(EXT_TEXTURE_01, vTexCoordProj);;
}
);
