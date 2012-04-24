const char* ShaderPostEdgeDetectV = STRINGIFY(
                                                   
                                                   attribute vec3 IN_SLOT_Position;
                                                   attribute vec2 IN_SLOT_TexCoord;
                                                                                        
                                                   varying vec2   OUT_TexCoord;
                                                   varying vec4   OUT_TexCoord_01;
                                                   varying vec4   OUT_TexCoord_02;
                                                   varying vec4   OUT_TexCoord_03;
                                                   varying vec4   OUT_TexCoord_04;
                                       
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord;
    
    /*lowp float fThickness = 2.0;
    lowp vec2 ox = lowp vec2(fThickness / 640.0, 0.0);
    lowp vec2 oy = lowp vec2(0.0, fThickness / 480.0);
    OUT_TexCoord_01.xy = IN_SLOT_TexCoord - ox - oy;
    OUT_TexCoord_01.zw = IN_SLOT_TexCoord - oy;
    OUT_TexCoord_02.xy = IN_SLOT_TexCoord + ox - oy;
    OUT_TexCoord_02.zw = IN_SLOT_TexCoord - ox;
    OUT_TexCoord_03.xy = IN_SLOT_TexCoord + ox;
    OUT_TexCoord_03.zw = IN_SLOT_TexCoord - ox + oy;
    OUT_TexCoord_04.xy = IN_SLOT_TexCoord + oy;
    OUT_TexCoord_04.zw = IN_SLOT_TexCoord + ox + oy;*/
    
    lowp float fThickness = 1.0;
    lowp vec2 vEdgeOffset = vec2(1.0 / 480.0, 1.0 / 320.0);
    OUT_TexCoord_01.xy = IN_SLOT_TexCoord + vec2(-1.0, -1.0) * vEdgeOffset;
    OUT_TexCoord_01.zw = IN_SLOT_TexCoord + vec2( 1.0,  1.0) * vEdgeOffset;
    OUT_TexCoord_02.xy = IN_SLOT_TexCoord + vec2(-1.0,  1.0) * vEdgeOffset;
    OUT_TexCoord_02.zw = IN_SLOT_TexCoord + vec2( 1.0, -1.0) * vEdgeOffset;
    
    gl_Position = vec4(IN_SLOT_Position, 1.0);
}
);
