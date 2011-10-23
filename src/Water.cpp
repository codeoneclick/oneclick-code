#include "Water.h"

#include "RenderController.h"

Water::Water()
{
	_width  = 256;
	_height = 256;
	_shaderStr = "water";
	_textureStr[0] = "REFLECTION";
	_textureStr[2] = "REFRACTION";
	_textureStr[1] = "Content\\textures\\water.dds";
	_mapName = "";
}

void Water::Load(std::string value, LevelIndex _index)
{
	_mapName = value;

	_vertexBufferPtr = new VertexBufferPtr();
	_vertexBufferPtr->nVerteces = Resource::MapContainer()->_waterVB->nVerteces;
	_vertexBufferPtr->vertexDataPtr = Resource::MapContainer()->_waterVB->vertexDataPtr;
	_vertexBufferPtr->vertexBufferId = Resource::MapContainer()->_waterVB->vertexBufferId;

	_vertexBufferPtr->nIndeces = (CHUNK_SIZE - 1)*(CHUNK_SIZE - 1)*6;
	_vertexBufferPtr->indecesPtr = new unsigned int[(CHUNK_SIZE - 1)*(CHUNK_SIZE - 1)*6];
	unsigned int _vertexBufferIndex = 0;

	_vertexBufferPtr->nIndeces = CHUNK_SIZE*CHUNK_SIZE*6;
	_vertexBufferPtr->indecesPtr = new unsigned int[_vertexBufferPtr->nIndeces];

	for(unsigned int i = _index.indexX * CHUNK_SIZE; i <= (_index.indexX * CHUNK_SIZE + CHUNK_SIZE - 1); ++i)
		for(unsigned int j = _index.indexY * CHUNK_SIZE; j <= (_index.indexY * CHUNK_SIZE + CHUNK_SIZE - 1); ++j)
		{
			if((i  >= (MAP_SIZE - 1)) || (j >= (MAP_SIZE - 1)))
			{
				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;
				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;
				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;

				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;
				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;
				_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
				_vertexBufferIndex++;
				continue;
			}
			_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
            _vertexBufferIndex++;
            _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + j * _width ;
            _vertexBufferIndex++;
            _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;

            _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;
            _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + j * _width;
            _vertexBufferIndex++;
            _vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + (j + 1) * _width;
            _vertexBufferIndex++;
		}

	_vertexBufferPtr->bPosition = true;
	_vertexBufferPtr->bTexCoord = true;
	_vertexBufferPtr->bExtValue = true;

	VB::glCreateVB(1, &_vertexBufferPtr->indexBufferId);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->indexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nIndeces*sizeof(unsigned int), _vertexBufferPtr->indecesPtr, GL_STATIC_DRAW_ARB );

	delete[] _vertexBufferPtr->indecesPtr;
}

void Water::Update()
{
	_UpdateWorldMatrix();
}

void Water::Render()
{
	glCullFace(GL_FRONT);
	//EnableShader("water","water");
	_UpdateShaderParams();
	//EnableVB();
	//EnableIB();
	
	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, NULL );

	VB::glBindVB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
	VB::glBindVB(GL_ARRAY_BUFFER_ARB, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	VB::glBindDataVB(GL_TEXTURE0);

	//DisableShader();
}

void Water::UpdateData(UpdateDataFlag _flag)
{
	/*VertexData *_vertexDataPtr = NULL;
	unsigned int _vertexBufferIndex = 0;
	float **_heightmap = Resource::MapContainer()->GetMapData(_mapName)->_heightmapMainData;

	switch(_flag)
	{
		case UPDATE_REFRESH :
		{
			_vertexDataPtr = _vertexBufferPtr->vertexDataPtr;
			for(unsigned int i = 0; i < _width; ++i )
				for(unsigned int j = 0; j < _height; ++j )
				{
					_vertexDataPtr[_vertexBufferIndex].vExtValue.x = _heightmap[i][j] * 0.1f + 1.0f;
					++_vertexBufferIndex;
				}
			VB::glDeleteVB(1,&_vertexBufferPtr->vertexBufferId);
			VB::glCreateVB(1, &_vertexBufferPtr->vertexBufferId);							
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId );		
			VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*sizeof(VertexData), _vertexBufferPtr->vertexDataPtr, GL_STATIC_DRAW_ARB );
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, 0 );	
		}
		break;
		case UPDATE_RECREATE :
		{
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId );	
			_vertexDataPtr = (VertexData*) VB::glLockVB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
			for(unsigned int i = 0; i < _width; ++i )
				for(unsigned int j = 0; j < _height; ++j )
				{
					_vertexDataPtr[_vertexBufferIndex].vExtValue.x = _heightmap[i][j] * 0.1f + 1.0f;
					++_vertexBufferIndex;
				}
			VB::glUnlockVB(GL_ARRAY_BUFFER_ARB);
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, 0 );	
		}
		break;
	}*/
}