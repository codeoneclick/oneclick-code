#include "MapService.h"
#include "Utility.h"

MapService::MapService(char *filename)
{
	_ReadMapFile(filename);
	_tilesetContainer["box"] = Loader3DS::LoadFileData("Content\\models\\Box.3ds");

	_heightmapIB = new IndexBufferEnv**[MAP_SIZE / CHUNK_SIZE];
	_waterIB     = new IndexBufferEnv**[MAP_SIZE / CHUNK_SIZE];
	_grassIB     = new IndexBufferEnv**[MAP_SIZE / CHUNK_SIZE];

	for(unsigned int i = 0; i < MAP_SIZE / CHUNK_SIZE; ++i)
	{
		_heightmapIB[i] = new IndexBufferEnv*[MAP_SIZE / CHUNK_SIZE];
		_waterIB[i]     = new IndexBufferEnv*[MAP_SIZE / CHUNK_SIZE];
		_grassIB[i]     = new IndexBufferEnv*[MAP_SIZE / CHUNK_SIZE];
		for(unsigned int j = 0; j < MAP_SIZE / CHUNK_SIZE; ++j)
		{
			_heightmapIB[i][j] = NULL;
			_waterIB[i][j]     = NULL;
			_grassIB[i][j]     = NULL;
		}
	}

	_WriteHeightmapVBInVideoMemory();
	_WriteWaterVBInVideoMemory();
	_WriteGrassVBInVideoMemory();
}

void MapService::_ReadMapFile(char *filename)
{
	_heightmap = new float*[MAP_SIZE];
	for(unsigned int i = 0; i < MAP_SIZE; ++i)
	{
		_heightmap[i] = new float[MAP_SIZE];
		for(unsigned int j = 0; j < MAP_SIZE; ++j)
				_heightmap[i][j] = 0.0f;
	}

	unsigned char byteReadValue = 0;
	FILE * file;
	file = fopen( filename, "rb" );
	for( unsigned int i = 0; i < MAP_SIZE; ++i )
		for( unsigned int j = 0; j < MAP_SIZE; ++j )
		{
			fread(&byteReadValue,sizeof(unsigned char),1,file);
			_heightmap[i][j] = (float)byteReadValue;
			if(( i > 110 && i < 124) || ( i > 128 && i < 142))     // #TODO : remove
				if(( j > 120 && j < 124) || ( j > 128 && j < 132))
						_heightmap[i][j] = -1.0f;
		}
	fclose( file );
}

