#include "Heightmap.h"

Heightmap::Heightmap()
{
	_heightmap = NULL;
	_shaderStr = "multitex";
	_textureStr[0] = "Content\\textures\\grass.dds";
	_textureStr[1] = "Content\\textures\\rock.dds";
	_textureStr[2] = "Content\\textures\\sand.dds";
	_textureStr[3] = "Content\\textures\\grass_nh.dds";
	_textureStr[4] = "Content\\textures\\rock_nh.dds";
	_textureStr[5] = "Content\\textures\\sand_nh.dds";
	_mapName = "";
}

void Heightmap::Load(std::string value, LevelIndex _index)
{
	_mapName = value;
	Resource::MapContainer();
	_vertexBufferPtr = new VertexBufferPtr();
	_vertexBufferPtr->nVerteces      = Resource::MapContainer()->_heightmapVB->nVerteces;
	_vertexBufferPtr->vertexDataPtr  = Resource::MapContainer()->_heightmapVB->vertexDataPtr;
	_vertexBufferPtr->vertexBufferId = Resource::MapContainer()->_heightmapVB->vertexBufferId;

	_vertexBufferPtr->indexBufferId  = Resource::MapContainer()->_heightmapIB[_index.indexX][_index.indexY]->indexBufferId;
	_vertexBufferPtr->nIndeces       = Resource::MapContainer()->_heightmapIB[_index.indexX][_index.indexY]->nIndeces;

	_vertexBufferPtr->bPosition = true;
	_vertexBufferPtr->bTexCoord = true;
	_vertexBufferPtr->bNormal   = true;
	_vertexBufferPtr->bTangent  = true;
	_vertexBufferPtr->bBinormal = true;
	_vertexBufferPtr->bExtValue = true;
}

void Heightmap::Update()
{
	_UpdateWorldMatrix();
}

void Heightmap::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_UpdateShaderParams();
	cgGLSetParameter1f( _cgShaderParams.cg_fReflectionPass, _clipPlaneValue );

	glCullFace(GL_FRONT);

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, NULL );

	glDisable(GL_BLEND);
}

void Heightmap::UpdateData(UpdateDataFlag _flag)
{
	/*VertexData *_vertexDataPtr = NULL;
	unsigned int _vertexBufferIndex = 0;
	float **_heightmap = Resource::MapContainer()->GetMapData(_mapName)->_heightmapMainData;

	switch(_flag)
	{
		case UPDATE_RECREATE :
		{
			_vertexDataPtr = _vertexBufferPtr->vertexDataPtr;
			for(unsigned int i = 0; i < _width; ++i )
				for(unsigned int j = 0; j < _height; ++j )
				{
					_vertexDataPtr[_vertexBufferIndex].vPosition.y = _heightmap[i][j] * 0.1f + 1.0f;
					++_vertexBufferIndex;
				}
			VB::glDeleteVB(1,&_vertexBufferPtr->vertexBufferId);
			VB::glCreateVB(1, &_vertexBufferPtr->vertexBufferId);							
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId );		
			VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*sizeof(VertexData), _vertexBufferPtr->vertexDataPtr, GL_STATIC_DRAW_ARB );
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, 0 );	
		}
		break;
		case UPDATE_REFRESH:
		{
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId );	
			_vertexDataPtr = (VertexData*) VB::glLockVB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
			for(unsigned int i = 0; i < _width; ++i )
				for(unsigned int j = 0; j < _height; ++j )
				{
					_vertexDataPtr[_vertexBufferIndex].vPosition.y = _heightmap[i][j] * 0.1f + 1.0f;
					++_vertexBufferIndex;
				}
			VB::glUnlockVB(GL_ARRAY_BUFFER_ARB);
			VB::glBindVB( GL_ARRAY_BUFFER_ARB, 0 );	
		}
		break;
	}*/
}