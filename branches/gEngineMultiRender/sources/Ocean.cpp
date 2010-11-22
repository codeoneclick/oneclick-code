#include "Ocean.h"
#include "Resource.h"
#include "Game.h"
#include "RenderController.h"

using namespace Enviroment;

COcean::COcean()
{
	m_Width  = 256;
	m_Height = 256;
	m_vPosition.y = 12.0f;
}

void COcean::Load(std::string value)
{
	m_MeshArray["ocean_01"] = new Core::CMesh();
	m_MeshArray["ocean_01"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\water.dds",Core::ITexture::DDS_EXT);
	m_MeshArray["ocean_01"]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\wave.dds",Core::ITexture::DDS_EXT);
	m_MeshArray["ocean_01"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\ocean");
	m_MeshArray["ocean_01"]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshArray["ocean_01"]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	
	SVertex* v_data_01 = (SVertex*)m_MeshArray["ocean_01"]->m_VertexBuffer->Load(4, sizeof(SVertex));
	
	v_data_01[0].vPosition = math::Vector3d(0.0f, 0.0f, 0.0f);
	v_data_01[0].vTexCoord = math::Vector2d(0.0f, 0.0f);
	v_data_01[1].vPosition = math::Vector3d(0.0f, 0.0f, m_Height);
	v_data_01[1].vTexCoord = math::Vector2d(0.0f, 1.0f);
	v_data_01[2].vPosition = math::Vector3d(m_Width, 0.0f, 0.0f);
	v_data_01[2].vTexCoord = math::Vector2d(1.0f, 0.0f);
	v_data_01[3].vPosition = math::Vector3d(m_Width, 0.0f, m_Height);
	v_data_01[3].vTexCoord = math::Vector2d(1.0f, 1.0f);

	unsigned int *i_data_01 = m_MeshArray["ocean_01"]->m_IndexBuffer->Load(6);
	
	i_data_01[0] = 0;
	i_data_01[1] = 2;
	i_data_01[2] = 1;

	i_data_01[3] = 1;
	i_data_01[4] = 2;
	i_data_01[5] = 3;

	m_MeshArray["ocean_01"]->m_VertexBuffer->CommitToVRAM();
	m_MeshArray["ocean_01"]->m_IndexBuffer->CommitToVRAM();

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[2];
	
	declaration.m_Elements[0].m_Index = 0;
	declaration.m_Elements[0].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_Type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_Offset = 0 * sizeof(float);

	declaration.m_Elements[1].m_Index = 0;
	declaration.m_Elements[1].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_Offset = 3 * sizeof(float);

	declaration.m_ElementCount = 2;
	m_MeshArray["ocean_01"]->m_VertexBuffer->SetDeclaration(declaration);
}

void COcean::Update()
{
	Matrix();
	m_MeshArray["ocean_01"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	static float fTimer = 0.0f;
	fTimer += 0.001f;
	m_MeshArray["ocean_01"]->m_Shader->SetFloat(fTimer,"fTimer",Core::IShader::PS_SHADER);
}

void COcean::Render()
{
	Core::CGlobal::GetRender()->SetCullFace(Core::IRender::CULL_CW);
	m_MeshArray["ocean_01"]->m_Shader->SetTexture(m_MeshArray["ocean_01"]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshArray["ocean_01"]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFLECTION_TEXTURE),"Texture_02",Core::IShader::PS_SHADER);
	m_MeshArray["ocean_01"]->m_Shader->SetTexture(Video::CRenderController::GetRenderTargetTexture(Video::CRenderController::REFRACTION_TEXTURE),"Texture_03",Core::IShader::PS_SHADER);\
	m_MeshArray["ocean_01"]->m_Shader->SetTexture(m_MeshArray["ocean_01"]->m_TextureArray[1],"Texture_04",Core::IShader::PS_SHADER);
	m_MeshArray["ocean_01"]->Draw();
}