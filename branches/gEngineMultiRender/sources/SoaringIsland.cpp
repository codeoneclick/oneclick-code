#include "SoaringIsland.h"
#include "Resource.h"
#include "Game.h"
#include "Render.h"
#include "Core/CGlobal.h"

using namespace Enviroment;

CSoaringIsland::CSoaringIsland()
{
	m_Width  = 256;
	m_Height = 256;
	m_MapData = NULL;

	m_TopElementHeightMult = 0.5f;
	m_BottomElementHeightMult = -2.0f;
	m_TopElementDiscardOffset = 2.0f;;
	m_BottomElementDiscardOffset = 8.0f;

	m_MapScaleFactor = 4.0f;
	m_TextureScaleFactor = 16.0f;
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
	m_MeshList["top"] = new Core::CMesh();
	m_MeshList["top"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\5684.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\7733.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_TextureArray[2] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_TextureArray[3] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\sand_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_TextureArray[4] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\grass_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_TextureArray[5] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\road_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshList["top"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");
	m_MeshList["top"]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList["top"]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();

	m_MeshList["bottom"] = new Core::CMesh();
	m_MeshList["bottom"]->m_TextureArray[0] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\5684.dds",Core::ITexture::DDS_EXT);
	m_MeshList["bottom"]->m_TextureArray[1] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\6422.dds",Core::ITexture::DDS_EXT);
	m_MeshList["bottom"]->m_TextureArray[2] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\sand_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshList["bottom"]->m_TextureArray[3] = CResource::GetTextureControllerInstance()->Load("Content\\textures\\rock_nh.dds",Core::ITexture::DDS_EXT);
	m_MeshList["bottom"]->m_Shader = CResource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");
	m_MeshList["bottom"]->m_VertexBuffer = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_MeshList["bottom"]->m_IndexBuffer = Core::CGlobal::GetDevice()->CreateIndexBuffer();
	
	SVertex* v_data_top = (SVertex*)m_MeshList["top"]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertex));
	SVertex* v_data_bottom = (SVertex*)m_MeshList["bottom"]->m_VertexBuffer->Load(m_Width * m_Height,sizeof(SVertex));

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
			v_data_top[index].vPosition = math::Vector3d(i*m_MapScaleFactor,m_MapData[i][j] * m_TopElementHeightMult - m_TopElementDiscardOffset,j*m_MapScaleFactor);
			v_data_top[index].vTexCoord = math::Vector2d(static_cast<float>(i) / m_TextureScaleFactor,static_cast<float>(j) / m_TextureScaleFactor);

			if( i == 0 || j == 0 || i == (m_Width - 1) || j == (m_Height - 1))
				v_data_bottom[index].vPosition = math::Vector3d(i*m_MapScaleFactor,m_MapData[i][j] + m_BottomElementDiscardOffset,j*m_MapScaleFactor);
			else
				v_data_bottom[index].vPosition = math::Vector3d(i*m_MapScaleFactor,m_MapData[i][j] * m_BottomElementHeightMult + m_BottomElementDiscardOffset,j*m_MapScaleFactor);

			v_data_bottom[index].vTexCoord = math::Vector2d(static_cast<float>(i) / m_TextureScaleFactor,static_cast<float>(j) / m_TextureScaleFactor);

			v_data_top[index].vSplatting = math::Vector4d(0.0f,1.0f,0.0f,0.0f);
			v_data_bottom[index].vSplatting = math::Vector4d(0.0f,1.0f,0.0f,0.0f);

			if(v_data_top[index].vPosition.y < 0.0f)
				v_data_top[index].fDiscard = -1.0f;

			if(v_data_bottom[index].vPosition.y > 0.0f)
				v_data_bottom[index].fDiscard = -1.0f;

			int splattingOffset = 2.0f;
			float splattingMult = splattingOffset * 3.0f;
			if(m_MapData[i][j] <= 32.0f)
				for(int x = (i - splattingOffset); x <= (i + splattingOffset); ++x)
					for(int z = (j - splattingOffset); z <= (j + splattingOffset); ++z)
					{
						if(x < 0 || z < 0 || (x >= m_Width) || (z >= m_Height))
							continue;
						math::Vector2d splattingFactor = math::Vector2d(static_cast<float>(x) - static_cast<float>(i), static_cast<float>(z) - static_cast<float>(j));
						v_data_bottom[index].vSplatting.x = 1.0f - splattingFactor.length() / splattingMult;
						v_data_bottom[index].vSplatting.y = 1.0f - v_data_bottom[index].vSplatting.x;
					}
			++index;
		}

	index = 0;
	for(unsigned int i = 0; i < m_Width;++i)
        for(unsigned int j = 0; j < m_Height;++j)
		{
			int splattingOffset = 2.0f;
			float splattingMult = splattingOffset * 3.0f;

			if(m_MapData[i][j] <= 32.0f)
				for(int x = (i - splattingOffset); x <= (i + splattingOffset); ++x)
					for(int z = (j - splattingOffset); z <= (j + splattingOffset); ++z)
					{
						if((x < 0) || (z < 0) || (x >= m_Width) || (z >= m_Height))
							continue;
						math::Vector2d splattingFactor = math::Vector2d(static_cast<float>(x) - static_cast<float>(i), static_cast<float>(z) - static_cast<float>(j));
						v_data_top[index].vSplatting.x = 1.0f - splattingFactor.length() / splattingMult;
						v_data_top[index].vSplatting.y = 1.0f - v_data_top[index].vSplatting.x;
					}

			if(m_MapData[i][j] >= 128.0f)
				for(int x = (i - splattingOffset); x <= (i + splattingOffset); ++x)
					for(int z = (j - splattingOffset); z <= (j + splattingOffset); ++z)
					{
						if((x < 0) || (z < 0) || (x >= m_Width) || (z >= m_Height))
							continue;
						math::Vector2d splattingFactor = math::Vector2d(static_cast<float>(x) - static_cast<float>(i), static_cast<float>(z) - static_cast<float>(j));
						v_data_top[index].vSplatting.z = 1.0f - splattingFactor.length() / splattingMult;
						v_data_top[index].vSplatting.y = 1.0f - v_data_top[index].vSplatting.z;
					}
			++index;
		}

	unsigned int index_count = (m_Width - 1)*(m_Height - 1) * 6;
	unsigned int *i_data_top = m_MeshList["top"]->m_IndexBuffer->Load(index_count);
	unsigned int *i_data_bottom = m_MeshList["bottom"]->m_IndexBuffer->Load(index_count);
	index = 0;
	for(unsigned int i = 0; i < (m_Width - 1); ++i)
		for(unsigned int j = 0; j < (m_Height - 1); ++j)
		{
			i_data_top[index] = i + j * m_Width;
			i_data_bottom[index] = i + 1 + j * m_Width;
            index++;
            i_data_top[index] = i + (j + 1) * m_Width;
			i_data_bottom[index] = i + (j + 1) * m_Width;
            index++;
            i_data_top[index] = i + 1 + j * m_Width;
			i_data_bottom[index] = i + j * m_Width;
            index++;

            i_data_top[index] = i + (j + 1) * m_Width;
			i_data_bottom[index] = i + 1 + j * m_Width;
            index++;
            i_data_top[index] = i + 1 + (j + 1) * m_Width;
			i_data_bottom[index] = i + 1 + (j + 1) * m_Width;
            index++;
            i_data_top[index] = i + 1 + j * m_Width;
			i_data_bottom[index] = i + (j + 1) * m_Width;
            index++;
		}

		Math::Util::SVertexTBN * dataTBN = Math::Util::CalculateTBN(v_data_top,i_data_top,m_Width * m_Height,index_count,sizeof(SVertex));
		for(int i = 0; i < m_Width * m_Height; ++i)
		{
			v_data_top[i].vNormal = dataTBN[i].vNormal;
			v_data_top[i].vTangent = dataTBN[i].vTangent;
			v_data_top[i].vBinormal = dataTBN[i].vBinormal;
		}
		delete[] dataTBN;

		dataTBN = Math::Util::CalculateTBN(v_data_bottom,i_data_top,m_Width * m_Height,index_count,sizeof(SVertex));
		for(int i = 0; i < m_Width * m_Height; ++i)
		{
			v_data_bottom[i].vNormal = dataTBN[i].vNormal;
			v_data_bottom[i].vNormal.normalize();
			v_data_bottom[i].vTangent = dataTBN[i].vTangent;
			v_data_bottom[i].vBinormal = dataTBN[i].vBinormal;
		}
		delete[] dataTBN;

		m_MeshList["top"]->m_VertexBuffer->CommitToVRAM();
		m_MeshList["top"]->m_IndexBuffer->CommitToVRAM();
		m_MeshList["bottom"]->m_VertexBuffer->CommitToVRAM();
		m_MeshList["bottom"]->m_IndexBuffer->CommitToVRAM();
	

	Core::IVertexBuffer::SVertexDeclaration declaration;
	declaration.m_Elements = new Core::IVertexBuffer::SElementDeclaration[7];
	
	declaration.m_Elements[0].m_Index = 0;
	declaration.m_Elements[0].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[0].m_Type = Core::IVertexBuffer::ELEMENT_POSITION;
	declaration.m_Elements[0].m_Offset = 0 * sizeof(float);

	declaration.m_Elements[1].m_Index = 0;
	declaration.m_Elements[1].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_Elements[1].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[1].m_Offset = 3 * sizeof(float);

	declaration.m_Elements[2].m_Index = 0;
	declaration.m_Elements[2].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[2].m_Type = Core::IVertexBuffer::ELEMENT_NORMAL;
	declaration.m_Elements[2].m_Offset = 5 * sizeof(float);

	declaration.m_Elements[3].m_Index = 1;
	declaration.m_Elements[3].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[3].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[3].m_Offset = 8 * sizeof(float);

	declaration.m_Elements[4].m_Index = 2;
	declaration.m_Elements[4].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_Elements[4].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[4].m_Offset = 11 * sizeof(float);

	declaration.m_Elements[5].m_Index = 3;
	declaration.m_Elements[5].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT4;
	declaration.m_Elements[5].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[5].m_Offset = 14 * sizeof(float);

	declaration.m_Elements[6].m_Index = 4;
	declaration.m_Elements[6].m_Size = Core::IVertexBuffer::ELEMENT_FLOAT;
	declaration.m_Elements[6].m_Type = Core::IVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_Elements[6].m_Offset = 18 * sizeof(float);

	declaration.m_ElementCount = 7;

	m_MeshList["top"]->m_VertexBuffer->SetDeclaration(declaration);
	m_MeshList["bottom"]->m_VertexBuffer->SetDeclaration(declaration);
}

