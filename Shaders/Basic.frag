const char* BasicFragmentShader = STRINGIFY(

varying lowp vec4 DestinationColor;
varying mediump vec2 texcoord_slot_out;
uniform sampler2D Texture;

void main(void)
{
   gl_FragColor = texture2D(Texture, texcoord_slot_out) + DestinationColor * 0.5;
}
);
