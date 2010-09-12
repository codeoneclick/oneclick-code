#pragma once
#ifndef _G_DEVICE_H_
#define _G_DEVICE_H_

#include <d3dx9.h>
#include "gWindow.h"
#include "gVertex.h"

class gDevice
{
	// VARIBLES
private :
	static LPDIRECT3D9 d3d;
	// FUNCTION
private :
    // VARIBLES
public :
	static LPDIRECT3DDEVICE9 device;
	// FUNCTION
public :
	static bool Load();
	static bool Init();
};

#endif