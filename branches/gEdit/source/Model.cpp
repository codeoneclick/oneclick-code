#include "Model.h"
#include "Resource.h"
#include "Render.h"
#include "Game.h"
#include "Core/CGlobal.h"

using namespace Enviroment;

CModel::CModel()
{
	m_vPosition = math::Vector3d(100.0f,0.0f,100.0f);
}

void CModel::Load(std::string value)
{
	m_MeshArray["main"] = CResource::GetMeshControllerInstance()->Load(value,Core::CMesh::EXT_3DS);
	m_MeshArray["main"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\tank_diffuse.dds",Core::ITexture::DDS_EXT);
	m_MeshArray["main"]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\tank_diffuse_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshArray["main"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic_02");
}

void CModel::Update()
{
	Matrix();
	m_vScale = math::Vector3d(2.0f,2.0,2.0f);
	static math::Vector3d vLightDir = math::Vector3d(0.0f, 0.0f, 0.0f);
	static float LightAngle = 0.0f;
	LightAngle += 0.01f;
	vLightDir.x = cos(LightAngle);
	vLightDir.y = 0.0f;
	vLightDir.z = sin(LightAngle);

	m_MeshArray["main"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	m_MeshArray["main"]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
	m_MeshArray["main"]->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);
}

void CModel::Render()
{
	m_MeshArray["main"]->m_Shader->SetTexture(m_MeshArray["main"]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshArray["main"]->m_Shader->SetTexture(m_MeshArray["main"]->m_TextureArray[1],"Texture_01_NH",Core::IShader::PS_SHADER);
	m_MeshArray["main"]->Draw();
}