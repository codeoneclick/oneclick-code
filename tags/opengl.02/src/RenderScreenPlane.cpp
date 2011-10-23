#include "RenderScreenPlane.h"

RenderScreenPlane::RenderScreenPlane()
{
	_vertexBufferPtr = NULL;
	_shaderStr = "screen";
	_textureStr[0] =  "SCREEN";
}

void RenderScreenPlane::Update()
{
	_UpdateWorldMatrix();
}

void RenderScreenPlane::Render()
{
	EnableShader("","screen");
	_UpdateShaderParams();
	
	glBegin(GL_QUADS);	

		glTexCoord2f ( 0.0f, 1.0f );
        glVertex2f   ( 0.0f, 0.0f );

        glTexCoord2f ( 0.0f, 0.0f );
        glVertex2f   ( 0.0f, Window::currentHeight );

        glTexCoord2f ( 1.0f, 0.0f );
        glVertex2f   ( Window::currentWidth, Window::currentHeight );

        glTexCoord2f ( 1.0f, 1.0f );
        glVertex2f   ( Window::currentWidth, 0.0f);

	glEnd();

	DisableShader();

}