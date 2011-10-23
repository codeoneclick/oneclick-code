uniform sampler2D testTexture;

varying vec3 vertex_normal; 
varying vec3 vertex_light_position;
varying vec3 vertex_light_half_vector;

void main( void )
{
   vec4 ambient_color = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_LightModel.ambient * gl_FrontMaterial.ambient;

   vec4 diffuse_color = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;

   vec4 specular_color = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(dot(vertex_normal, vertex_light_half_vector), 0.0) , gl_FrontMaterial.shininess);

   float diffuse_value = max(dot(vertex_normal, vertex_light_position), 0.0);

   gl_FragColor =  specular_color* texture2D( testTexture, gl_TexCoord[0].xy )/2.0 + diffuse_value * texture2D( testTexture, gl_TexCoord[0].xy );

}
