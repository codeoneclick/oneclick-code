#include "Landscape.h"
#include "Resource.h"
#include "Game.h"

using namespace Enviroment;

Landscape::Landscape()
{
	_width  = 256;
	_height = 256;
	_heightmap = NULL;
}

void Landscape::Load(std::string value)
{
	_heightmap = new float*[_width];
	for(unsigned int i = 0; i < _width; ++i)
	{
		_heightmap[i] = new float[_width];
		for(unsigned int j = 0; j < _height; ++j)
			_heightmap[i][j] = 0.0f;
	}

	unsigned char readValue = 0;
	FILE * file;
	file = fopen( value.c_str(), "rb" );
	for( unsigned int i = 0; i < _width; ++i )
		for( unsigned int j = 0; j < _height; ++j )
		{
			fread(&readValue,sizeof(unsigned char),1,file);
			_heightmap[i][j] = static_cast<float>(readValue);
		}
	fclose( file );



	_textures[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",Core::CTexture::DDS_EXT);
	//_textures[1] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road_nh.dds",Core::CTexture::DDS_EXT);
	_meshData = new type::SMesh();
	_meshData->vertexBuffer = new CVertexBuffer();
	
	CVertexBuffer::SVertexVTTBN* vertexData = (CVertexBuffer::SVertexVTTBN*)_meshData->vertexBuffer->Load(_width * _height,sizeof(CVertexBuffer::SVertexVTTBN));
	
	unsigned int _vertexBufferIndex = 0;
	for(unsigned int i = 0; i < _width;++i)
        for(unsigned int j = 0; j < _height;++j)
		{
			vertexData[_vertexBufferIndex].vPosition.x = i*4.0f;
			vertexData[_vertexBufferIndex].vPosition.y = _heightmap[i][j]*0.5f - 128.0f;
			vertexData[_vertexBufferIndex].vPosition.z = j*4.0f;
			vertexData[_vertexBufferIndex].vTexCoord.x = static_cast<float>(i) / 16.0f;
			vertexData[_vertexBufferIndex].vTexCoord.y = static_cast<float>(j) / 16.0f;
			++_vertexBufferIndex;
		}
	_meshData->indexBuffer = new CIndexBuffer();
	unsigned int *indexData = _meshData->indexBuffer->Create((_width - 1)*(_height - 1)*6);
	_vertexBufferIndex = 0;

	for(unsigned int i = 0; i < (_width - 1); ++i)
		for(unsigned int j = 0; j < (_height - 1); ++j)
		{
			indexData[_vertexBufferIndex] = i + j * _width;
            _vertexBufferIndex++;
            indexData[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;
            indexData[_vertexBufferIndex] = i + 1 + j * _width;
            _vertexBufferIndex++;

            indexData[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;
            indexData[_vertexBufferIndex] = i + 1 + (j + 1) * _width;
            _vertexBufferIndex++;
            indexData[_vertexBufferIndex] = i + 1 + j * _width;
            _vertexBufferIndex++;
		}
	_CalculateTBN(vertexData,indexData,_width * _height,(_width - 1)*(_height - 1)*6);
	_meshData->vertexBuffer->CommitVRAM();
	_meshData->indexBuffer->Commit();
	_shader = Resource::GetShaderControllerInstance()->Load("Content\\shaders\\basic");

	CVertexBuffer::SVertexDeclaration declaration;
	declaration.m_elements = new CVertexBuffer::SElementDeclaration[5];
	
	declaration.m_elements[0].m_index = 0;
	declaration.m_elements[0].m_size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_elements[0].m_type = CVertexBuffer::ELEMENT_POSITION;
	declaration.m_elements[0].m_offset = 0 * sizeof(float);

	declaration.m_elements[1].m_index = 0;
	declaration.m_elements[1].m_size = CVertexBuffer::ELEMENT_FLOAT2;
	declaration.m_elements[1].m_type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_elements[1].m_offset = 3 * sizeof(float);

	declaration.m_elements[2].m_index = 0;
	declaration.m_elements[2].m_size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_elements[2].m_type = CVertexBuffer::ELEMENT_NORMAL;
	declaration.m_elements[2].m_offset = 5 * sizeof(float);

	declaration.m_elements[3].m_index = 1;
	declaration.m_elements[3].m_size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_elements[3].m_type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_elements[3].m_offset = 8 * sizeof(float);

	declaration.m_elements[4].m_index = 2;
	declaration.m_elements[4].m_size = CVertexBuffer::ELEMENT_FLOAT3;
	declaration.m_elements[4].m_type = CVertexBuffer::ELEMENT_TEXCOORD;
	declaration.m_elements[4].m_offset = 11 * sizeof(float);

	declaration.m_element_count = 5;

	_meshData->vertexBuffer->SetDeclaration(declaration);
}

void Landscape::_CalculateTBN(CVertexBuffer::SVertexVTTBN *vertexData,unsigned int *indexData, unsigned int nVerteces,unsigned int nIndeces)
{
    for(unsigned int i = 0; i < nIndeces; i += 3)
    {
		math::Vector3d p1 = math::Vector3d(vertexData[indexData[i + 0]].vPosition.x,
			vertexData[indexData[i + 0]].vPosition.y,
			vertexData[indexData[i + 0]].vPosition.z);

		math::Vector3d p2 = math::Vector3d(vertexData[indexData[i + 1]].vPosition.x,
			vertexData[indexData[i + 1]].vPosition.y,
			vertexData[indexData[i + 1]].vPosition.z);

		math::Vector3d p3 = math::Vector3d(vertexData[indexData[i + 2]].vPosition.x,
			vertexData[indexData[i + 2]].vPosition.y,
			vertexData[indexData[i + 2]].vPosition.z);

		math::Vector3d v1 = p3 - p1;
		math::Vector3d v2 = p2 - p1;
		math::Vector3d normal = math::cross(v1,v2);
		normal.normalize();

		vertexData[indexData[i + 0]].vNormal = normal;
		vertexData[indexData[i + 1]].vNormal = normal;
		vertexData[indexData[i + 2]].vNormal = normal;

		math::Vector3d tangent = cross(v1,normal);
		tangent.normalize();

		vertexData[indexData[i + 0]].vTangent = tangent;
		vertexData[indexData[i + 1]].vTangent = tangent;
		vertexData[indexData[i + 2]].vTangent = tangent;

		math::Vector3d binormal = cross(tangent,normal);
		binormal.normalize();

		vertexData[indexData[i + 0]].vBinormal = binormal;
		vertexData[indexData[i + 1]].vBinormal = binormal;
		vertexData[indexData[i + 2]].vBinormal = binormal;

		/*math::vector::Vector3d v1 = math::vector::Vector3d(vertexData[indexData[i + 0]].vPosition.x,
			vertexData[indexData[i + 0]].vPosition.y,
			vertexData[indexData[i + 0]].vPosition.z);

		math::vector::Vector3d v2 = math::vector::Vector3d(vertexData[indexData[i + 1]].vPosition.x,
			vertexData[indexData[i + 1]].vPosition.y,
			vertexData[indexData[i + 1]].vPosition.z);

		math::vector::Vector3d v3 = math::vector::Vector3d(vertexData[indexData[i + 2]].vPosition.x,
			vertexData[indexData[i + 2]].vPosition.y,
			vertexData[indexData[i + 2]].vPosition.z);

		math::vector::Vector3d v2v1 = v2 - v1;
		math::vector::Vector3d v3v1 = v3 - v1;

		float c2c1_T = vertexData[indexData[i + 1]].vTexCoord.x - vertexData[indexData[i + 0]].vTexCoord.x;
		float c2c1_B = vertexData[indexData[i + 1]].vTexCoord.y - vertexData[indexData[i + 0]].vTexCoord.y;

		float c3c1_T = vertexData[indexData[i + 2]].vTexCoord.x - vertexData[indexData[i + 0]].vTexCoord.x;
		float c3c1_B = vertexData[indexData[i + 2]].vTexCoord.y - vertexData[indexData[i + 0]].vTexCoord.y;

		float fDenominator = c2c1_T * c3c1_B - c3c1_T * c2c1_B;
		if (fDenominator == 0.0f)	
		{
			int test = 0;
		}
		else
		{
			float fScale1 = 1.0f / fDenominator;
			math::vector::Vector3d tangent = math::vector::Vector3d((c3c1_B * v2v1.x - c2c1_B * v3v1.x) * fScale1,
																    (c3c1_B * v2v1.y - c2c1_B * v3v1.y) * fScale1,
																	(c3c1_B * v2v1.z - c2c1_B * v3v1.z) * fScale1);

			math::vector::Vector3d binormal = math::vector::Vector3d((-c3c1_T * v2v1.x + c2c1_T * v3v1.x) * fScale1,
																	 (-c3c1_T * v2v1.y + c2c1_T * v3v1.y) * fScale1,
																	 (-c3c1_T * v2v1.z + c2c1_T * v3v1.z) * fScale1);

			math::vector::Vector3d normal = math::vector::CrossProduct(tangent,binormal);


			float fScale2 = 1.0f / ((tangent.x * binormal.y * normal.z - tangent.z * binormal.y * normal.x) + 
									(binormal.x * normal.y * tangent.z - binormal.z * normal.y * tangent.x) + 
									(normal.x * tangent.y * binormal.z - normal.z * tangent.y * binormal.x));

			math::vector::Vector3d tangentTBN = math::vector::Normalize(math::vector::Vector3d(math::vector::CrossProduct(binormal,normal).x * fScale2,
				-math::vector::CrossProduct(normal,tangent).x * fScale2,
				math::vector::CrossProduct(tangent,binormal).x * fScale2));
			
			math::vector::Vector3d binormalTBN = math::vector::Normalize(math::vector::Vector3d(-math::vector::CrossProduct(binormal,normal).y * fScale2,
				math::vector::CrossProduct(normal,tangent).y * fScale2,
				-math::vector::CrossProduct(tangent,binormal).y * fScale2));
			
			math::vector::Vector3d normalTBN = math::vector::Normalize(math::vector::Vector3d(math::vector::CrossProduct(binormal,normal).z * fScale2,
				-math::vector::CrossProduct(normal,tangent).z * fScale2, 
				math::vector::CrossProduct(tangent,binormal).z * fScale2));
		
			vertexData[indexData[i + 0]].vNormal = normalTBN;
			vertexData[indexData[i + 1]].vNormal = normalTBN;
			vertexData[indexData[i + 2]].vNormal = normalTBN;

			vertexData[indexData[i + 0]].vTangent = tangentTBN;
			vertexData[indexData[i + 1]].vTangent = tangentTBN;
			vertexData[indexData[i + 2]].vTangent = tangentTBN;

			vertexData[indexData[i + 0]].vBinormal = binormalTBN;
			vertexData[indexData[i + 1]].vBinormal = binormalTBN;
			vertexData[indexData[i + 2]].vBinormal = binormalTBN;
		}*/
	}
}

void Landscape::Update()
{
	_UpdateMatrix();
}

void Landscape::Render()
{
	bool _shaderRender = true;
	if(_shaderRender)
	{
		_shader->Enable();
		_shader->SetMatrix(_mWorldViewProjection,"mWorldViewProjection",Core::CShader::VS_SHADER);
		_shader->SetTexture(*_textures[0],"Texture_01",Core::CShader::PS_SHADER);
		//_shader->SetWVPMatrix(_mWorldViewProjection);
		//_shader->SetTexture(0,_textures[0]->addr_ptr);
		//_shader->SetTexture(1,_textures[1]->addr_ptr);

		//_shader->SetClip(Video::CRenderController::clipSetting.fClipInc, Video::CRenderController::clipSetting.fClipHeight);

		// ***** DEBUG LIGHT ***** //
		math::Vector3d vCameraPosition = Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
		static math::Vector4d vLightPosition_01;
		math::Vector3d vColor_01 = math::Vector3d(1.0f,0.0f,0.0f);
		static float fAngle = 0.0f;
		fAngle += 0.01f;
		vLightPosition_01.x = vCameraPosition.x + cos(fAngle) * 128.0f;
		vLightPosition_01.y = vCameraPosition.y;
		vLightPosition_01.z = vCameraPosition.z + sin(fAngle) * 128.0f;
		vLightPosition_01.w = 32.0f;
		//_shader->SetLight_01(vLightPosition_01,vColor_01);

		static math::Vector4d vLightPosition_02;
		math::Vector3d vColor_02 = math::Vector3d(1.0f,1.0f,0.0f);
		vLightPosition_02.x = vCameraPosition.x + cos(fAngle * 2.0f) * 256.0f;
		vLightPosition_02.y = vCameraPosition.y;
		vLightPosition_02.z = vCameraPosition.z + sin(fAngle * 2.0f) * 256.0f;
		vLightPosition_02.w = 32.0f;
		//_shader->SetLight_02(vLightPosition_02,vColor_02);

		static math::Vector4d vLightPosition_03;
		math::Vector3d vColor_03 = math::Vector3d(0.0f,0.0f,1.0f);
		vLightPosition_03.x = vCameraPosition.x + cos(fAngle / 2.0f) * 512.0f;
		vLightPosition_03.y = vCameraPosition.y;
		vLightPosition_03.z = vCameraPosition.z + sin(fAngle / 2.0f) * 512.0f;
		vLightPosition_03.w = 32.0f;
		//_shader->SetLight_03(vLightPosition_03,vColor_03);

		//_shader->SetCamera(vCameraPosition);

		//Extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB,GL_WRITE_ONLY_ARB);
		// ***** DEBUG LIGHT ***** //
		_meshData->vertexBuffer->Enable();
		_meshData->indexBuffer->Enable();
		//Extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB,GL_WRITE_ONLY_ARB);
		//Extension::VBExtension::glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		glDrawElements( GL_TRIANGLES, _meshData->indexBuffer->GetNumIndeces(), GL_UNSIGNED_INT, NULL);
		_meshData->vertexBuffer->Disable();
		_meshData->vertexBuffer->Disable();
		_shader->Disable();
	}
}