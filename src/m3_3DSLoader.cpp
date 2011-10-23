#include "m3_3DSLoader.h"

PFNGLGENBUFFERSARBPROC m3_3DSLoader::glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC m3_3DSLoader::glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC m3_3DSLoader::glBufferDataARB = NULL;
PFNGLDELETEBUFFERSARBPROC m3_3DSLoader::glDeleteBuffersARB = NULL;


void m3_3DSLoader::Initilize()
{
	if(glGenBuffersARB == NULL)
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	if(glBindBufferARB == NULL)
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	if(glBufferDataARB == NULL)
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	if(glDeleteBuffersARB == NULL)
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
}

m3_VertexBufferPtr* m3_3DSLoader::LoadFileData(std::string value)
{
	FILE *file = fopen(value.c_str() , "rb");
	unsigned int   filePosition = 0;
	unsigned int   lFilePosition = 0;
	unsigned int   chunkSize;
	unsigned short chunkId;
	unsigned int   length = 0;
	unsigned int   triagleIndex = 0;
	unsigned int   temp = 0;

	std::vector<m3_VertexBufferPtr*> _chunksData;
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
				//if(_chunksData.size() > 0 && (*_chunksData.begin())->vertexDataPtr != NULL) break;
				_chunksData.push_back(new m3_VertexBufferPtr());
				unsigned short vertecesToRead;
				filePosition += 2 * fread(&vertecesToRead,2,1,file);
				(*(_chunksData.end() - 1))->vertexDataPtr = new m3_VertexData[vertecesToRead];
				(*(_chunksData.end() - 1))->normalDataPtr = new m3_NormalData[vertecesToRead];	
				(*(_chunksData.end() - 1))->nVerteces = vertecesToRead;
				_nVertecesSum += vertecesToRead;
				for(int i = 0; i < (*(_chunksData.end() - 1))->nVerteces; ++i)
					filePosition += 12 * fread(&(*(_chunksData.end() - 1))->vertexDataPtr[i],12,1,file);
		    break;

			case 0x4120:
				//if(_chunksData.size() > 0 && (*_chunksData.begin())->indecesPtr != NULL) break;
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
				//if(_chunksData.size() > 0 && (*_chunksData.begin())->textureCoordPtr != NULL) break;
				unsigned short nTextureCoords;
			    filePosition += 2 * fread(&nTextureCoords,2,1,file);
				(*(_chunksData.end() - 1))->textureCoordPtr = new m3_TextureCoordData[vertecesToRead];
				for(int i = 0; i < nTextureCoords; ++i)
				{
					filePosition += 4*fread(&(*(_chunksData.end() - 1))->textureCoordPtr[i],8,1,file);
				}
		    break;

			default:
				filePosition += length - 6;
				fseek(file,length - 6,SEEK_CUR);
			break;
		}
	}
	fclose(file);

	m3_VertexBufferPtr *vertexBufferPtr = new m3_VertexBufferPtr();
	vertexBufferPtr->vertexDataPtr = new m3_VertexData[_nVertecesSum];
	vertexBufferPtr->normalDataPtr = new m3_NormalData[_nVertecesSum];
	vertexBufferPtr->textureCoordPtr = new m3_TextureCoordData[_nVertecesSum];

	vertexBufferPtr->indecesPtr = new unsigned int[_nIndecesSum];

	vertexBufferPtr->nVerteces = _nVertecesSum;
	vertexBufferPtr->nIndeces  = _nIndecesSum;

	unsigned int indexVerteces = 0;
	unsigned int indexIndeces  = 0;

	vertexBufferPtr->nChunks = _chunksData.size();

	std::vector<m3_VertexBufferPtr*>::iterator chunkIterator = _chunksData.begin();
	unsigned int chunkIndex = 0;
	while(chunkIterator != _chunksData.end())
	{
		for(unsigned int i = 0; i < (*chunkIterator)->nVerteces; ++i)
		{
			vertexBufferPtr->vertexDataPtr[indexVerteces].x = (*chunkIterator)->vertexDataPtr[i].x;
			vertexBufferPtr->vertexDataPtr[indexVerteces].y = (*chunkIterator)->vertexDataPtr[i].z;
			vertexBufferPtr->vertexDataPtr[indexVerteces].z = (*chunkIterator)->vertexDataPtr[i].y;
			vertexBufferPtr->normalDataPtr[indexVerteces] = (*chunkIterator)->normalDataPtr[i];
			vertexBufferPtr->textureCoordPtr[indexVerteces] = (*chunkIterator)->textureCoordPtr[i];
			indexVerteces++;
		}

		m3_ChunkData* _chunkData = new m3_ChunkData();
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
		delete[] (*chunkIterator)->normalDataPtr;
		delete[] (*chunkIterator)->textureCoordPtr;
		delete[] (*chunkIterator)->indecesPtr;
		delete (*chunkIterator);
		chunkIterator++;
		chunkIndex++;
	}
	_chunksData.clear();
	return vertexBufferPtr;
}

void m3_3DSLoader::_CalculateNormals(m3_VertexBufferPtr* _vertexBufferPtr)
{
	float v1[3];
	float v2[3];
	float normal[3];

	for( int i = 0; i < _vertexBufferPtr->nIndeces; i += 3 )
	{
		//if(d_Indeces[i] > nVerteces) 
		//	continue;

		v1[0] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+1]].x - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].x;
		v1[1] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+1]].y - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].y;
		v1[2] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+1]].z - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].z;

		v2[0] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+2]].x - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].x;
		v2[1] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+2]].y - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].y;
		v2[2] = _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i+2]].z - _vertexBufferPtr->vertexDataPtr[_vertexBufferPtr->indecesPtr[i]].z;

		normal[0] =  v1[1] * v2[2] - v1[2] * v2[1];
		normal[1] =  v2[0] * v1[2] - v2[2] * v2[0];
		normal[2] =  v1[0] * v2[1] - v1[1] * v2[0];

		float vLength = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));
		normal[0] /= vLength;
		normal[1] /= vLength;
		normal[2] /= vLength;

		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i]].x = normal[0];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i]].y = normal[1];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i]].z = normal[2];

		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 1]].x = normal[0];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 1]].y = normal[1];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 1]].z = normal[2];

		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 2]].x = normal[0];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 2]].y = normal[1];
		_vertexBufferPtr->normalDataPtr[_vertexBufferPtr->indecesPtr[i + 2]].z = normal[2];
	}
}


m3_VertexBufferID*  m3_3DSLoader::Load(m3_VertexBufferPtr* value)
{
	if(glGenBuffersARB == NULL)
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	if(glBindBufferARB == NULL)
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	if(glBufferDataARB == NULL)
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	if(glDeleteBuffersARB == NULL)
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

	_CalculateNormals(value);

	m3_VertexBufferID* vertexBufferId = new m3_VertexBufferID();

	glGenBuffersARB( 1, &vertexBufferId->vertexId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->vertexId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->vertexDataPtr, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &vertexBufferId->textureCoordId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->textureCoordId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*2*sizeof(float), value->textureCoordPtr, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &vertexBufferId->normalId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertexBufferId->normalId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, value->nVerteces*3*sizeof(float), value->normalDataPtr, GL_STATIC_DRAW_ARB );

	return vertexBufferId;
}
	