#include "Model.h"
#include "../../Resource/Manager/Resource.h"
#include "../../Core/CGlobal.h"
#include "../Game.h"

using namespace Enviroment;

CModel::CModel()
{
	
}

CModel::~CModel()
{

}

void CModel::Load(std::vector<SResource> _resource)
{
	std::vector<SResource>::iterator resourceIteratorBegin = _resource.begin();
	std::vector<SResource>::iterator resourceIteratorEnd = _resource.end();

	while(resourceIteratorBegin != resourceIteratorEnd)
	{
		m_MeshList[resourceIteratorBegin->m_ResouceFile] = CResource::GetMeshControllerInstance()->Load(resourceIteratorBegin->m_ResouceFile,resourceIteratorBegin->m_Extension);
		for(unsigned int index = 0; index < K_MAX_TEXTURES_PER_MESH; ++index)
		{
			if(resourceIteratorBegin->m_TextureFileList[index].length())
				m_MeshList[resourceIteratorBegin->m_ResouceFile]->m_TextureArray[index] = CResource::GetTextureControllerInstance()->Load(resourceIteratorBegin->m_TextureFileList[index],Core::ITexture::DDS_EXT);
		}
		m_MeshList[resourceIteratorBegin->m_ResouceFile]->m_Shader = CResource::GetShaderControllerInstance()->Load(resourceIteratorBegin->m_ShaderFile);	
		resourceIteratorBegin++;
	}
}

void CModel::Update()
{
	Matrix();

	static math::Vector3d vLightDir = math::Vector3d(0.0f, 0.0f, 0.0f);
	static float LightAngle = 0.0f;
	LightAngle += 0.01f;
	vLightDir.x = cos(LightAngle);
	vLightDir.y = 0.0f;
	vLightDir.z = sin(LightAngle);

	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorld,"mWorld",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);
		meshIteratorBegin++;
	}
}

void CModel::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_CCW);
	
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[1],"Texture_01_NH",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->Draw();
		meshIteratorBegin++;
	}
}