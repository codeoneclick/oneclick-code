#include "Landscape.h"
#include "../../Resource/Manager/Resource.h"
#include "../Game.h"
#include "../../Core/CGlobal.h"

using namespace Enviroment;

CLandscape::CLandscape()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;
	m_ChunkSize = 32;

	m_MapScaleFactor = 1.0f;
	m_TextureScaleFactor = 32.0f;
	m_MapHeightFactor = 0.1f;
	m_Name = "landscape_";
	m_FirstChunkName = "landscape_0";

	m_intersectBlock = NULL;
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
			if(i == 0 || j == 0 || i == ( m_Width - 1) || j == ( m_Height - 1))
				m_MapData[i][j] = 0.0f;
		}
	fclose( file );
}

void CLandscape::Load(std::vector<SResource> _resource)
{
	SResource landscapeResource = *_resource.begin();
	ReadData(landscapeResource.m_ResouceFile);
	int chunkIndex = 0; 
	for(unsigned int i = 0; i < m_Width / m_ChunkSize; ++i)
		for(unsigned int j = 0; j < m_Height / m_ChunkSize; ++j)
		{
			char str[32];
			itoa(chunkIndex, str, 10);
			std::string strIndex(str);
			m_MeshList[m_Name + strIndex] = new Core::CMesh();
			for(unsigned int k = 0; k < K_MAX_TEXTURES_PER_MESH; k++)
			{
				if(landscapeResource.m_TextureFileList[k].length())
				{
					m_MeshList[m_Name + strIndex]->m_TextureArray[k] = CResource::GetTextureControllerInstance()->Load(landscapeResource.m_TextureFileList[k],Core::ITexture::DDS_EXT);
				}
			}
			m_MeshList[m_Name + strIndex]->m_Shader = CResource::GetShaderControllerInstance()->Load(landscapeResource.m_ShaderFile);
			m_MeshList[m_Name + strIndex]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
			m_MeshList[m_Name + strIndex]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
			
			SChunk chunk;
			chunk.m_bVisible = true;
			chunk.m_Index.x = i;
			chunk.m_Index.y = j;
			m_ChunkArray[m_Name + strIndex] = chunk;

			chunkIndex++;
		}

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

	m_intersectBlock = new Enviroment::CIntersectController::SIntersectBlock();
	m_intersectBlock->vertexData = new math::Vector3d[m_Width * m_Height];

	SVertexStreamMesh* v_data = (SVertexStreamMesh*)m_MeshList[m_FirstChunkName]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertexStreamMesh),0);
	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			v_data[index].m_vPosition = math::Vector3d(i*m_MapScaleFactor,m_MapData[i][j] * m_MapHeightFactor,j*m_MapScaleFactor);
			v_data[index].m_vTexCoord = math::Vector2d<float>(static_cast<float>(i) / m_TextureScaleFactor,static_cast<float>(j) / m_TextureScaleFactor);
			m_intersectBlock->vertexData[index] = v_data[index].m_vPosition;
			++index;
		}

	unsigned int index_count = (m_Width - 1)*(m_Height - 1) * 6;
	unsigned int *i_data = new unsigned int[index_count];

	m_intersectBlock->nIndeces = index_count;
	m_intersectBlock->indexData = new unsigned int[index_count];

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

	memcpy(m_intersectBlock->indexData,i_data, index_count * sizeof(unsigned int));
	Game::GetEnviromentControllerInstance()->GetIntersectControllerInstance()->AddIntersectBlock(m_FirstChunkName,m_intersectBlock);

	Math::Util::SVertexTBN * dataTBN = Math::Util::CalculateTBN(v_data,i_data,m_Width * m_Height,index_count,sizeof(SVertexStreamMesh));
	for(int i = 0; i < m_Width * m_Height; ++i)
	{
		dataTBN[i].vNormal.normalize();
		v_data[i].m_vNormal = -dataTBN[i].vNormal;

		dataTBN[i].vTangent.normalize();
		v_data[i].m_vTangent = -dataTBN[i].vTangent;
	}
	delete[] dataTBN;

	delete[] i_data;

	m_MeshList[m_FirstChunkName]->m_VertexBuffer->CommitToVRAM(0);

	SVertexStreamSplatting* v_data1 = (SVertexStreamSplatting*)m_MeshList[m_FirstChunkName]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertexStreamSplatting),1);
	index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			v_data1[index].m_vSplatting = 0x00000000;
			if(v_data[index].m_vPosition.y > 13.0f)
				v_data1[index].m_vSplatting = 0x0000FF00;
			else
				v_data1[index].m_vSplatting = 0x00FF0000;
			++index;
		}
	m_MeshList[m_FirstChunkName]->m_VertexBuffer->CommitToVRAM(1);

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[5];
	
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

	declaration.m_Elements[2].m_stream = 0;
	declaration.m_Elements[2].m_index = 1;
	declaration.m_Elements[2].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[2].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[2].m_offset = 20;

	declaration.m_Elements[3].m_stream = 0;
	declaration.m_Elements[3].m_index = 2;
	declaration.m_Elements[3].m_size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[3].m_type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[3].m_offset = 32;

	declaration.m_Elements[4].m_stream = 1;
	declaration.m_Elements[4].m_index = 0;
	declaration.m_Elements[4].m_size = Core::IVertexBuffer::ELEMENT_BYTE4;
	declaration.m_Elements[4].m_type = Core::IVertexBuffer::ELEMENT_COLOR;
	declaration.m_Elements[4].m_offset = 0;

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
			m_MeshList[m_Name + strIndex]->m_VertexBuffer->CopyVertexBufferRef(m_MeshList[m_FirstChunkName]->m_VertexBuffer,0,0);
			m_MeshList[m_Name + strIndex]->m_VertexBuffer->SetDeclaration(declaration);
			chunkIndex++;
		}
}

