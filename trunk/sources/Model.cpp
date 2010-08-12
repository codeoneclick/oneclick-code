#include "Model.h"
#include "Resource.h"

using namespace Enviroment;

CModel::CModel()
{
}

void CModel::Load(std::string value)
{
	_textures[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",type::STexture::_DDS);
	_meshData = Resource::GetMeshControllerInstance()->Load(value,type::SMesh::_3DS);
	
	_shader->Create("multitex");
}

void CModel::Update()
{
	_UpdateMatrix();
}

void CModel::Render()
{
	bool _shaderRender = true;
	if(_shaderRender)
	{
		_shader->Enable();
		_shader->SetWVPMatrix(_mWorldViewProjection);
		_shader->SetTexture(0,_textures[0]->addr_ptr);
		_meshData->vertexBuffer->Enable();
		_meshData->indexBuffer->Enable();
		glDrawElements( GL_TRIANGLES, _meshData->indexBuffer->GetNumIndeces(), GL_UNSIGNED_INT, NULL);
		_shader->Disable();
	}
}