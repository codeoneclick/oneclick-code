const char* ShaderTextureCubeF = STRINGIFY(                                    
                                                    varying highp vec3   OUT_TexCoord;
                                                    uniform samplerCube  EXT_TEXTURE_CUBE;
                                       
void main(void)
{
    highp vec4 vDiffuseColor = textureCube(EXT_TEXTURE_CUBE, OUT_TexCoord);
    vDiffuseColor.a = 1.0;
    gl_FragColor = vDiffuseColor;
}
);