void CLandscape::Update()
{
	Matrix();

	std::map<std::string,Core::CMesh*>::iterator beginMeshIterator = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator endMeshIterator = m_MeshList.end();

	std::map<std::string,SChunk>::iterator beginChunkIterator = m_ChunkArray.begin();
	std::map<std::string,SChunk>::iterator endChunkIterator = m_ChunkArray.end();

	while(beginMeshIterator != endMeshIterator && beginChunkIterator != endChunkIterator)
	{
		if(!Game::GetEnviromentControllerInstance()->GetCameraInstance()->IsBoundingSphereInFrustum(beginChunkIterator->second.m_Index.x * m_ChunkSize + m_ChunkSize / 2, beginChunkIterator->second.m_Index.y * m_ChunkSize + m_ChunkSize / 2, m_ChunkSize))
		{
			beginChunkIterator->second.m_bVisible = false;
			beginMeshIterator++;
			beginChunkIterator++;
			continue;
		}
		beginMeshIterator->second->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
		beginMeshIterator->second->m_Shader->SetMatrix(m_mWorld,"mWorld",Core::IShader::VS_SHADER);
		beginMeshIterator->second->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
		beginMeshIterator->second->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetLightInstance()->GetDirection(),"vLightDir",Core::IShader::VS_SHADER);

		beginChunkIterator->second.m_bVisible = true;
		beginMeshIterator++;
		beginChunkIterator++;
	}
}

void CLandscape::Render()
{
	Core::CGlobal::GetDevice()->SetCullFace(Core::IDevice::CULL_CW);
	Core::CGlobal::GetDevice()->AlphaBlendDisable();
	Core::CGlobal::GetDevice()->AlphaTestDisable();

	std::map<std::string,Core::CMesh*>::iterator beginMeshIterator = m_MeshList.begin();
	std::map<std::string,Core::CMesh*>::iterator endMeshIterator = m_MeshList.end();

	std::map<std::string,SChunk>::iterator beginChunkIterator = m_ChunkArray.begin();
	std::map<std::string,SChunk>::iterator endChunkIterator = m_ChunkArray.end();

	while(beginMeshIterator != endMeshIterator && beginChunkIterator != endChunkIterator)
	{
		if(!beginChunkIterator->second.m_bVisible)
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
		beginMeshIterator->second->Draw();

		beginMeshIterator++;
		beginChunkIterator++;
	}
}

void CLandscape::RefreshVB(int _streamId)
{
	SVertexStreamMesh* vertexData = (SVertexStreamMesh*)m_MeshList[m_FirstChunkName]->m_VertexBuffer->Lock(_streamId);
	//unsigned int* indexData = m_MeshList[m_FirstChunkName]->m_IndexBuffer->Lock();
	//Math::Util::SVertexTBN * dataTBN = Math::Util::CalculateTBN(vertexData,indexData,m_Width * m_Height,m_MeshList[m_FirstChunkName]->m_IndexBuffer->GetIndexCount(),sizeof(SVertexStreamMesh));
	unsigned int index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			vertexData[index].m_vPosition.y = m_MapData[i][j] * m_MapHeightFactor;
			m_intersectBlock->vertexData[index].y = vertexData[index].m_vPosition.y;
			/*dataTBN[index].vNormal.normalize();

			vertexData[index].m_cNormalX = (unsigned char)(((dataTBN[index].vNormal.x + 1) / 2) * 255);
			vertexData[index].m_cNormalY = (unsigned char)(((dataTBN[index].vNormal.y + 1) / 2) * 255);
			vertexData[index].m_cNormalZ = (unsigned char)(((dataTBN[index].vNormal.z + 1) / 2) * 255);
			vertexData[index].m_cNormalW = 0;

			dataTBN[index].vTangent.normalize();

			vertexData[index].m_cTangentX = (unsigned char)(((dataTBN[index].vTangent.x + 1) / 2) * 255);
			vertexData[index].m_cTangentY = (unsigned char)(((dataTBN[index].vTangent.y + 1) / 2) * 255);
			vertexData[index].m_cTangentZ = (unsigned char)(((dataTBN[index].vTangent.z + 1) / 2) * 255);
			vertexData[index].m_cTangentW = 0;*/

			++index;
		}
	//delete[] dataTBN;

	m_MeshList[m_FirstChunkName]->m_VertexBuffer->Unlock(_streamId);
	//m_MeshList[m_FirstChunkName]->m_IndexBuffer->Unlock();
}

void CLandscape::DrawTraces(float _x, float _z)
{
	SVertexStreamSplatting *vertexData = (SVertexStreamSplatting*)m_MeshList[m_FirstChunkName]->m_VertexBuffer->Lock(1);
	vertexData[(int)_x * m_Width+ (int)_z].m_vSplatting = 0x000000FF;
	m_MeshList[m_FirstChunkName]->m_VertexBuffer->Unlock(1);
}