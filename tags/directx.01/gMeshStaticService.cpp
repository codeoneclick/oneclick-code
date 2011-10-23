#include "gMeshStaticService.h"

void gMeshStaticService::Load()
{
	WIN32_FIND_DATA FindFileData; 
	HANDLE hFind = INVALID_HANDLE_VALUE; 
	char *DirSpec = "Content\\models\\*.gmv";
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		//error
	}else
	{
		this->_AddStaticMesh(FindFileData.cFileName);
		while(FindNextFile(hFind, &FindFileData) != 0)
			this->_AddStaticMesh(FindFileData.cFileName);
	}

FindClose(hFind);

}

void gMeshStaticService::_AddStaticMesh(std::string fileName)
{
		std::string _sMainMeshFileName   = "";
		std::string _sVertexMeshFileName = "Content\\models\\";
		std::string _sIndexMeshFileName  = "Content\\models\\";
		std::string _sInfoMeshFileName   = "Content\\models\\";

		_sMainMeshFileName = fileName;
		_sMainMeshFileName.erase(_sMainMeshFileName.length() - 4,4);

		_sVertexMeshFileName.insert(_sVertexMeshFileName.length(),_sMainMeshFileName);
		_sVertexMeshFileName.insert(_sVertexMeshFileName.length(),".gmv");

		_sIndexMeshFileName.insert(_sIndexMeshFileName.length(),_sMainMeshFileName);
		_sIndexMeshFileName.insert(_sIndexMeshFileName.length(),".gmi");

		_sInfoMeshFileName.insert(_sInfoMeshFileName.length(),_sMainMeshFileName);
		_sInfoMeshFileName.insert(_sInfoMeshFileName.length(),".gmt");

		char *_cMainMeshFileName = new char[_sMainMeshFileName.length()];
		char *_cVertexMeshFileName = new char[_sVertexMeshFileName.length()];
		char *_cIndexMeshFileName = new char[_sIndexMeshFileName.length()];
		char *_cInfoMeshFileName = new char[_sInfoMeshFileName.length()];
		
		strcpy(_cMainMeshFileName,_sMainMeshFileName.c_str());
		strcpy(_cVertexMeshFileName,_sVertexMeshFileName.c_str());
		strcpy(_cIndexMeshFileName,_sIndexMeshFileName.c_str());
		strcpy(_cInfoMeshFileName,_sInfoMeshFileName.c_str());
		
		Insert(_sMainMeshFileName,_cVertexMeshFileName,_cInfoMeshFileName,_cIndexMeshFileName);
		this->_meshName.push_back(_sMainMeshFileName);
}


void gMeshStaticService::Insert(std::string key,char* name_v,char* name_t,char* name_i)
{
	gMeshStaticContainer *_mesh = new gMeshStaticContainer();
	gResourceData resource;
	resource.vertexFileName = name_v;
	resource.texturesListFileName = name_t;
	resource.indexFileName = name_i;
	resource.currentEffectName = "mesh_effect";
	resource.effectResources.push_back("mesh_effect");
	resource.effectResources.push_back("shadow_effect");
	_mesh->Load(&resource);
	_meshesContainer.insert(std::pair<std::string,gMeshStaticContainer*>(key,_mesh));
}

gMeshStaticContainer* gMeshStaticService::Find(std::string name)
{
	std::map<std::string,gMeshStaticContainer*>::iterator meshIterator;
	meshIterator = this->_meshesContainer.find(name);
	if(meshIterator != this->_meshesContainer.end())
		return meshIterator->second;
	else
		return NULL;
}