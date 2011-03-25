#include "Grass.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../../Core/CGlobal.h"

using namespace Enviroment;

CGrass::CGrass()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;
}

void CGrass::ReadData(std::string _fileName)
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


void CGrass::Load(std::vector<SResource> _resource)
{
	m_MeshList["grass"] = new Core::CMesh();
	m_MeshList["grass"]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList["grass"]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();

	SResource grassResource = *_resource.begin();
	ReadData(grassResource.m_ResouceFile);
	for(unsigned int index = 0; index < K_MAX_TEXTURES_PER_MESH; ++index)
	{
		if(grassResource.m_TextureFileList[index].length())
			m_MeshList["grass"]->m_TextureArray[index] = CResource::GetTextureControllerInstance()->Load(grassResource.m_TextureFileList[index],Core::ITexture::DDS_EXT);
	}
	m_MeshList["grass"]->m_Shader = CResource::GetShaderControllerInstance()->Load(grassResource.m_ShaderFile);	

	std::vector<math::Vector3d> grassPoints;
	unsigned int vertexCount = 0;

	unsigned int grassPeriod = 4;
	unsigned int grassPeriodCount = 0;

	for(unsigned int i = 0; i < m_Width;++i)
	{
        for(unsigned int j = 0; j < m_Height;++j)
		{
			if(m_MapData[i][j] > 120 && m_MapData[i][j] < 135)
			{
				if(grassPeriod == grassPeriodCount)
				{
					grassPoints.push_back(math::Vector3d(i, ((float)m_MapData[i][j]) * 0.1f, j));
					vertexCount += 8;
					grassPeriodCount = 0;
				}
				grassPeriodCount++;
			}
		}
	}

	SVertex* v_data = (SVertex*)m_MeshList["grass"]->m_VertexBuffer->Load(vertexCount,sizeof(SVertex),0);
	unsigned int index = 0;
	float offsetX = 1.0f;
	float offsetY = 6.0f;
	float offsetZ = 1.0f;
	for(unsigned int i = 0; i < grassPoints.size(); i++)
	{
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x + offsetX, grassPoints[i].y, grassPoints[i].z);
		v_data[index].m_vTexCoord = math::Vector2d(0.0f,1.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x + offsetX, grassPoints[i].y + offsetY, grassPoints[i].z);
		v_data[index].m_vTexCoord = math::Vector2d(0.0f,0.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x - offsetX, grassPoints[i].y, grassPoints[i].z);
		v_data[index].m_vTexCoord = math::Vector2d(1.0f,1.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x - offsetX, grassPoints[i].y + offsetY, grassPoints[i].z);
		v_data[index].m_vTexCoord = math::Vector2d(1.0f,0.0f);
		index++;

		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x, grassPoints[i].y, grassPoints[i].z + offsetZ);
		v_data[index].m_vTexCoord = math::Vector2d(0.0f,1.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x, grassPoints[i].y + offsetY, grassPoints[i].z - offsetZ);
		v_data[index].m_vTexCoord = math::Vector2d(0.0f,0.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x, grassPoints[i].y, grassPoints[i].z - offsetZ);
		v_data[index].m_vTexCoord = math::Vector2d(1.0f,1.0f);
		index++;
		v_data[index].m_vPosition = math::Vector3d(grassPoints[i].x, grassPoints[i].y + offsetY, grassPoints[i].z - offsetZ);
		v_data[index].m_vTexCoord = math::Vector2d(1.0f,0.0f);
		index++;
	}

	m_MeshList["grass"]->m_VertexBuffer->CommitToVRAM(0);

	unsigned int *i_data = m_MeshList["grass"]->m_IndexBuffer->Load(vertexCount * 12);
	index = 0;
	unsigned int indexValue = 0;
	for(unsigned int i = 0; i < grassPoints.size(); i++)
	{
		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue--;

		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;

		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue--;

		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;
		i_data[index++] = indexValue; indexValue++;
	}

	m_MeshList["grass"]->m_IndexBuffer->CommitToVRAM();
}

void CGrass::Update()
{
	Matrix();

	static float fTimer = 0.0f;
	fTimer += 0.01f;

	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetMatrix(m_mWorld,"mWorld",Core::IShader::VS_SHADER);
		meshIteratorBegin->second->m_Shader->SetFloat(fTimer,"fTimer",Core::IShader::VS_SHADER);
		meshIteratorBegin++;
	}
}

void CGrass::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_NONE);
	Core::CGlobal::GetDevice()->AlphaBlendDisable();
	Core::CGlobal::GetDevice()->AlphaTestEnable();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorBegin = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator meshIteratorEnd = m_MeshList.end();

	while(meshIteratorBegin != meshIteratorEnd)
	{
		meshIteratorBegin->second->m_Shader->SetTexture(meshIteratorBegin->second->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
		meshIteratorBegin->second->Draw();
		meshIteratorBegin++;
	}

	Core::CGlobal::GetDevice()->AlphaBlendEnable();
	Core::CGlobal::GetDevice()->AlphaTestDisable();
}