void MapService::_WriteHeightmapVBInVideoMemory()
{
	std::vector<VertexData*> _preVertexDataPtr;

	for(unsigned int i = 0; i < MAP_SIZE;++i)
        for(unsigned int j = 0; j < MAP_SIZE;++j)
		{
			VertexData *_preVertexData = new VertexData();
			
			_preVertexData->vPosition.x = i;
			_preVertexData->vPosition.z = j;

			_preVertexData->vPosition.y = _heightmap[i][j]*HEIGHTMAP_LEVEL;

			if(((i + 1) < MAP_SIZE ) && 
			   (( j + 1) < MAP_SIZE) &&
			   (( i - 1) > 0)        &&
			   (( j - 1) > 0))
			for(unsigned int _i = (i - 1); _i < ( i + 1); ++_i)
				for(unsigned int _j = (j - 1); _j < ( j + 1); ++_j)
					if(_heightmap[_i][_j] < 0.0f)
						_preVertexData->vPosition.y = 32.0f;	    // #TODO :	remove

			_preVertexData->vTexCoord.x = i/(float)MAP_SIZE * 8.0f;
			_preVertexData->vTexCoord.y = j/(float)MAP_SIZE * 8.0f;
			_preVertexDataPtr.push_back(_preVertexData);
		}

	for(unsigned int nVerteces = 0; nVerteces < _tilesetContainer["box"]->nVerteces; ++nVerteces)  // # TODO : remove
	{
		if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.x < 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.x = 0.0f;
		else if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.x > 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.x = 1.0f;

		if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.z < 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.z = 0.0f;
		else if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.z > 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.z = 1.0f;

		if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.y < 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.y = 0.0f;
		else if(_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.y > 0.0f)
			_tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.y = 1.0f;
	}

	for(unsigned int i = 0; i < MAP_SIZE;++i)
        for(unsigned int j = 0; j < MAP_SIZE;++j)
			if(_heightmap[i][j] < 0.0f)
			{
				for(unsigned int nVerteces = 0; nVerteces < _tilesetContainer["box"]->nVerteces; ++nVerteces)
				{
					VertexData *_preVertexData = new VertexData();
					_preVertexData->vPosition.x = _tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.x + i;
					_preVertexData->vPosition.z = _tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.z + j;
					_preVertexData->vPosition.y = _tilesetContainer["box"]->vertexDataPtr[nVerteces].vPosition.y + 32.0f;

					_preVertexData->vTexCoord.x = _tilesetContainer["box"]->vertexDataPtr[nVerteces].vTexCoord.x;
					_preVertexData->vTexCoord.y = _tilesetContainer["box"]->vertexDataPtr[nVerteces].vTexCoord.y;

					_preVertexData->vExtValue.x = 0.0f;
					_preVertexData->vExtValue.y = 1.0f;
					_preVertexData->vExtValue.z = 0.0f;

					_preVertexDataPtr.push_back(_preVertexData);
				}
			}

	_heightmapVB = new VertexBufferEnv();
	_heightmapVB->nVerteces = _preVertexDataPtr.size();

	_heightmapVB->vertexDataPtr = new VertexData[_heightmapVB->nVerteces];

	for(unsigned int i = 0; i < _heightmapVB->nVerteces; ++i)
		_heightmapVB->vertexDataPtr[i] = *_preVertexDataPtr[i];

	_preVertexDataPtr.clear();
	
	unsigned int _vertexBufferIndex = 0;

    for(unsigned int i = 0; i < MAP_SIZE; ++i)
        for(unsigned int j = 0; j < MAP_SIZE; ++j)
        {
			 _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f;
			 _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.y = 0.0f;
			 _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.z = 0.0f;

             if(_heightmap[i][j] <= 128.0f)
                for(unsigned int x = (i - 10); x <= (i + 10); ++x)
                    for(unsigned int z = (j - 10); z <= (j + 10); ++z)
                    {
                       if((x < 0) || (z < 0) || (x >= MAP_SIZE) || (z >= MAP_SIZE))
                           continue;
                       Vector3d colorTilePower = Vector3d(x - i, 0.0f ,z - j);
					   _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.z = 1.0f - Length(colorTilePower)/32.0f;
					   _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f - _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.z;
                     }

                        if(_heightmap[i][j] >= 184.0f)
                            for(unsigned int x = (i - 5); x <= (i + 5); ++x)
                               for(unsigned int z = (j - 5); z <= (j + 5); ++z)
                               {
                                   if((x < 0) || (z < 0) || (x >= MAP_SIZE) || (z >= MAP_SIZE))
                                        continue;
                                   Vector3d colorTilePower = Vector3d(x - i, 0.0f, z - j);
								   _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.y = 1.0f - Length(colorTilePower)/16.0f;
								   _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = 1.0f - _heightmapVB->vertexDataPtr[_vertexBufferIndex].vExtValue.y;
                               }
				   _vertexBufferIndex++;
                }

	for(unsigned int i = 0; i < MAP_SIZE / CHUNK_SIZE; ++i)
	{
		for(unsigned int j = 0; j < MAP_SIZE / CHUNK_SIZE; ++j)
		{
			_WriteHeightmapIBInVideoMemory(i, j);
			_CalculateTBN(_heightmapIB[i][j]->nIndeces,_heightmapVB->vertexDataPtr,_heightmapIB[i][j]->indecesPtr);
		}
	}

	_WriteTilesetIBInVideoMemory();

	VB::glCreateVB(1, &_heightmapVB->vertexBufferId);							
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _heightmapVB->vertexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _heightmapVB->nVerteces*sizeof(VertexData), _heightmapVB->vertexDataPtr, GL_STATIC_DRAW_ARB );
}

