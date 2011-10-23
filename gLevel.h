#pragma once
#ifndef _G_LEVEL_H_
#define _G_LEVEL_H_

#include <vector>
#include <map>

#include "gMeshStatic.h"
#include "gMeshDynamic.h"
#include "gResource.h"
#include "gMapsService.h"

class gLevel
{
private :
	std::map<std::string,std::vector<gMeshStatic*>> _meshStaticList;
	std::map<std::string,std::vector<gMeshDynamic*>> _meshDynamicList;
	gMeshDynamic* _playerPtr;
	gMapsService* _mapsService;
private :
	std::vector<gMeshStatic*> *_FindMeshStaticResourcePtr(std::string value);
	std::vector<gMeshDynamic*> *_FindMeshDynamicResourcePtr(std::string value);
public :
	gLevel();
	void Load();
	void Update();
	void Render(std::string effectName);
	gMeshStatic *AddStaticMesh(std::string meshName);
	gMeshDynamic *AddDynamicMesh(std::string meshName,bool isPlayer = false);
	__forceinline gMeshDynamic *GetPlayerMesh() { return this->_playerPtr; }
	__forceinline void SetMapsService(gMapsService *_mapsService) { this->_mapsService = _mapsService; }
};
#endif