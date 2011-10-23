#include "gMeshStaticContainer.h"

void gMeshStaticContainer::ReadIndexData(const char *name)
{
	FILE *file = NULL;
	file = fopen(name,"rb");
	fread(&nTextures,sizeof(unsigned short),1,file);
	this->indexInfo = new gmi[nTextures];
	for(int i = 0; i < nTextures; i++)
	{
		fread(&indexInfo[i].startIndex,sizeof(unsigned short),1,file);
		fread(&indexInfo[i].countPrimitive,sizeof(unsigned short),1,file);
	}

	fread(&nIndices,sizeof(unsigned short),1,file);
	this->_simpleIndexBuffer = new unsigned short[nIndices];
	for(int i = 0; i < nIndices; i++)
		fread(&this->_simpleIndexBuffer[i],sizeof(unsigned short),1,file);

	fclose(file);
}

void gMeshStaticContainer::ReadTextureData(const char *name)
{
	FILE *file = fopen(name,"rb");
	fread(&nTextures,sizeof(unsigned short),1,file);
	unsigned short* textureFileLength = new unsigned short[nTextures];
	this->textureColorFileName = new std::string[nTextures];
	this->textureNormalFileName = new std::string[nTextures];
	for(int i = 0; i < nTextures; i++)
	{
		fread(&textureFileLength[i],sizeof(unsigned short),1,file);
		char *tempTextureFileName = new char[textureFileLength[i]];
		for(int j = 0; j < textureFileLength[i]; j++)
			fread(&tempTextureFileName[j],sizeof(char),1,file);

		this->textureColorFileName[i] = tempTextureFileName;
		this->textureNormalFileName[i] = tempTextureFileName;
		this->textureNormalFileName[i].insert(this->textureNormalFileName[i].length() - 4,"_n");
		delete[] tempTextureFileName;
		gCore::TexturesService()->Insert(this->textureColorFileName[i], this->textureColorFileName[i]);
		gCore::TexturesService()->Insert(this->textureNormalFileName[i], this->textureNormalFileName[i]);

	}
	fclose(file);
}

void gMeshStaticContainer::ReadVertexData(const char* name)
{
	FILE *file = fopen(name,"rb");

	fread(&nVertices,sizeof(unsigned int),1,file);
	this->_simpleVertexBuffer = new gSimpleVertexFormat[nVertices];
	
	for(int i = 0; i < nVertices; i++)
	{
		fread(&this->_simpleVertexBuffer[i].position.x,sizeof(float),1,file);
		fread(&this->_simpleVertexBuffer[i].position.z,sizeof(float),1,file);
		fread(&this->_simpleVertexBuffer[i].position.y,sizeof(float),1,file);
		
		float _tempValue;
		fread(&_tempValue,sizeof(float),1,file);
		fread(&_tempValue,sizeof(float),1,file);
		fread(&_tempValue,sizeof(float),1,file);
		
		fread(&this->_simpleVertexBuffer[i].textureCoordinates.x,sizeof(float),1,file);
		fread(&this->_simpleVertexBuffer[i].textureCoordinates.y,sizeof(float),1,file);
	}
	fclose(file);
}

void gMeshStaticContainer::_WriteToDeviceVertexBuffer()
{
	gDevice::device->CreateVertexBuffer(this->nVertices*sizeof(gVertex),D3DUSAGE_WRITEONLY, NULL,D3DPOOL_DEFAULT,&vb,NULL);
	this->vb->Lock(0,this->nVertices*sizeof(gVertex), (void**)&this->_vertexBuffer,D3DLOCK_NOSYSLOCK);
	for(int i = 0; i < this->nVertices; i++)
	{
		_vertexBuffer[i].position = this->_simpleVertexBuffer[i].position;
		_vertexBuffer[i].texture  = this->_simpleVertexBuffer[i].textureCoordinates;
		_vertexBuffer[i].normal   = this->_TBNInfo[i]._normal;
		_vertexBuffer[i].tangent  = this->_TBNInfo[i]._tangent;
		_vertexBuffer[i].binormal = this->_TBNInfo[i]._binormal;
	}
	this->vb->Unlock();
}

void gMeshStaticContainer::_WriteToDeviceIndexBuffer()
{
	gDevice::device->CreateIndexBuffer( this->nIndices*sizeof(unsigned short),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&ib,NULL);
	ib->Lock(0, sizeof(unsigned short)*nIndices, (void**)&this->_indexBuffer, D3DLOCK_NOSYSLOCK);
    for (int i = 0; i<nIndices; i++)
		this->_indexBuffer[i] = this->_simpleIndexBuffer[i];
	this->ib->Unlock();
}

void gMeshStaticContainer::Load(const gResourceData *resource)
{
	this->ReadVertexData(resource->vertexFileName);
	this->ReadTextureData(resource->texturesListFileName);
	this->ReadIndexData(resource->indexFileName);

	this->_FillTexturesList();

	this->_CalculateTBN(this->nVertices,this->nIndices);

	this->_WriteToDeviceVertexBuffer();
	this->_WriteToDeviceIndexBuffer();

	std::vector<std::string>::const_iterator iEffectName = resource->effectResources.begin();
	for(;iEffectName != resource->effectResources.end(); ++iEffectName)
		this->effectsList[(*iEffectName)] =  gCore::ShadersService()->Find(*iEffectName);
}

gMeshStaticData gMeshStaticContainer::GetMeshData()
{
	gMeshStaticData _meshData;
	_meshData.vb = this->vb;
	_meshData.ib = this->ib;

	_meshData.indexInfo = this->indexInfo;

	_meshData.nIndices = this->nIndices;
	_meshData.nTextures = this->nTextures;
	_meshData.nVertices = this->nVertices;

	_meshData.texturesColorList = this->texturesColorList;
	_meshData.texturesNormalList = this->texturesNormalList;

	_meshData.effectsList = this->effectsList;

	return _meshData;
}