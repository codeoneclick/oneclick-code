#include "Model.h"
#include "Resource.h"
#include "Render.h"

using namespace Enviroment;

CModel::CModel()
{
}

void CModel::Load(std::string value)
{
	m_TextureArray[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::CTexture::DDS_EXT);
	m_MeshData = Resource::GetMeshControllerInstance()->Load(value,type::SMesh::EXT_3DS);
	m_Shader = Resource::GetShaderControllerInstance()->Load("Content\\shaders\\basic_02");
}

void CModel::Update()
{
	RefreshMatrix();
}

void CModel::Render()
{
	m_Shader->Enable();
	m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::CShader::VS_SHADER);
	m_Shader->SetTexture(*m_TextureArray[0],"Texture_01",Core::CShader::PS_SHADER);
	m_MeshData->m_VertexBuffer->Enable();
	m_MeshData->m_IndexBuffer->Enable();
	Core::CRender::Draw(m_MeshData->m_VertexBuffer->GetVertexCount(),m_MeshData->m_IndexBuffer->GetIndexCount(),m_MeshData->m_IndexBuffer->GetPrimitiveCount());
	m_MeshData->m_VertexBuffer->Disable();
	m_MeshData->m_IndexBuffer->Disable();
	m_Shader->Disable();
}