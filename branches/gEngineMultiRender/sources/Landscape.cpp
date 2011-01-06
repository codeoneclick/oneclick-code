#include "Landscape.h"
#include "Resource.h"
#include "Game.h"
#include "Render.h"
#include "Core/CGlobal.h"

using namespace Enviroment;

CLandscape::CLandscape()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;
	m_ChunkSize = 64;

	m_MapScaleFactor = 1.0f;
	m_TextureScaleFactor = 16.0f;
	m_MapHeightFactor = 0.1f;
	m_Name = "landscape_";
	m_FirstChunkName = "landscape_0";
}

void CLandscape::ReadData(std::string _fileName)
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

void CLandscape::Load(std::vector<SResource> _resource)
{
	ReadData("Content\\maps\\map.raw");
	int chunkIndex = 0; 
	for(unsigned int i = 0; i < m_Width / m_ChunkSize; ++i)
		for(unsigned int j = 0; j < m_Height / m_ChunkSize; ++j)
		{
			char str[32];
			itoa(chunkIndex, str, 10);
			std::string strIndex(str);
			m_MeshList[m_Name + strIndex] = new Core::CMesh();
			m_MeshList[m_Name + strIndex]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\sand.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\grass.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[2] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[3] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\sand_nh.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[4] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\grass_nh.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[5] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road_nh.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_TextureArray[6] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\grid_mask.dds",Core::ITexture::DDS_EXT);
			m_MeshList[m_Name + strIndex]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");
			m_MeshList[m_Name + strIndex]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
			m_MeshList[m_Name + strIndex]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
			
			SChunk chunk;
			chunk.bVisible = true;
			chunk.index.x = i;
			chunk.index.y = j;
			m_ChunkArray[m_Name + strIndex] = chunk;

			chunkIndex++;
		}
	
	SVertex* v_data = (SVertex*)m_MeshList[m_FirstChunkName]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertex));

	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
            if(i <= 0 || j <= 0 || i >= (m_Width - 1) || j >= (m_Height - 1)) continue;
            float currentHeight = m_MapData[i][j];
            float middleHeight = 0.0f;
            middleHeight = currentHeight;
            middleHeight += m_MapData[i-1][j];
            middleHeight += m_MapData[i+1][j];
            middleHeight += m_MapData[i-1][j-1];
            middleHeight += m_MapData[i][j-1];
            middleHeight += m_MapData[i+1][j-1];
            middleHeight += m_MapData[i-1][j+1];
            middleHeight += m_MapData[i][j+1];
            middleHeight += m_MapData[i+1][j+1];
            currentHeight = middleHeight / 9.0f;
            currentHeight = floor(currentHeight + 0.5f);
            m_MapData[i][j] = currentHeight;
         }

	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			
			v_data[index].vPosition = math::Vector3d(i*m_MapScaleFactor,m_MapData[i][j] * m_MapHeightFactor,j*m_MapScaleFactor);
			v_data[index].vTexCoord = math::Vector2d(static_cast<float>(i) / m_TextureScaleFactor,static_cast<float>(j) / m_TextureScaleFactor);
			v_data[index].vSplatting = 0x00000000;
			if(v_data[index].vPosition.y > 13.0f)
				v_data[index].vSplatting = 0x0000FF00;
			else
				v_data[index].vSplatting = 0x00FF0000;
			++index;
		}


	unsigned int index_count = (m_Width - 1)*(m_Height - 1) * 6;
	unsigned int *i_data = new unsigned int[index_count];
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

	Math::Util::SVertexTBN * dataTBN = Math::Util::CalculateTBN(v_data,i_data,m_Width * m_Height,index_count,sizeof(SVertex));
	for(int i = 0; i < m_Width * m_Height; ++i)
	{
		dataTBN[i].vNormal.normalize();

		v_data[i].NormalX = (unsigned char)(((dataTBN[i].vNormal.x + 1) / 2) * 255);
		v_data[i].NormalY = (unsigned char)(((dataTBN[i].vNormal.y + 1) / 2) * 255);
		v_data[i].NormalZ = (unsigned char)(((dataTBN[i].vNormal.z + 1) / 2) * 255);
		v_data[i].NormalW = 0;

		dataTBN[i].vTangent.normalize();

		v_data[i].TangentX = (unsigned char)(((dataTBN[i].vTangent.x + 1) / 2) * 255);
		v_data[i].TangentY = (unsigned char)(((dataTBN[i].vTangent.y + 1) / 2) * 255);
		v_data[i].TangentZ = (unsigned char)(((dataTBN[i].vTangent.z + 1) / 2) * 255);
		v_data[i].TangentW = 0;
	}
	delete[] dataTBN;

	delete[] i_data;

	m_MeshList[m_FirstChunkName]->m_VertexBuffer->CommitToVRAM();

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[5];
	
	declaration.m_Elements[0].m_Index = 0;
	declaration.m_Elements[0].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_Type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_Offset = 0;

	declaration.m_Elements[1].m_Index = 0;
	declaration.m_Elements[1].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_Offset = 12;

	declaration.m_Elements[2].m_Index = 0;
	declaration.m_Elements[2].m_Size = Core::IVertexBuffer::ELEMENT_BYTE4;
	declaration.m_Elements[2].m_Type = Core::IVertexBuffer::ELEMENT_COLOR;
	declaration.m_Elements[2].m_Offset = 20;

	declaration.m_Elements[3].m_Index = 1;
	declaration.m_Elements[3].m_Size = Core::IVertexBuffer::ELEMENT_BYTE4;
	declaration.m_Elements[3].m_Type = Core::IVertexBuffer::ELEMENT_COLOR;
	declaration.m_Elements[3].m_Offset = 24;

	declaration.m_Elements[4].m_Index = 2;
	declaration.m_Elements[4].m_Size = Core::IVertexBuffer::ELEMENT_BYTE4;
	declaration.m_Elements[4].m_Type = Core::IVertexBuffer::ELEMENT_COLOR;
	declaration.m_Elements[4].m_Offset = 28;

	declaration.m_ElementCount = 5;

	chunkIndex = 0;
	for(unsigned int _i = 0; _i < m_Width / m_ChunkSize; ++_i)
		for(unsigned int _j = 0; _j < m_Height / m_ChunkSize; ++_j)
		{
			char str[32];
			itoa(chunkIndex, str, 10);
			std::string strIndex(str);
			i_data = m_MeshList[m_Name + strIndex]->m_IndexBuffer->Load(m_ChunkSize * m_ChunkSize * 6);
			index = 0;
			for(unsigned int i = _i * m_ChunkSize; i <= ( _i * m_ChunkSize + m_ChunkSize - 1); ++i)
				for(unsigned int j = _j * m_ChunkSize; j <= ( _j * m_ChunkSize + m_ChunkSize - 1); ++j)
				{
					if((i  >= (m_Width - 1)) || (j >= (m_Width - 1)))
					{
						i_data[index] = i + j * m_Width;
						index++;
						i_data[index] = i + j * m_Width;
						index++;
						i_data[index] = i + j * m_Width;
						index++;
					
						i_data[index] = i + j * m_Width;
						index++;
						i_data[index] = i + j * m_Width;
						index++;
						i_data[index] = i + j * m_Width;
						index++;
						continue;
					}

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
			m_MeshList[m_Name + strIndex]->m_IndexBuffer->CommitToVRAM();
			m_MeshList[m_Name + strIndex]->m_VertexBuffer->AdoptVertexBuffer(m_MeshList[m_FirstChunkName]->m_VertexBuffer);
			m_MeshList[m_Name + strIndex]->m_VertexBuffer->SetDeclaration(declaration);
			chunkIndex++;
		}
}

