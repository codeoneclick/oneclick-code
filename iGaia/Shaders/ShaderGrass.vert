const char* ShaderGrassV = STRINGIFY(
                                                    
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Normal;
                                                    attribute vec4 IN_SLOT_Tangent;
                                                    
                                                    varying vec3   OUT_View;
                                                    varying vec3   OUT_Light;
                                                    varying vec3   OUT_Normal;                                     
                                                    varying vec2   OUT_TexCoord;
                                                    
                                                    uniform vec3   EXT_View;
                                                    uniform vec3   EXT_Light;
                                                    uniform float  EXT_Timer;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
                                       
void main(void)
{
    vec4 vWorldPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    
    float fAngleX = vWorldPosition.z * vWorldPosition.y -  floor(vWorldPosition.z * vWorldPosition.y);
	float fAngleZ = vWorldPosition.x - floor(vWorldPosition.x);
	if(IN_SLOT_TexCoord.y == 0.0)  
	{
		vWorldPosition.x += sin(EXT_Timer * fAngleX) * 0.33;
		vWorldPosition.z += cos(EXT_Timer * fAngleZ) * 0.33;
	}
    
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vWorldPosition;
    OUT_TexCoord = IN_SLOT_TexCoord;
}
);
