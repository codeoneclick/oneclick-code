#pragma once
#ifndef _G_RESOURCE_H_
#define _G_RESOURCE_H_

#include "gMeshStaticService.h"
#include "gMeshDynamicLoadService.h"

class gResource
{
	// VARIBLES
private :
	// FUNCTION
private :
	static gMeshStaticService *_meshStaticService;
	static bool _meshStaticServiceSingleFlag;

	static gMeshDynamicLoadService *_meshDynamicLoadService;
	static bool _meshDynamicLoadServiceSingleFlag;
    // VARIBLES
public :
	// FUNCTION
public :
	 static gMeshStaticService *MeshStaticService();
	 static gMeshDynamicLoadService *MeshDynamicLoadService();

};
#endif