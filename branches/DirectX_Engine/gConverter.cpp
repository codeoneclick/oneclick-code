#include "gConverter.h"

void gConverter::ConvertM3(const char *fileName)
{
	char *fileData = _readVertexData(fileName);

	gM3Header *header = (gM3Header*)fileData;
	gM3Tag *tags =(gM3Tag*)(fileData + header->tagsOffset);
	
	gM3VertexBlock *vertexBlock;
	short *indexBlock;

	unsigned int nVerteces;
	unsigned int nIndeces;

	bool firstIndexBlockFlag = false;

	for(unsigned int i = 0; i < header->nTags; ++i)
	{
		if((tags[i].tagName[2] == '8') && (tags[i].tagName[3] == 'U'))
		{
			nVerteces = (tags[i].blockSize)/sizeof(gM3VertexBlock);
			vertexBlock = (gM3VertexBlock*)(fileData + tags[i].blockOffset);
		}
		if((tags[i].tagName[1] == '6') && (tags[i].tagName[2] == '1') && (tags[i].tagName[3] == 'U'))
		{
			if(firstIndexBlockFlag) continue;
			firstIndexBlockFlag = true;
			nIndeces = tags[i].blockSize;
			indexBlock = (short*)(fileData + tags[i].blockOffset);
		}
	}

	_writeToGSMFile(fileName,vertexBlock,indexBlock,nVerteces,nIndeces);

	delete[] fileData;
}

void gConverter::_writeGSMHeader(FILE *file,unsigned int nVerteces, unsigned int nIndeces)
{
	gStaticModelHeader gsmHeader;
	gsmHeader.id[0] = 'g'; gsmHeader.id[1] = 's'; gsmHeader.id[2] = 'm';
	
	gsmHeader.vertexData.tagName[0] = 'v'; gsmHeader.vertexData.tagName[1] = 'd';
	gsmHeader.vertexData.dataBlockOffset = sizeof(gStaticModelHeader);
	gsmHeader.vertexData.dataBlockSize = nVerteces;

	gsmHeader.indexData.tagName[0] = 'i'; gsmHeader.indexData.tagName[1] = 'd';
	gsmHeader.indexData.dataBlockOffset = sizeof(gStaticModelHeader) + nVerteces*sizeof(gStaticModelVertexBlock);
	gsmHeader.indexData.dataBlockSize = nIndeces;

	gsmHeader.textureData.tagName[0] = 't'; gsmHeader.textureData.tagName[1] = 'd';
	gsmHeader.textureData.dataBlockOffset = sizeof(gStaticModelHeader) + nVerteces*sizeof(gStaticModelVertexBlock) + nIndeces*sizeof(short);
	gsmHeader.textureData.dataBlockSize = 0;

	fwrite(&gsmHeader,sizeof(gStaticModelHeader),1,file);
}

void gConverter::_writeToGSMFile(const char* fileName, gM3VertexBlock *vertexBlock, short *indexBlock,unsigned int nVerteces, unsigned int nIndeces)
{
	std::string newFilename = fileName;
	newFilename.erase(newFilename.length() - 3,3);
	newFilename.insert(newFilename.length(),".gsm");

	FILE *file = NULL;
	file = fopen(newFilename.c_str(),"wb");
	
	_writeGSMHeader(file,nVerteces,nIndeces);

	float divUV = 0.0f;

	for(int i = 0; i < nVerteces; i++)
	{
		fwrite(&vertexBlock[i].position.x,sizeof(float),1,file);
		fwrite(&vertexBlock[i].position.y,sizeof(float),1,file);
		fwrite(&vertexBlock[i].position.z,sizeof(float),1,file);
		
		divUV = vertexBlock[i].uv[0]/2048.0f;
		fwrite(&divUV,sizeof(float),1,file);

		divUV = vertexBlock[i].uv[1]/2048.0f;
		fwrite(&divUV,sizeof(float),1,file);
	}

	for(int i = 0; i < nIndeces; i++)
	{
		fwrite(&indexBlock[i],sizeof(short),1,file);
	}

	fclose(file);
}

void gConverter::_writeToGSMFile(const char* fileName, gM2VertexBlock *vertexBlock, short *indexBlock,unsigned int nVerteces, unsigned int nIndeces)
{
	std::string newFilename = fileName;
	newFilename.erase(newFilename.length() - 3,3);
	newFilename.insert(newFilename.length(),".gsm");

	FILE *file = NULL;
	file = fopen(newFilename.c_str(),"wb");

	_writeGSMHeader(file,nVerteces,nIndeces);

	for(int i = 0; i < nVerteces; i++)
	{
		fwrite(&vertexBlock[i].position.x,sizeof(float),1,file);
		fwrite(&vertexBlock[i].position.y,sizeof(float),1,file);
		fwrite(&vertexBlock[i].position.z,sizeof(float),1,file);
	
		fwrite(&vertexBlock[i].textCoords.x,sizeof(float),1,file);
		fwrite(&vertexBlock[i].textCoords.y,sizeof(float),1,file);
	}

	for(int i = 0; i < nIndeces; i++)
	{
		fwrite(&indexBlock[i],sizeof(short),1,file);
	}

	fclose(file);
}

char* gConverter::_readVertexData(const char* fileName)
{
	std::ifstream inStream;
	inStream.open(fileName,std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();
	return fileData;
}

char* gConverter::_readIndexData(const char* fileName)
{
	std::ifstream inStream;
	inStream.open(fileName,std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();
	return fileData;
}

void gConverter::ConvertM2(const char*fileName)
{
	char *fileVertexData = _readVertexData(fileName);
	std::string indexDataFileName = fileName;
	indexDataFileName.erase(indexDataFileName.length() - 3,3);
	indexDataFileName.insert(indexDataFileName.length(),"00.skin");
	char *fileIndexData = _readIndexData(indexDataFileName.c_str());
	
	gM2Header *header = (gM2Header*)fileVertexData;
	gM2VertexBlock* vertexBlock;
    short *indexBlock;

	unsigned int nVerteces;
	unsigned int nIndeces;
	
	nVerteces = header->nVertices;

	vertexBlock = (gM2VertexBlock*)(fileVertexData + header->ofsVertices);

	gM2IndexGeometryBlock *indexGeometryBlock = (gM2IndexGeometryBlock*)(fileIndexData);
	unsigned short *indexLookup = (unsigned short*)(fileIndexData + indexGeometryBlock->ofsIndex);
    uint16 *triangles = (uint16*)(fileIndexData + indexGeometryBlock->ofsTris);
    nIndeces = indexGeometryBlock->nTris;
    indexBlock = new short[nIndeces];

    for (unsigned int i = 0; i < nIndeces; ++i) 
        indexBlock[i] = indexLookup[triangles[i]];

	_writeToGSMFile(fileName,vertexBlock,indexBlock,nVerteces,nIndeces);

	delete[] fileVertexData;
	delete[] fileIndexData;
	delete[] indexBlock;
}