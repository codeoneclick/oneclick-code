#pragma once
#ifndef _G_CORE_H_
#define _G_CORE_H_

#include <d3dx9.h>
#include "gCamera.h"
#include "gTexturesService.h"
#include "gShadersService.h"
#include "gLight.h"

class gCore
{
	// VARIBLES
private :
	static gTexturesService* _texturesService;
	static bool _texturesServiceSingleFlag;

	static gShadersService* _shadersService;
	static bool _shadersServiceSingleFlag;

	static gCamera* _camera;
	static bool _cameraSingleFlag;

	static gLight* _global_light;
	static bool  _global_lightSingleFlag;

	static LPDIRECT3DSURFACE9 oldRenderTarget;
	static LPDIRECT3DSURFACE9 oldDepthStencilSurface;
	static D3DVIEWPORT9 oldViewport;

	static LPDIRECT3DSURFACE9 currentRenderTarget;
	static D3DVIEWPORT9 currentViewport;

	static LPDIRECT3DVERTEXDECLARATION9 _ptrShaderDeclaration;
	static bool  _ptrShaderDeclarationSingleFlag;

	static LPDIRECT3DVERTEXDECLARATION9 _ptrMd2ShaderDeclaration;
	static bool  _ptrMd2ShaderDeclarationSingleFlag;

	// FUNCTION
private :
    // VARIBLES
public :
	// FUNCTION
public :
	 static gTexturesService* TexturesService();

	 static gShadersService*  ShadersService();

	 static gCamera* Camera();

	 static gLight*  Light();

	 static void Update();

	 static void EnableRenderToTexture(IDirect3DTexture9* pOutTexture,LPDIRECT3DSURFACE9 shadowDepthStancilSurface,unsigned int width,unsigned int height,D3DFORMAT textureFormat,DWORD clearColor);
	 static void DisableRenderToTexture();

	 static float editRadius;

	 static D3DVERTEXELEMENT9 shaderVertexElemets[];
	 static LPDIRECT3DVERTEXDECLARATION9 ShaderDeclaration();

	 static D3DVERTEXELEMENT9 md2ShaderVertexElemets[];
	 static LPDIRECT3DVERTEXDECLARATION9 Md2ShaderDeclaration();
};

#endif