#pragma once
#ifndef _G_MESHCONTAINER_H_
#define _G_MESHCONTAINER_H_

#include <d3dx9.h>
#include <string>

#include "gCore.h"
#include "gTypes.h"
#include "gVertex.h"
#include "gResourceData.h"

class gMeshContainer
{
protected :
	HRESULT directXResult;
	LPD3DXBUFFER errorString;

	gmi *indexInfo;

	unsigned short nVertices;
	unsigned short nTextures;
	unsigned short nIndices;

	std::string *textureColorFileName;
	std::string *textureNormalFileName;

	IDirect3DVertexBuffer9* vb;
	IDirect3DIndexBuffer9*  ib;
	std::vector<IDirect3DTexture9*> texturesColorList;
	std::vector<IDirect3DTexture9*> texturesNormalList;
	std::map<std::string,ID3DXEffect*> effectsList;

	unsigned short* _simpleIndexBuffer;
	unsigned short* _indexBuffer;
	gSimpleVertexFormat* _simpleVertexBuffer;
	gVertex* _vertexBuffer;

	gTBNInfo* _TBNInfo;

protected :
	void _FillTexturesList();
	void _CalculateTBN(unsigned int nVerteces,unsigned int nIndeces);

	virtual void _WriteToDeviceVertexBuffer() = 0;
	virtual void _WriteToDeviceIndexBuffer() = 0;

public :
	virtual void Load(const gResourceData *resource) = 0;
	gMeshContainer();
};

#endif