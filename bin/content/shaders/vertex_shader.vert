varying vec3 vertex_normal; 
varying vec3 vertex_light_position;
varying vec3 vertex_light_half_vector;

void main( void )
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
        gl_FrontColor = gl_Color;
	vertex_normal = normalize(gl_NormalMatrix  * gl_Normal);
	vertex_light_position = normalize(gl_LightSource[0].position.xyz);
        vertex_light_half_vector = normalize(gl_LightSource[0].halfVector.xyz);
}
