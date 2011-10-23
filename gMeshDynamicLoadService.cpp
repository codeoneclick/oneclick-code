#include "gMeshDynamicLoadService.h"

void gMeshDynamicLoadService::Load()
{
	this->_AddStaticMesh("knight.md2");
	this->_AddStaticMesh("zombi.md2");
}

void gMeshDynamicLoadService::_AddStaticMesh(std::string fileName)
{
		std::string _sMainMeshFileName   = "";
		std::string _sVertexMeshFileName = "Content\\models\\";
		std::string _sTextureMeshFileName  = "Content\\textures\\";

		_sMainMeshFileName = fileName;
		_sMainMeshFileName.erase(_sMainMeshFileName.length() - 4,4);

		_sVertexMeshFileName.insert(_sVertexMeshFileName.length(),_sMainMeshFileName);
		_sVertexMeshFileName.insert(_sVertexMeshFileName.length(),".md2");

		_sTextureMeshFileName.insert(_sTextureMeshFileName.length(),_sMainMeshFileName);
		_sTextureMeshFileName.insert(_sTextureMeshFileName.length(),".dds");

		char *_cMainMeshFileName = new char[_sMainMeshFileName.length()];
		char *_cVertexMeshFileName = new char[_sVertexMeshFileName.length()];
		char *_cTextureMeshFileName = new char[_sTextureMeshFileName.length()];
		
		strcpy(_cMainMeshFileName,_sMainMeshFileName.c_str());
		strcpy(_cVertexMeshFileName,_sVertexMeshFileName.c_str());
		strcpy(_cTextureMeshFileName,_sTextureMeshFileName.c_str());
		
		Insert(_sMainMeshFileName,_cVertexMeshFileName,_cTextureMeshFileName);
		this->_meshName.push_back(_sMainMeshFileName);
}


void gMeshDynamicLoadService::Insert(std::string key,char* name_v,char *name_t)
{
	gMeshDynamicContainer *_mesh = new gMeshDynamicContainer();
	gResourceData resource;
	resource.vertexFileName = name_v;
	resource.texturesListFileName = name_t;
	resource.currentEffectName = "mesh_effect";
	resource.effectResources.push_back("mesh_effect");
	resource.effectResources.push_back("shadow_effect");
	_mesh->Load(&resource);
	_meshesContainer.insert(std::pair<std::string,gMeshDynamicContainer*>(key,_mesh));
}

gMeshDynamicContainer* gMeshDynamicLoadService::Find(std::string name)
{
	std::map<std::string,gMeshDynamicContainer*>::iterator meshIterator;
	meshIterator = this->_meshesContainer.find(name);
	if(meshIterator != this->_meshesContainer.end())
		return meshIterator->second;
	else
		return NULL;
}