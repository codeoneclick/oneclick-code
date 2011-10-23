#include "SkySphere.h"

#include "RenderController.h"
#include "m3_Util.h"

SkySphere::SkySphere()
{
	_shaderStr = "sky";
	_textureStr[0] = "Content\\textures\\grass.dds";
	__vertexBufferPtr = NULL;
	vPosition = Vector3d(128.0f,0.0f,128.0f);
	vScale = Vector3d(16.0f,16.0f,16.0f);
}

void SkySphere::Load(std::string value)
{
	_meshFileName = value;
}

void SkySphere::Update()
{
	if(!__vertexBufferPtr)
	{
		__vertexBufferPtr = Resource::MeshContainer()->GetMesh(_meshFileName);
		if(__vertexBufferPtr)
		{
			__vertexBufferPtr->bPosition = true;
			__vertexBufferPtr->bTexCoord = true;
		}
	}	

	_UpdateWorldMatrix();
}

void SkySphere::Render()
{
	if(!__vertexBufferPtr) return;

	glDisable(GL_CULL_FACE);
	_EnableShader();
	_UpdateShaderParams();
	_UpdateVB();
	
	glDrawElements( GL_TRIANGLES, __vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, &__vertexBufferPtr->indecesPtr[0] );

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	VB::glBindDataVB(GL_TEXTURE0);

	_DisableShader();
	glEnable(GL_CULL_FACE);
}