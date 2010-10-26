#include "Model.h"
#include "Resource.h"
#include "Render.h"

using namespace Enviroment;

CModel::CModel()
{

}

void CModel::Load(std::string value)
{
	m_MeshArray["main"] = CResource::GetMeshControllerInstance()->Load(value,Core::CMesh::EXT_3DS);
	m_MeshArray["main"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::ITexture::DDS_EXT);
	m_MeshArray["main"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic_02");
}

void CModel::Update()
{
	Matrix();
	m_MeshArray["main"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	m_MeshArray["main"]->m_Shader->SetTexture(m_MeshArray["main"]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
}

void CModel::Render()
{
	m_MeshArray["main"]->Draw();
}