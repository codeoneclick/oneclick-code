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

	_textures[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road.dds",type::STexture::_DDS);
	_textures[1] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\road_nh.dds",type::STexture::_DDS);
	_meshData = new type::SMesh();
	_meshData->vertexBuffer = new CVertexBuffer();
	
	CVertexBuffer::SVertexVTTBN* vertexData = (CVertexBuffer::SVertexVTTBN*)_meshData->vertexBuffer->Create(_width * _height,sizeof(CVertexBuffer::SVertexVTTBN));
	
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
	_meshData->vertexBuffer->Commit();
	_meshData->indexBuffer->Commit();
	_shader->Create("parallax");
}

void Landscape::_CalculateTBN(CVertexBuffer::SVertexVTTBN *vertexData,unsigned int *indexData, unsigned int nVerteces,unsigned int nIndeces)
{
    for(unsigned int i = 0; i < nIndeces; i += 3)
    {
		math::vector::Vector3d p1 = math::vector::Vector3d(vertexData[indexData[i + 0]].vPosition.x,
			vertexData[indexData[i + 0]].vPosition.y,
			vertexData[indexData[i + 0]].vPosition.z);

		math::vector::Vector3d p2 = math::vector::Vector3d(vertexData[indexData[i + 1]].vPosition.x,
			vertexData[indexData[i + 1]].vPosition.y,
			vertexData[indexData[i + 1]].vPosition.z);

		math::vector::Vector3d p3 = math::vector::Vector3d(vertexData[indexData[i + 2]].vPosition.x,
			vertexData[indexData[i + 2]].vPosition.y,
			vertexData[indexData[i + 2]].vPosition.z);

		math::vector::Vector3d v1 = p3 - p1;
		math::vector::Vector3d v2 = p2 - p1;
		math::vector::Vector3d normal = math::vector::Normalize(math::vector::CrossProduct(v1,v2));

		vertexData[indexData[i + 0]].vNormal = normal;
		vertexData[indexData[i + 1]].vNormal = normal;
		vertexData[indexData[i + 2]].vNormal = normal;

		math::vector::Vector3d tangent = math::vector::Normalize(math::vector::CrossProduct(v1,normal));

		vertexData[indexData[i + 0]].vTangent = tangent;
		vertexData[indexData[i + 1]].vTangent = tangent;
		vertexData[indexData[i + 2]].vTangent = tangent;

		math::vector::Vector3d binormal = math::vector::Normalize(math::vector::CrossProduct(tangent,normal));

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
		_shader->SetWVPMatrix(_mWorldViewProjection);
		_shader->SetTexture(0,_textures[0]->addr_ptr);
		_shader->SetTexture(1,_textures[1]->addr_ptr);
		// ***** DEBUG LIGHT ***** //
		static math::vector::Vector3d vLightDirection;
		static float fAngle = 0.0f;
		fAngle += 0.01f;
		vLightDirection.x = cos(fAngle);
		vLightDirection.y = 0.0f;
		vLightDirection.z = sin(fAngle);
		_shader->SetLight(vLightDirection);
		_shader->SetCamera(Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition);
		// ***** DEBUG LIGHT ***** //
		_shader->SetClip(Video::CRenderController::clipSetting.fClipInc, Video::CRenderController::clipSetting.fClipHeight);
		_meshData->vertexBuffer->Enable();
		_meshData->indexBuffer->Enable();
		glDrawElements( GL_TRIANGLES, _meshData->indexBuffer->GetNumIndeces(), GL_UNSIGNED_INT, NULL);
		_meshData->vertexBuffer->Disable();
		_meshData->vertexBuffer->Disable();
		_shader->Disable();
	}
}