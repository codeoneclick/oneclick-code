const char* ShaderColorF = STRINGIFY(

varying lowp vec4 DestinationColor;
varying mediump vec2 texcoord_slot_out;

void main(void)
{
   gl_FragColor = DestinationColor;
}
);
