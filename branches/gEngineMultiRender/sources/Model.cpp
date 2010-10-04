#include "Model.h"
#include "Resource.h"
#include "Render.h"

using namespace Enviroment;

CModel::CModel()
{
}

void CModel::Load(std::string value)
{
	_textures[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::CTexture::DDS_EXT);
	_meshData = Resource::GetMeshControllerInstance()->Load(value,type::SMesh::_3DS);
	_shader = Resource::GetShaderControllerInstance()->Load("Content\\shaders\\basic_02");
}

void CModel::Update()
{
	_UpdateMatrix();
}

void CModel::Render()
{
	_shader->Enable();
	_shader->SetMatrix(_mWorldViewProjection,"mWorldViewProjection",Core::CShader::VS_SHADER);
	_shader->SetTexture(*_textures[0],"Texture_01",Core::CShader::PS_SHADER);
	_meshData->vertexBuffer->Enable();
	_meshData->indexBuffer->Enable();
	Core::CRender::Draw(_meshData->vertexBuffer->GetVertexCount(),_meshData->indexBuffer->GetIndexCount(),_meshData->indexBuffer->GetIndexCount());
	_meshData->vertexBuffer->Disable();
	_meshData->indexBuffer->Disable();
	_shader->Disable();
}