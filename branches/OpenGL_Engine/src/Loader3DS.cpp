#include "Loader3DS.h"

VertexBufferPtr* Loader3DS::LoadFileData(std::string value)
{
	FILE *file = fopen(value.c_str() , "rb");
	unsigned int   filePosition = 0;
	unsigned int   lFilePosition = 0;
	unsigned int   chunkSize;
	unsigned short chunkId;
	unsigned int   length = 0;
	unsigned int   triagleIndex = 0;
	unsigned int   temp = 0;

	std::vector<VertexBufferPtr*> _chunksData;
	unsigned int _chunksCount = 0;
	unsigned int _nVertecesSum     = 0;
	unsigned int _nIndecesSum      = 0;
	

	filePosition += 2 * fread(&chunkId,2,1,file);
	if(chunkId != 0x4D4D) return NULL; 
	filePosition += 4 * fread(&chunkSize,4,1,file);

	std::string _chunkName;
	std::vector<std::string> _chunkNames;

	char _char = '_';
	while(filePosition < chunkSize && lFilePosition != filePosition)
	{
		lFilePosition = filePosition;
		filePosition += 2 * fread(&chunkId,2,1,file);
		filePosition += 4 * fread(&length,4,1,file);
	
		switch(chunkId)
		{
			case 0x3d3d:break;
		    case 0x4100:break;

			case 0x4000:
				_chunkName = "";
				_char = '_';
				while(_char != '\0' && filePosition - lFilePosition < length)
				{
					filePosition += fread(&_char,1,1,file);
					if(_char != '\0')
						_chunkName += _char;
				}
				_chunkNames.push_back(_chunkName);
			break;

			case 0x4110:
				_chunksData.push_back(new VertexBufferPtr());
				unsigned short vertecesToRead;
				filePosition += 2 * fread(&vertecesToRead,2,1,file);
				(*(_chunksData.end() - 1))->vertexDataPtr = new VertexData[vertecesToRead];
				(*(_chunksData.end() - 1))->nVerteces = vertecesToRead;
				_nVertecesSum += vertecesToRead;
				for(int i = 0; i < (*(_chunksData.end() - 1))->nVerteces; ++i)
					filePosition += 12 * fread(&(*(_chunksData.end() - 1))->vertexDataPtr[i].vPosition,12,1,file);
		    break;

			case 0x4120:
				unsigned short nTriangles;
				filePosition += 2*fread(&nTriangles,2,1,file);
				(*(_chunksData.end() - 1))->indecesPtr = new unsigned int[nTriangles*3];
				(*(_chunksData.end() - 1))->nIndeces = nTriangles*3;
				triagleIndex = 0;
				for(int i = 0; i < nTriangles; ++i)
				{
					unsigned short indexValue = 0;
					filePosition += 2 * fread(&indexValue,2,1,file);
					(*(_chunksData.end() - 1))->indecesPtr[triagleIndex] = indexValue + temp;
					triagleIndex++;
					filePosition+=2*fread(&indexValue,2,1,file);
					(*(_chunksData.end() - 1))->indecesPtr[triagleIndex] = indexValue + temp;
					triagleIndex++;
					filePosition+=2*fread(&indexValue,2,1,file);
					(*(_chunksData.end() - 1))->indecesPtr[triagleIndex] = indexValue + temp;
					triagleIndex++;
					filePosition+=2*fread(&indexValue,2,1,file);
				}
				temp += (*(_chunksData.end() - 1))->nVerteces;
				_nIndecesSum += nTriangles*3;
		    break;

			case 0x4140:
				unsigned short nTextureCoords;
			    filePosition += 2 * fread(&nTextureCoords,2,1,file);
				for(int i = 0; i < nTextureCoords; ++i)
				{
					filePosition += 4*fread(&(*(_chunksData.end() - 1))->vertexDataPtr[i].vTexCoord,8,1,file);
				}
		    break;

			default:
				filePosition += length - 6;
				fseek(file,length - 6,SEEK_CUR);
			break;
		}
	}
	fclose(file);

	VertexBufferPtr *vertexBufferPtr = new VertexBufferPtr();

	vertexBufferPtr->vertexDataPtr = new VertexData[_nVertecesSum];
	vertexBufferPtr->indecesPtr = new unsigned int[_nIndecesSum];

	vertexBufferPtr->nVerteces = _nVertecesSum;
	vertexBufferPtr->nIndeces  = _nIndecesSum;

	unsigned int indexVerteces = 0;
	unsigned int indexIndeces  = 0;

	vertexBufferPtr->nChunks = _chunksData.size();

	std::vector<VertexBufferPtr*>::iterator chunkIterator = _chunksData.begin();
	unsigned int chunkIndex = 0;
	while(chunkIterator != _chunksData.end())
	{
		for(unsigned int i = 0; i < (*chunkIterator)->nVerteces; ++i)
		{
			vertexBufferPtr->vertexDataPtr[indexVerteces].vPosition.x = (*chunkIterator)->vertexDataPtr[i].vPosition.x;
			vertexBufferPtr->vertexDataPtr[indexVerteces].vPosition.y = (*chunkIterator)->vertexDataPtr[i].vPosition.z;
			vertexBufferPtr->vertexDataPtr[indexVerteces].vPosition.z = (*chunkIterator)->vertexDataPtr[i].vPosition.y;
			vertexBufferPtr->vertexDataPtr[indexVerteces].vTexCoord = (*chunkIterator)->vertexDataPtr[i].vTexCoord;
			indexVerteces++;
		}

		MeshChunkBlock* _chunkData = new MeshChunkBlock();
		_chunkData->nIndeces = (*chunkIterator)->nIndeces;
		_chunkData->indecesPtr = new unsigned int[(*chunkIterator)->nIndeces];

		for(unsigned int i = 0; i < (*chunkIterator)->nIndeces; ++i)
		{
			_chunkData->indecesPtr[i] = (*chunkIterator)->indecesPtr[i];
			vertexBufferPtr->indecesPtr[indexIndeces] = (*chunkIterator)->indecesPtr[i];
			indexIndeces++;
		}

		vertexBufferPtr->chunkIndecesPtr[_chunkNames[chunkIndex]] = _chunkData;

		delete[] (*chunkIterator)->vertexDataPtr;
		delete[] (*chunkIterator)->indecesPtr;
		delete (*chunkIterator);
		chunkIterator++;
		chunkIndex++;
	}
	_chunksData.clear();
	vertexBufferPtr->vertexBufferId = 0;
	return vertexBufferPtr;
}

void  Loader3DS::WriteInVideoMemory(VertexBufferPtr* value)
{
	VB::glCreateVB( 1, &value->vertexBufferId );							
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, value->vertexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, value->nVerteces*sizeof(VertexData), value->vertexDataPtr, GL_STATIC_DRAW_ARB );
	delete[] value->vertexDataPtr;

	/*VB::glCreateVB(1, &value->indexBufferId);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, value->indexBufferId );		
	VB::glWriteDataVB( GL_ARRAY_BUFFER_ARB, value->nIndeces*sizeof(unsigned int), value->indecesPtr, GL_STATIC_DRAW_ARB );
	
	delete[] value->indecesPtr;*/
}
	