void MapService::_WriteWaterVBInVideoMemory()
{
	_waterVB = new VertexBufferEnv();
	_waterVB->nVerteces = MAP_SIZE*MAP_SIZE;

	_waterVB->vertexDataPtr = new VertexData[_waterVB->nVerteces];

	unsigned int _vertexBufferIndex = 0;
	for(unsigned int i = 0; i < MAP_SIZE;++i)
        for(unsigned int j = 0; j < MAP_SIZE;++j)
		{
			_waterVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = i;
			_waterVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = WATER_LEVEL;
			_waterVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = j;

			_waterVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = i/(float)MAP_SIZE*4.0f;
			_waterVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = j/(float)MAP_SIZE*4.0f;
			_waterVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = _heightmap[i][j]*HEIGHTMAP_LEVEL + 1.0f;

			++_vertexBufferIndex;
		}

	VB::glCreateVB(1, &_waterVB->vertexBufferId);							
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _waterVB->vertexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _waterVB->nVerteces*sizeof(VertexData), _waterVB->vertexDataPtr, GL_STATIC_DRAW_ARB );
}

void MapService::_WriteGrassVBInVideoMemory()
{
	unsigned int _grassPeriod_01  = 5;
	unsigned int _grassPeriod_02  = 5;
	unsigned int _grassPerionCount = 0;

	for(unsigned int i = 0; i < MAP_SIZE; ++i )
        for(unsigned int j = 0; j < MAP_SIZE; ++j )
		{
			  if(_heightmap[i][j] * HEIGHTMAP_LEVEL >= WATER_LEVEL &&  _heightmap[i][j] * HEIGHTMAP_LEVEL <= GRASS_01_LEVEL)
			  {
				  if(_grassPerionCount == _grassPeriod_01)
				  {
				    GrassParam _grassParam; 
					float offsetX = Utility::GetRandomFromRange(1,10)/10.0f;
					float offsetZ = Utility::GetRandomFromRange(1,10)/10.0f;
					_grassParam.vPosition.x = i + offsetX;
					_grassParam.vPosition.y = _heightmap[i][j] * HEIGHTMAP_LEVEL - 0.2f;
					_grassParam.vPosition.z = j + offsetZ;
					_grassParam.iType = 1;
					_grassParam.fWidth  = 1.6f + Utility::GetRandomFromRange(1,10)/10.0f;
					_grassParam.fHeight = 4.2f + Utility::GetRandomFromRange(1,10)/10.0f;

					grassPositionList.push_back(_grassParam);
					_grassPerionCount = 0;
				  }
				  _grassPerionCount++;
			  }
			  else if ( _heightmap[i][j] * HEIGHTMAP_LEVEL > GRASS_01_LEVEL &&  _heightmap[i][j] * HEIGHTMAP_LEVEL <= GRASS_02_LEVEL)
			  {
				  if(_grassPerionCount == _grassPeriod_02)
				  {
				    GrassParam _grassParam; 
					float offsetX = Utility::GetRandomFromRange(1,10)/10.0f;
					float offsetZ = Utility::GetRandomFromRange(1,10)/10.0f;
					_grassParam.vPosition.x = i + offsetX;
					_grassParam.vPosition.y = _heightmap[i][j] * HEIGHTMAP_LEVEL - 0.2f;
					_grassParam.vPosition.z = j + offsetZ;
					_grassParam.iType = -1;
					_grassParam.fWidth  = 0.2f + Utility::GetRandomFromRange(1,10)/10.0f;
					_grassParam.fHeight = 1.2f + Utility::GetRandomFromRange(1,10)/10.0f;

					grassPositionList.push_back(_grassParam);
					_grassPerionCount = 0;
				  }
				  _grassPerionCount++;
			  }
		}

	_grassVB = new VertexBufferEnv();
	_grassVB->nVerteces = grassPositionList.size() * 8;

	_grassVB->vertexDataPtr = new VertexData[_grassVB->nVerteces];

	unsigned int _vertexBufferIndex = 0;

	for(unsigned int i = 0; i < grassPositionList.size(); ++i)
	{
		//  Vertex 0 of plane 0
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x +  grassPositionList[i].fWidth;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 1 of plane 0
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x +  grassPositionList[i].fWidth;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y +  grassPositionList[i].fHeight;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 2 of plane 0
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x -  grassPositionList[i].fWidth;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 3 of plane 0
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x -  grassPositionList[i].fWidth;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y + grassPositionList[i].fHeight;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;


		//  Vertex 0 of plane 1
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z +  grassPositionList[i].fWidth; 

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 1 of plane 1
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y + grassPositionList[i].fHeight;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z +  grassPositionList[i].fWidth;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 2 of plane 1
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z -  grassPositionList[i].fWidth;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
		//  Vertex 3 of plane 1
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.x = grassPositionList[i].vPosition.x;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.y = grassPositionList[i].vPosition.y + grassPositionList[i].fHeight;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vPosition.z = grassPositionList[i].vPosition.z -  grassPositionList[i].fWidth;

		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.x = 1.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vTexCoord.y = 0.0f;
		_grassVB->vertexDataPtr[_vertexBufferIndex].vExtValue.x = grassPositionList[i].iType;
		_vertexBufferIndex++;
	}

	VB::glCreateVB(1, &_grassVB->vertexBufferId);							
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _grassVB->vertexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _grassVB->nVerteces*sizeof(VertexData), _grassVB->vertexDataPtr, GL_STATIC_DRAW_ARB );
}

