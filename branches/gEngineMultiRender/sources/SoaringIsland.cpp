#include "SoaringIsland.h"
#include "Resource.h"
#include "Game.h"
#include "Render.h"

using namespace Enviroment;

CSoaringIsland::CSoaringIsland()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;
}

void CSoaringIsland::ReadData(std::string _fileName)
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
}

void CSoaringIsland::Load(std::string _fileName)
{
	ReadData(_fileName);
	m_MeshArray["top"] = new Core::CMesh();
	m_MeshArray["top"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\grass.dds",Core::CTexture::DDS_EXT);
	m_MeshArray["top"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");
	m_MeshArray["top"]->m_VertexBuffer = new CVertexBuffer();
	m_MeshArray["top"]->m_IndexBuffer = new CIndexBuffer();

	m_MeshArray["bottom"] = new Core::CMesh();
	m_MeshArray["bottom"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::CTexture::DDS_EXT);
	m_MeshArray["bottom"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");
	m_MeshArray["bottom"]->m_VertexBuffer = new CVertexBuffer();
	m_MeshArray["bottom"]->m_IndexBuffer = new CIndexBuffer();
	
	CVertexBuffer::SVertexVTTBN* v_data_top = (CVertexBuffer::SVertexVTTBN*)m_MeshArray["top"]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(CVertexBuffer::SVertexVTTBN));
	CVertexBuffer::SVertexVTTBN* v_data_bottom = (CVertexBuffer::SVertexVTTBN*)m_MeshArray["bottom"]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(CVertexBuffer::SVertexVTTBN));
	
	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			v_data_top[index].vPosition = math::Vector3d(i*4.0f,m_MapData[i][j]*0.5f - 128.0f,j*4.0f);
			v_data_top[index].vTexCoord = math::Vector2d(static_cast<float>(i) / 16.0f,static_cast<float>(j) / 16.0f);

			if( i == 0 || j == 0 || i == (m_Width - 1) || j == (m_Height - 1))
				v_data_bottom[index].vPosition = math::Vector3d(i*4.0f,m_MapData[i][j]*0.5f - 128.0f,j*4.0f);
			else
				v_data_bottom[index].vPosition = math::Vector3d(i*4.0f,(m_MapData[i][j]*0.5f - 128.0f) * 4.0f,j*4.0f);

			v_data_bottom[index].vTexCoord = math::Vector2d(static_cast<float>(i) / 16.0f,static_cast<float>(j) / 16.0f);

			++index;
		}
   

	unsigned int index_count = (m_Width - 1)*(m_Height - 1) * 6;
	unsigned int *i_data_top = m_MeshArray["top"]->m_IndexBuffer->Load(index_count);
	unsigned int *i_data_bottom = m_MeshArray["bottom"]->m_IndexBuffer->Load(index_count);
	index = 0;
	for(unsigned int i = 0; i < (m_Width - 1); ++i)
		for(unsigned int j = 0; j < (m_Height - 1); ++j)
		{
			i_data_top[index] = i + j * m_Width;
			i_data_bottom[index] = i + j * m_Width;
            index++;
            i_data_top[index] = i + (j + 1) * m_Width;
			i_data_bottom[index] = i + (j + 1) * m_Width;
            index++;
            i_data_top[index] = i + 1 + j * m_Width;
			i_data_bottom[index] = i + 1 + j * m_Width;
            index++;

            i_data_top[index] = i + (j + 1) * m_Width;
			i_data_bottom[index] = i + (j + 1) * m_Width;
            index++;
            i_data_top[index] = i + 1 + (j + 1) * m_Width;
			i_data_bottom[index] = i + 1 + (j + 1) * m_Width;
            index++;
            i_data_top[index] = i + 1 + j * m_Width;
			i_data_bottom[index] = i + 1 + j * m_Width;
            index++;
		}
	CalculateTBN(v_data_top,i_data_top,m_Width * m_Height,index_count);
	m_MeshArray["top"]->m_VertexBuffer->CommitVRAM();
	m_MeshArray["top"]->m_IndexBuffer->CommitVRAM();
	m_MeshArray["bottom"]->m_VertexBuffer->CommitVRAM();
	m_MeshArray["bottom"]->m_IndexBuffer->CommitVRAM();
	

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

	m_MeshArray["top"]->m_VertexBuffer->SetDeclaration(declaration);
	m_MeshArray["bottom"]->m_VertexBuffer->SetDeclaration(declaration);
}

void CSoaringIsland::CalculateTBN(CVertexBuffer::SVertexVTTBN *_v_data,unsigned int *_i_data, unsigned int _vertex_count,unsigned int _index_count)
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

void CSoaringIsland::Update()
{
	m_MeshArray["top"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::CShader::VS_SHADER);
	m_MeshArray["bottom"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::CShader::VS_SHADER);
	Matrix();
}

void CSoaringIsland::Render()
{
	Core::CDevice::GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_MeshArray["top"]->m_Shader->SetTexture(*m_MeshArray["top"]->m_TextureArray[0],"Texture_01",Core::CShader::PS_SHADER);
	m_MeshArray["top"]->Draw();
	
	Core::CDevice::GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_MeshArray["bottom"]->m_Shader->SetTexture(*m_MeshArray["bottom"]->m_TextureArray[0],"Texture_01",Core::CShader::PS_SHADER);
	m_MeshArray["bottom"]->Draw();
}