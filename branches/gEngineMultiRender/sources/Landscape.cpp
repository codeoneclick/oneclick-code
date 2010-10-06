#include "Landscape.h"
#include "Resource.h"
#include "Game.h"
#include "Render.h"

using namespace Enviroment;

Landscape::Landscape()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;
}

void Landscape::Load(std::string _fileName)
{
	m_MapData = new float*[m_Width];
	for(unsigned int i = 0; i < m_Width; ++i)
	{
		m_MapData[i] = new float[m_Width];
		for(unsigned int j = 0; j < m_Height; ++j)
			m_MapData[i][j] = 0.0f;
	}

	unsigned char readValue = 0;
	FILE * file;
	file = fopen( _fileName.c_str(), "rb" );
	for( unsigned int i = 0; i < m_Width; ++i )
		for( unsigned int j = 0; j < m_Height; ++j )
		{
			fread(&readValue,sizeof(unsigned char),1,file);
			m_MapData[i][j] = static_cast<float>(readValue);
		}
	fclose( file );

	m_TextureArray[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::CTexture::DDS_EXT);
	
	m_MeshData = new type::SMesh();
	m_MeshData->m_VertexBuffer = new CVertexBuffer();
	
	CVertexBuffer::SVertexVTTBN* v_data = (CVertexBuffer::SVertexVTTBN*)m_MeshData->m_VertexBuffer->Load(m_Width * m_Height,sizeof(CVertexBuffer::SVertexVTTBN));
	
	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			v_data[index].vPosition = math::Vector3d(i*4.0f,m_MapData[i][j]*0.5f - 128.0f,j*4.0f);
			v_data[index].vTexCoord = math::Vector2d(static_cast<float>(i) / 16.0f,static_cast<float>(j) / 16.0f);;
			++index;
		}
   
	m_MeshData->m_IndexBuffer = new CIndexBuffer();
	unsigned int index_count = (m_Width - 1)*(m_Height - 1) * 6;
	unsigned int *i_data = m_MeshData->m_IndexBuffer->Load(index_count);
	index = 0;
	for(unsigned int i = 0; i < (m_Width - 1); ++i)
		for(unsigned int j = 0; j < (m_Height - 1); ++j)
		{
			i_data[index] = i + j * m_Width;
            index++;
            i_data[index] = i + (j + 1) * m_Width;
            index++;
            i_data[index] = i + 1 + j * m_Width;
            index++;

            i_data[index] = i + (j + 1) * m_Width;
            index++;
            i_data[index] = i + 1 + (j + 1) * m_Width;
            index++;
            i_data[index] = i + 1 + j * m_Width;
            index++;
		}
	CalculateTBN(v_data,i_data,m_Width * m_Height,index_count);
	m_MeshData->m_VertexBuffer->CommitVRAM();
	m_MeshData->m_IndexBuffer->CommitVRAM();
	m_Shader = Resource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");

	CVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new CVertexBuffer::SElementDeclaration[5];
	
	declaration.m_Elements[0].m_Index = 0;
	declaration.m_Elements[0].m_Size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_Type = CVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_Offset = 0 * sizeof(float);

	declaration.m_Elements[1].m_Index = 0;
	declaration.m_Elements[1].m_Size = CVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_Type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_Offset = 3 * sizeof(float);

	declaration.m_Elements[2].m_Index = 0;
	declaration.m_Elements[2].m_Size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[2].m_Type = CVertexBuffer::ELEMENT_NORMAL;
	declaration.m_Elements[2].m_Offset = 5 * sizeof(float);

	declaration.m_Elements[3].m_Index = 1;
	declaration.m_Elements[3].m_Size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[3].m_Type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[3].m_Offset = 8 * sizeof(float);

	declaration.m_Elements[4].m_Index = 2;
	declaration.m_Elements[4].m_Size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[4].m_Type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[4].m_Offset = 11 * sizeof(float);

	declaration.m_ElementCount = 5;

	m_MeshData->m_VertexBuffer->SetDeclaration(declaration);
}

void Landscape::CalculateTBN(CVertexBuffer::SVertexVTTBN *_v_data,unsigned int *_i_data, unsigned int _vertex_count,unsigned int _index_count)
{
    for(unsigned int i = 0; i < _index_count; i += 3)
    {
		math::Vector3d p1 = math::Vector3d(_v_data[_i_data[i + 0]].vPosition.x,
										   _v_data[_i_data[i + 0]].vPosition.y,
										   _v_data[_i_data[i + 0]].vPosition.z);
				
		math::Vector3d p2 = math::Vector3d(_v_data[_i_data[i + 1]].vPosition.x,
										   _v_data[_i_data[i + 1]].vPosition.y,
			                               _v_data[_i_data[i + 1]].vPosition.z);

		math::Vector3d p3 = math::Vector3d(_v_data[_i_data[i + 2]].vPosition.x,
										   _v_data[_i_data[i + 2]].vPosition.y,
										   _v_data[_i_data[i + 2]].vPosition.z);

		math::Vector3d v1 = p3 - p1;
		math::Vector3d v2 = p2 - p1;
		math::Vector3d normal = math::cross(v1,v2);
		normal.normalize();

		_v_data[_i_data[i + 0]].vNormal = normal;
		_v_data[_i_data[i + 1]].vNormal = normal;
		_v_data[_i_data[i + 2]].vNormal = normal;

		math::Vector3d tangent = cross(v1,normal);
		tangent.normalize();

		_v_data[_i_data[i + 0]].vTangent = tangent;
		_v_data[_i_data[i + 1]].vTangent = tangent;
		_v_data[_i_data[i + 2]].vTangent = tangent;

		math::Vector3d binormal = cross(tangent,normal);
		binormal.normalize();

		_v_data[_i_data[i + 0]].vBinormal = binormal;
		_v_data[_i_data[i + 1]].vBinormal = binormal;
		_v_data[_i_data[i + 2]].vBinormal = binormal;
	}
}

void Landscape::Update()
{
	RefreshMatrix();
}

void Landscape::Render()
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