void MapService::_WriteHeightmapIBInVideoMemory(unsigned int indexX, unsigned int indexY)
{
	std::vector<unsigned int> _preCountIndexBuffer;

	for(unsigned int i = indexX * CHUNK_SIZE; i <= (indexX * CHUNK_SIZE + CHUNK_SIZE - 1); ++i)
		for(unsigned int j = indexY * CHUNK_SIZE; j <= (indexY * CHUNK_SIZE + CHUNK_SIZE - 1); ++j)
		{
			if((i  >= (MAP_SIZE - 1)) || (j >= (MAP_SIZE - 1)))
			{
				if(_heightmap[j][i] < 0.0f)
					continue;

				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				
				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
				continue;
			}

			if(_heightmap[j][i] < 0.0f)
				continue;
			
			_preCountIndexBuffer.push_back(i + j * MAP_SIZE);
            _preCountIndexBuffer.push_back(i + 1 + j * MAP_SIZE);
            _preCountIndexBuffer.push_back(i + (j + 1) * MAP_SIZE);

            _preCountIndexBuffer.push_back(i + (j + 1) * MAP_SIZE);
            _preCountIndexBuffer.push_back(i + 1 + j * MAP_SIZE);
            _preCountIndexBuffer.push_back(i + 1 + (j + 1) * MAP_SIZE);
		}
	_heightmapIB[indexX][indexY] = new IndexBufferEnv();
	_heightmapIB[indexX][indexY]->nIndeces = _preCountIndexBuffer.size();
	_heightmapIB[indexX][indexY]->indecesPtr = new unsigned int[_heightmapIB[indexX][indexY]->nIndeces];

	for(unsigned int i = 0; i < _heightmapIB[indexX][indexY]->nIndeces; ++i)
		_heightmapIB[indexX][indexY]->indecesPtr[i] = _preCountIndexBuffer[i];

	_preCountIndexBuffer.clear();

	VB::glCreateVB(1, &_heightmapIB[indexX][indexY]->indexBufferId);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _heightmapIB[indexX][indexY]->indexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _heightmapIB[indexX][indexY]->nIndeces*sizeof(unsigned int), _heightmapIB[indexX][indexY]->indecesPtr, GL_STATIC_DRAW_ARB );
}

