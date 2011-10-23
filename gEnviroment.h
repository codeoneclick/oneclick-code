#pragma once
#ifndef _G_ENVIROMENT_H_
#define _G_ENVIROMENT_H_

#include <windows.h>

#include "gMapsService.h"
#include "gMeshStaticService.h"
#include "gSkyDome.h"
#include "gLevel.h"

DWORD WINAPI mapsLoadThread(LPVOID data);
#define SHADOWMAP_SIZE 512
#define REFLECTION_SIZE 512
static class gEnviroment
{
	// VARIBLES
private :

	static HANDLE _thread;

	static gMapsService* _mapsService;
	static bool _mapsServiceSingleFlag;
	
	static gSkyDome* _sky;
	static bool  _skySingleFlag;

	static gLevel* _levelContainer;
	static bool    _levelContainerSingleFlag;

	//static gMeshService* _meshService;
	//static bool _meshServiceSingleFlag;


	static LPDIRECT3DTEXTURE9 _models_reflection_texture;
	static bool  _models_reflection_textureSingleFlag;

	static LPDIRECT3DSURFACE9 _models_reflection_surface;
	static bool  _models_reflection_surfaceSingleFlag;

	static LPDIRECT3DTEXTURE9 _shadowMapTexture;
	static bool  _shadowMapTextureSingleFlag;

	static LPDIRECT3DSURFACE9 _shadowDepthStencilSurface;
	static bool  _shadowDepthStencilSurfaceSingleFlag;

	// FUNCTION
private :
	
	static LPDIRECT3DTEXTURE9 _ModelsReflectionTexture();
	static LPDIRECT3DSURFACE9 _ModelsReflectionSurface();

	static LPDIRECT3DTEXTURE9 _ShadowMapTexture();
	static LPDIRECT3DSURFACE9 _ShadowMapSurface();

    // VARIBLES
public :
	// FUNCTION
public :
	 static gMapsService* MapsService();

	// static gMeshService* MeshService();

	 static void _mapsLoadThread();
	
	 static gSkyDome* Sky();

	 static gLevel* LevelContainer();

	 static void Update();

	 static void Reflection();
	 static void ShadowMap();

};

#endif