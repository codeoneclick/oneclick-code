#pragma once
#ifndef _G_SHADERSERVICE_H_
#define _G_SHADERSERVICE_H_

#include <d3dx9.h>
#include <string>
#include <map>


#include "gDevice.h"

class gShadersService
{
private :
	std::map<std::string,ID3DXEffect*> _shadersContainer;

	LPD3DXBUFFER errors;
	HRESULT error_result;
	char* error_name;

public  :
	void Load();
	void Insert(std::string name,ID3DXEffect* shader);
	void Insert(std::string name,std::string key);
	__forceinline std::map<std::string,ID3DXEffect*> Container() { return _shadersContainer; }
    void Delete(std::string name,ID3DXEffect* shader);
	ID3DXEffect* Find(std::string name);
};
#endif