void CSoaringIsland::Update()
{
	Matrix();

	static math::Vector3d vLightDir = math::Vector3d(0.0f, 0.0f, 0.0f);
	static float LightAngle = 0.0f;
	LightAngle += 0.01f;
	vLightDir.x = cos(LightAngle);
	vLightDir.y = 0.0f;
	vLightDir.z = sin(LightAngle);

	m_MeshList["top"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetMatrix(m_mWorldViewProjection,"mWorldViewProjection",Core::IShader::VS_SHADER);
	
	m_MeshList["top"]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetVector(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition,"vCameraEye",Core::IShader::VS_SHADER);

	m_MeshList["top"]->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetVector(vLightDir,"vLightDir",Core::IShader::VS_SHADER);
}

void CSoaringIsland::Render()
{
	float discard_dir = 1.0f;
	float discard_value = 0.0f;
	m_MeshList["top"]->m_Shader->SetFloat(discard_dir,"fDiscardUp",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetFloat(discard_value,"fDiscardHeight",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[1],"Texture_02",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[2],"Texture_03",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[3],"Texture_01_NH",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[4],"Texture_02_NH",Core::IShader::PS_SHADER);
	m_MeshList["top"]->m_Shader->SetTexture(m_MeshList["top"]->m_TextureArray[5],"Texture_03_NH",Core::IShader::PS_SHADER);
	m_MeshList["top"]->Draw();

	discard_dir = -1.0f;
	m_MeshList["bottom"]->m_Shader->SetFloat(discard_dir,"fDiscardUp",Core::IShader::PS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetFloat(discard_value,"fDiscardHeight",Core::IShader::PS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetTexture(m_MeshList["bottom"]->m_TextureArray[0],"Texture_01",Core::IShader::PS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetTexture(m_MeshList["bottom"]->m_TextureArray[1],"Texture_02",Core::IShader::PS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetTexture(m_MeshList["bottom"]->m_TextureArray[2],"Texture_01_NH",Core::IShader::PS_SHADER);
	m_MeshList["bottom"]->m_Shader->SetTexture(m_MeshList["bottom"]->m_TextureArray[3],"Texture_02_NH",Core::IShader::PS_SHADER);
	//m_MeshArray["bottom"]->Draw();
}