void MapService::_WriteWaterIBInVideoMemory(unsigned int indexX, unsigned int indexY)
{

}

void MapService::_WriteGrassIBInVideoMemory(unsigned int indexX, unsigned int indexY)
{

}

void MapService::_WriteTilesetIBInVideoMemory()
{
	std::vector<unsigned int> _preCountIndexBuffer;

	unsigned int deltaIndex = MAP_SIZE * MAP_SIZE;
	for(unsigned int i = 0; i <= MAP_SIZE - 1; ++i)
		for(unsigned int j = 0; j <= MAP_SIZE - 1; ++j)
			if(_heightmap[i][j] < 0.0f)
			{
				for(unsigned int index = 0; index < _tilesetContainer["box"]->nIndeces; ++index)
					_preCountIndexBuffer.push_back(_tilesetContainer["box"]->indecesPtr[index] + deltaIndex);
				deltaIndex += _tilesetContainer["box"]->nVerteces;
			}

	_tilesetIB = new IndexBufferEnv();
	_tilesetIB->nIndeces = _preCountIndexBuffer.size();
	_tilesetIB->indecesPtr = new unsigned int[_tilesetIB->nIndeces];

	for(unsigned int i = 0; i < _tilesetIB->nIndeces; ++i)
		_tilesetIB->indecesPtr[i] = _preCountIndexBuffer[i];

	_CalculateTBN(_tilesetIB->nIndeces,_heightmapVB->vertexDataPtr,_tilesetIB->indecesPtr);

	VB::glCreateVB(1, &_tilesetIB->indexBufferId);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, _tilesetIB->indexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, _tilesetIB->nIndeces*sizeof(unsigned int), _tilesetIB->indecesPtr, GL_STATIC_DRAW_ARB );
}

void MapService::_CalculateTBN(unsigned int nIndeces,VertexData *valueVB, unsigned int *valueIB)
{
    for( int i = 0; i < nIndeces; i += 3 )
    {
		Vector3d p1 = Vector3d(valueVB[valueIB[i + 0]].vPosition.x,
							   valueVB[valueIB[i + 0]].vPosition.y,
							   valueVB[valueIB[i + 0]].vPosition.z);

		Vector3d p2 = Vector3d(valueVB[valueIB[i + 1]].vPosition.x,
							   valueVB[valueIB[i + 1]].vPosition.y,
							   valueVB[valueIB[i + 1]].vPosition.z);

		Vector3d p3 = Vector3d(valueVB[valueIB[i + 2]].vPosition.x,
							   valueVB[valueIB[i + 2]].vPosition.y,
							   valueVB[valueIB[i + 2]].vPosition.z);

		Vector3d v1 = p2 - p1;
		Vector3d v2 = p3 - p1;
		Vector3d normal = Normalize(CrossProduct(v1,v2));

		valueVB[valueIB[i + 0]].vNormal = normal;
		valueVB[valueIB[i + 1]].vNormal = normal;
		valueVB[valueIB[i + 2]].vNormal = normal;

		Vector3d tangent =  Normalize(CrossProduct(v1,normal));

		valueVB[valueIB[i + 0]].vTangent = tangent;
		valueVB[valueIB[i + 1]].vTangent = tangent;
		valueVB[valueIB[i + 2]].vTangent = tangent;

		Vector3d binormal =  Normalize(CrossProduct(tangent,normal));

		valueVB[valueIB[i + 0]].vBinormal = binormal;
		valueVB[valueIB[i + 1]].vBinormal = binormal;
		valueVB[valueIB[i + 2]].vBinormal = binormal;
	}
}