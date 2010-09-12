#pragma once
#ifndef _G_TEXTURESERVICE_H_
#define _G_TEXTURESERVICE_H_

#include <d3dx9.h>
//#include <vector>
#include <string>
#include <map>

#include "gDevice.h"

//using namespace std;

class gTexturesService
{
private :
	std::map<std::string,IDirect3DTexture9*> _texturesContainer;

	LPD3DXBUFFER errors;
	HRESULT error_result;
	char* error_name;

public  :
	void Load();
	void Insert(std::string name,IDirect3DTexture9* texture);
	void Insert(std::string name,std::string key);
	__forceinline std::map<std::string,IDirect3DTexture9*> Container() { return _texturesContainer; }
    void Delete(std::string name,IDirect3DTexture9* texture);
	IDirect3DTexture9* Find(std::string name);
};
#endif