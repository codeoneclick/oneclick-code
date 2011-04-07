#include "Ocean.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../Controller/RenderController.h"

using namespace Enviroment;

COcean::COcean(CLandscape* _landscape)
{
	m_Width  = _landscape->GetWidth() * 3.0f;
	m_Height = _landscape->GetHeight() * 3.0f;
	m_HeightLevel = 12.0f;
	m_vPosition = math::Vector3d(-(float)(_landscape->GetWidth()), m_HeightLevel, -(float)(_landscape->GetHeight()));
	m_Name = "ocean";
}

void COcean::Load(std::vector<SResource> _resource)
{
	m_MeshList[m_Name] = new Core::CMesh();
	m_MeshList[m_Name]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\water.dds",Core::ITexture::DDS_EXT);
	m_MeshList[m_Name]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\sand.dds",Core::ITexture::DDS_EXT);
	m_MeshList[m_Name]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\ocean");
	m_MeshList[m_Name]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList[m_Name]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	
	SVertex* v_data_01 = (SVertex*)m_MeshList[m_Name]->m_VertexBuffer->Load(4, sizeof(SVertex),0);
	
	v_data_01[0].vPosition = math::Vector3d(0.0f, 0.0f, 0.0f);
	v_data_01[0].vTexCoord = math::Vector2d(0.0f, 0.0f);
	v_data_01[1].vPosition = math::Vector3d(0.0f, 0.0f, m_Height);
	v_data_01[1].vTexCoord = math::Vector2d(0.0f, 1.0f);
	v_data_01[2].vPosition = math::Vector3d(m_Width, 0.0f, 0.0f);
	v_data_01[2].vTexCoord = math::Vector2d(1.0f, 0.0f);
	v_data_01[3].vPosition = math::Vector3d(m_Width, 0.0f, m_Height);
	v_data_01[3].vTexCoord = math::Vector2d(1.0f, 1.0f);

	unsigned int *i_data_01 = m_MeshList[m_Name]->m_IndexBuffer->Load(6);
	
	i_data_01[0] = 0;
	i_data_01[1] = 2;
	i_data_01[2] = 1;

	i_data_01[3] = 1;
	i_data_01[4] = 2;
	i_data_01[5] = 3;

	m_MeshList[m_Name]->m_VertexBuffer->CommitToVRAM(0);
	m_MeshList[m_Name]->m_IndexBuffer->CommitToVRAM();

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[2];
	
	declaration.m_Elements[0].m_index = 0;
	declaration.m_Elements[0].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_offset = 0 * sizeof(float);

	declaration.m_Elements[1].m_index = 0;
	declaration.m_Elements[1].m_size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_offset = 3 * sizeof(float);

	declaration.m_ElementCount = 2;
	m_MeshList[m_Name]->m_VertexBuffer->SetDeclaration(declaration);
}

void COcean::Update()
{
	static math::Vector3d vLightDir = math::Vector3d(0.0f, 0.0f, 0.0f);
	static float LightAngle = 0.0f;
	LightAngle += 0.001f;
	vLightDir.x = cos(LightAngle);
	vLightDir.y = 0.0f;
	vLightDir.z = sin(LightAngle);

	Matrix();
	m_MeshList[m_Name]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetMatrix(m_mWorld,"mWorld",Core::IShader::VS_SHADER);
	static float fTimer = 0.0f;
	fTimer += 0.01f;
	m_MeshList[m_Name]->m_Shader->SetFloat(fTimer,"fTimer",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->m_LightDir,"vLightDir",Core::IShader::VS_SHADER);
}

void COcean::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_CW);
	Core::CGlobal::GetDevice()->AlphaBlendDisable();
	Core::CGlobal::GetDevice()->AlphaTestDisable();

	m_MeshList[m_Name]->m_Shader->SetTexture(m_MeshList[m_Name]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFLECTION_TEXTURE),"Texture_02",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFRACTION_TEXTURE),"Texture_03",Core::IShader::PS_SHADER);\
	m_MeshList[m_Name]->m_Shader->SetTexture(m_MeshList[m_Name]->m_TextureArray[1],"Texture_04",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->Draw();
}