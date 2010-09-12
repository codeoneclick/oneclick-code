#pragma once
#ifndef _G_MESHSTATICSERVICE_H_
#define _G_MESHSTATICSERVICE_H_

#include <string>
#include <map>

#include "gMeshStaticContainer.h"

class gMeshStaticService
{
private :
	std::map<std::string,gMeshStaticContainer*> _meshesContainer;
	std::vector<std::string> _meshName;

	LPD3DXBUFFER errors;
	HRESULT error_result;
	char* error_name;

private :
	void _AddStaticMesh(std::string fileName);

public  :
	void Load();
	void Insert(std::string name,char* name_v,char* name_t,char* name_i);
	__forceinline std::vector<std::string> Name() { return _meshName; }
	__forceinline std::map<std::string,gMeshStaticContainer*> Container() { return _meshesContainer; }
	__forceinline std::map<std::string,gMeshStaticContainer*>::iterator Begin() { return _meshesContainer.begin(); }
	__forceinline std::map<std::string,gMeshStaticContainer*>::iterator End() { return _meshesContainer.end(); }
    void Delete(char* name,gMeshStaticContainer* mesh);
	gMeshStaticContainer* Find(std::string name);
};

#endif