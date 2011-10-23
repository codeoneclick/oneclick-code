#include "LevelService.h"

LevelService::LevelService()
{

}

void LevelService::Load(std::string &name)
{
	LoadHeightmapVB(name);
	for(unsigned int i = 0; i < MAP_WIDTH/CHUNK_WIDTH; ++i)
		for(unsigned int j = 0; j < MAP_HEIGHT/CHUNK_HEIGHT; ++j)
		{
			LevelChunk* _levelChunk = new LevelChunk();
			LevelIndex  _levelIndex;
			_levelIndex.indexX = i;
			_levelIndex.indexY = j;
			_levelChunk->Load(_heightmapVertexData, name, _levelIndex);
			_levelChunkContainer.push_back(_levelChunk);
		}
}

void LevelService::Update(RenderTextureType _renderType)
{
	std::vector<LevelChunk*>::iterator _beginIterator = _levelChunkContainer.begin();
	std::vector<LevelChunk*>::iterator _endIterator = _levelChunkContainer.end();
	while(_beginIterator != _endIterator)
	{
		(*_beginIterator)->Update(_renderType);
		++_beginIterator;
	}
}

void LevelService::Render(RenderTextureType _renderType)
{
	std::vector<LevelChunk*>::iterator _beginIterator = _levelChunkContainer.begin();
	std::vector<LevelChunk*>::iterator _endIterator = _levelChunkContainer.end();
	while(_beginIterator != _endIterator)
	{
		(*_beginIterator)->Render(_renderType);
		++_beginIterator;
	}
}

void LevelService::LoadHeightmapVB(std::string &name)
{
	float **_heightmap = Resource::MapContainer()->GetMapData(name)->_heightmapData;

	_heightmapVertexData = new VertexBufferPtrExt();
	_heightmapVertexData->nVerteces = MAP_WIDTH * MAP_HEIGHT;

	_heightmapVertexData->vertexDataPtr = new VertexData[_heightmapVertexData->nVerteces];

	unsigned int _vertexBufferIndex = 0;

	for(unsigned int a = 0; a < MAP_WIDTH/CHUNK_WIDTH; ++a)
		for(unsigned int b = 0; b < MAP_HEIGHT/CHUNK_HEIGHT; ++b)
	{

	for(unsigned int i = a * CHUNK_WIDTH; i < (CHUNK_WIDTH + CHUNK_WIDTH * a);++i)
		for(unsigned int j = b * CHUNK_HEIGHT; j < (CHUNK_HEIGHT + CHUNK_HEIGHT * b);++j)
		{
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vPosition.x = i;
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vPosition.y = _heightmap[i][j]*0.1f;
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vPosition.z = j;

			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = i/(float)MAP_WIDTH*4.0f;
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = j/(float)MAP_HEIGHT*4.0f;

			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.z = 0.0f;
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.y = 0.0f;
			_heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f;

			++_vertexBufferIndex;
		}

		/*_vertexBufferIndex = 0;
        for(unsigned int i = 0; i < MAP_WIDTH; ++i)
          for(unsigned int j = 0; j < MAP_HEIGHT; ++j)
          {
			  _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f;
             if(_heightmap[i][j] <= 120.0f)
                for(unsigned int x = (i - 10); x <= (i + 10); ++x)
                    for(unsigned int z = (j - 10); z <= (j + 10); ++z)
                    {
                       if((x < 0) || (z < 0) || (x >= MAP_WIDTH) || (z >= MAP_HEIGHT))
                           continue;
                       Vector3d colorTilePower = Vector3d(x - i, 0.0f ,z - j);
					   _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.z = 1.0f - Length(colorTilePower)/32.0f;
					   _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f - _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.z;
                     }

                        if(_heightmap[i][j] >= 164.0f)
                            for(unsigned int x = (i - 5); x <= (i + 5); ++x)
                               for(unsigned int z = (j - 5); z <= (j + 5); ++z)
                               {
                                   if((x < 0) || (z < 0) || (x >= MAP_WIDTH) || (z >= MAP_HEIGHT))
                                        continue;
                                   Vector3d colorTilePower = Vector3d(x - i, 0.0f, z - j);
								   _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.y = 1.0f - Length(colorTilePower)/16.0f;
								   _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f - _heightmapVertexData->vertexDataPtr[_vertexBufferIndex].vExtValue.y;
                               }
				   _vertexBufferIndex++;
                }*/
		}

	VB::glCreateVB(1, &_heightmapVertexData->vertexBufferId);							
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _heightmapVertexData->vertexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _heightmapVertexData->nVerteces*sizeof(VertexData), _heightmapVertexData->vertexDataPtr, GL_STATIC_DRAW_ARB );
}