void CLandscape::Update()
{
	Matrix();

	static math::Vector3d vLightDir = math::Vector3d(0.0f, 0.0f, 0.0f);
	static float LightAngle = 0.0f;
	LightAngle += 0.001f;
	vLightDir.x = cos(LightAngle);
	vLightDir.y = 0.0f;
	vLightDir.z = sin(LightAngle);

	std::map<std::string,Core::CMesh*>::iterator beginMeshIterator = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator endMeshIterator = m_MeshList.end();

	std::map<std::string,SChunk>::iterator beginChunkIterator = m_ChunkArray.begin();
	std::map<std::string,SChunk>::iterator endChunkIterator = m_ChunkArray.end();

	while(beginMeshIterator != endMeshIterator && beginChunkIterator != endChunkIterator)
	{
		if(!Game::GetEnviromentControllerInstance()->GetCameraInstance()->IsBoundingSphereInFrustum(beginChunkIterator->second.index.x * m_ChunkSize + m_ChunkSize / 2, beginChunkIterator->second.index.y * m_ChunkSize + m_ChunkSize / 2, m_ChunkSize))
		{
			beginChunkIterator->second.bVisible = false;
			beginMeshIterator++;
			beginChunkIterator++;
			continue;
		}
		beginMeshIterator->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
		beginMeshIterator->second->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
		beginMeshIterator->second->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);

		beginChunkIterator->second.bVisible = true;
		beginMeshIterator++;
		beginChunkIterator++;
	}
}

void CLandscape::Render()
{
	Core::CGlobal::GetRender()->SetCullFace(Core::IRender::CULL_CW);

	std::map<std::string,Core::CMesh*>::iterator beginMeshIterator = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator endMeshIterator = m_MeshList.end();

	std::map<std::string,SChunk>::iterator beginChunkIterator = m_ChunkArray.begin();
	std::map<std::string,SChunk>::iterator endChunkIterator = m_ChunkArray.end();

	while(beginMeshIterator != endMeshIterator && beginChunkIterator != endChunkIterator)
	{
		if(!beginChunkIterator->second.bVisible)
		{
			beginMeshIterator++;
			beginChunkIterator++;
			continue;
		}
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[1],"Texture_02",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[2],"Texture_03",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[3],"Texture_01_NH",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[4],"Texture_02_NH",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[5],"Texture_03_NH",Core::IShader::PS_SHADER);
		beginMeshIterator->second->m_Shader->SetTexture(beginMeshIterator->second->m_TextureArray[6],"Texture_grid_mask",Core::IShader::PS_SHADER);
		beginMeshIterator->second->Draw();

		beginMeshIterator++;
		beginChunkIterator++;
	}
}