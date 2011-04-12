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
	m_MeshList[m_Name]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\ocean");
	m_MeshList[m_Name]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList[m_Name]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	
	SVertex* vertexData = (SVertex*)m_MeshList[m_Name]->m_VertexBuffer->Load(4, sizeof(SVertex),0);
	vertexData[0].vPosition = math::Vector3d(0.0f, 0.0f, 0.0f);
	vertexData[0].vTexCoord = math::Vector2d(0.0f, 0.0f);
	vertexData[1].vPosition = math::Vector3d(0.0f, 0.0f, m_Height);
	vertexData[1].vTexCoord = math::Vector2d(0.0f, 1.0f);
	vertexData[2].vPosition = math::Vector3d(m_Width, 0.0f, 0.0f);
	vertexData[2].vTexCoord = math::Vector2d(1.0f, 0.0f);
	vertexData[3].vPosition = math::Vector3d(m_Width, 0.0f, m_Height);
	vertexData[3].vTexCoord = math::Vector2d(1.0f, 1.0f);
	m_MeshList[m_Name]->m_VertexBuffer->CommitToVRAM(0);

	unsigned int *indexData = m_MeshList[m_Name]->m_IndexBuffer->Load(6);
	indexData[0] = 0;
	indexData[1] = 2;
	indexData[2] = 1;
	indexData[3] = 1;
	indexData[4] = 2;
	indexData[5] = 3;
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
	Matrix();

	m_MeshList[m_Name]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetMatrix(m_mWorld,"mWorld",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetFloat(Game::GetEnviromentControllerInstance()->GetLightInstance()->GetTime(),"fTimer",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetLightInstance()->GetDirection(),"vLightDir",Core::IShader::VS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->m_FogColor, "vFogColor", Core::IShader::VS_SHADER);
}

void COcean::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_CW);
	Core::CGlobal::GetDevice()->AlphaBlendDisable();
	Core::CGlobal::GetDevice()->AlphaTestDisable();

	m_MeshList[m_Name]->m_Shader->SetTexture(m_MeshList[m_Name]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFLECTION_TEXTURE),"Texture_02",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFRACTION_TEXTURE),"Texture_03",Core::IShader::PS_SHADER);
	m_MeshList[m_Name]->Draw();
}