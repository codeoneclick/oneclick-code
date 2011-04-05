#include "Brush.h"
#include "../Resource/Manager/Resource.h"
#include "../Game/Game.h"
#include "../Core/CGlobal.h"

using namespace Enviroment;

CBrush::CBrush(CLandscape* _landscape)
{
	m_Width  = 16;
	m_Height = 16;

	m_heightOffset = 0.5f;

	m_Name = "Brush";
	m_Landscape = _landscape;
}

void CBrush::Load(std::vector<SResource> _resource)
{
	SResource brushResource = *_resource.begin();
	m_MeshList[m_Name] = new Core::CMesh();
	m_MeshList[m_Name]->m_Shader = CResource::GetShaderControllerInstance()->Load(brushResource.m_ShaderFile);
	m_MeshList[m_Name]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList[m_Name]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();

	SVertex* vertexData = (SVertex*)m_MeshList[m_Name]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertex),0);
	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
	{
        for(unsigned int j = 0; j < m_Height;++j)
		{
			vertexData[index].m_vPosition = math::Vector3d(i * m_Landscape->GetScaleFactor() ,m_Landscape->GetHeightData()[i][j] * m_Landscape->GetHeightFactor() + m_heightOffset,j * m_Landscape->GetScaleFactor());
			vertexData[index].m_vExtValue = math::Vector2d(1.0f,1.0f);
			++index;
		}
	}

	m_MeshList[m_Name]->m_VertexBuffer->CommitToVRAM(0);

	unsigned int *indexData = m_MeshList[m_Name]->m_IndexBuffer->Load(m_Width * m_Height * 6);
	index = 0;
	for(unsigned int i = 0; i < (m_Width - 1); ++i)
	{
		for(unsigned int j = 0; j < (m_Height - 1); ++j)
		{
			indexData[index] = i + j * m_Width;
            index++;
            indexData[index] = i + (j + 1) * m_Width;
            index++;
            indexData[index] = i + 1 + j * m_Width;
            index++;

            indexData[index] = i + (j + 1) * m_Width;
            index++;
            indexData[index] = i + 1 + (j + 1) * m_Width;
            index++;
            indexData[index] = i + 1 + j * m_Width;
            index++;
		}
	}

	m_MeshList[m_Name]->m_IndexBuffer->CommitToVRAM();

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[2];
	
	declaration.m_Elements[0].m_stream = 0;
	declaration.m_Elements[0].m_index = 0;
	declaration.m_Elements[0].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_offset = 0;

	declaration.m_Elements[1].m_stream = 0;
	declaration.m_Elements[1].m_index = 0;
	declaration.m_Elements[1].m_size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_offset = 12;

	declaration.m_ElementCount = 2;
}

void CBrush::Update()
{
	Matrix();

	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();
	
	while(meshIteratorBegin != meshIteratorEnd)
	{
		SVertex *vertexData = (SVertex*)meshIteratorBegin->second->m_VertexBuffer->Lock(0);
		unsigned int index = 0;
		for(unsigned int i = 0; i < m_Width;++i)
		{
			for(unsigned int j = 0; j < m_Height;++j)
			{
				int posX = (int)m_brush2DPosition.x + i - m_Width / 2;
				int posZ = (int)m_brush2DPosition.y + j - m_Height / 2;

				vertexData[index].m_vExtValue = math::Vector2d(0.0f,0.0f);
				if(posX <= 0 || posZ <= 0 || posX >= m_Landscape->GetWidth() || posZ >= m_Landscape->GetHeight())
				{
					vertexData[index].m_vPosition = math::Vector3d(posX * m_Landscape->GetScaleFactor() ,0.0f,posZ * m_Landscape->GetScaleFactor());
					vertexData[index].m_vExtValue = math::Vector2d(0.0f,0.0f);
					++index;
					continue;
				}

				vertexData[index].m_vPosition = math::Vector3d(posX * m_Landscape->GetScaleFactor() ,m_Landscape->GetHeightData()[posX][posZ] * m_Landscape->GetHeightFactor() + m_heightOffset,posZ * m_Landscape->GetScaleFactor());
				vertexData[index].m_vExtValue = math::Vector2d(0.2f,0.2f);
				++index;
			}
		}
		meshIteratorBegin->second->m_VertexBuffer->Unlock(0);
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
		meshIteratorBegin++;
	}
}

void CBrush::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_NONE);
	Core::CGlobal::GetDevice()->AlphaBlendEnable();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();
	
	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->Draw();
		meshIteratorBegin++;
	}
}
