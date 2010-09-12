#pragma once
#ifndef _G_MESHDYNAMICLOADSERVICE_H_
#define _G_MESHDYNAMICLOADSERVICE_H_

#include <string>
#include <map>

#include "gMeshDynamicContainer.h"

class gMeshDynamicLoadService
{
private :
	std::map<std::string,gMeshDynamicContainer*> _meshesContainer;
	std::vector<std::string> _meshName;

	LPD3DXBUFFER errors;
	HRESULT error_result;
	char* error_name;

private :
	void _AddStaticMesh(std::string fileName);

public  :
	void Load();
	void Insert(std::string name,char* name_v,char *name_t);
	__forceinline std::vector<std::string> Name() { return _meshName; }
	__forceinline std::map<std::string,gMeshDynamicContainer*> Container() { return _meshesContainer; }
	__forceinline std::map<std::string,gMeshDynamicContainer*>::iterator Begin() { return _meshesContainer.begin(); }
	__forceinline std::map<std::string,gMeshDynamicContainer*>::iterator End() { return _meshesContainer.end(); }
    void Delete(char* name,gMeshDynamicContainer* mesh);
	gMeshDynamicContainer* Find(std::string name);
};

#endif