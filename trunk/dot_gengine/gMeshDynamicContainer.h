#pragma once
#ifndef _G_MESHDYNAMICCONTAINER_H_
#define _G_MESHDYNAMICCONTAINER_H_

#include <d3dx9.h>
#include <string>
#include <fstream>

#include "gCore.h"
#include "gTypes.h"
#include "gVertex.h"
#include "gResourceData.h"

const int MAX_TRIANGLES = 4096;
const int MAX_VERTS		= 2048;
const int MAX_FRAMES	= 512;
const int MAX_MD2SKINS	= 32;
const int MAX_SKINNAME	= 64;

class gMeshDynamicContainer
{
private :
	std::map<std::string,ID3DXEffect*> _effectsList;
	std::vector<IDirect3DTexture9*> _texturesColorList;
	gMd2IndexList* _indexData;
	gMd2FrameVertexList* _frameVertexList;
	gMd2FrameVertexData *_framesVertexData;
	
	long nFrames;
	long nVerteces;
	long nTriangles;

	//////////////////////////////////////////////////////////////////////////////////////

	md2::header header;

	void Load(std::istream& md2_stream);
	void LoadFromFile(char* file_name);
	
	IDirect3DVertexBuffer9** GetModelVB(int frame);
	IDirect3DVertexBuffer9* GetTextureVB(void);
	IDirect3DIndexBuffer9* GetModelIB(void);

	int GetVertCount(void);
	int GetTriangleCount(void);
	int GetFrameCount(void);

protected:
	void GetHeader(std::istream& md2_stream);	
	void GetFrameData(std::istream& md2_stream);
	void GetIndexData(std::istream& md2_stream);
	void GetTextureData(std::istream& md2_stream);
	
	IDirect3DIndexBuffer9*  model_IB;
	IDirect3DVertexBuffer9* model_VB[512];
	IDirect3DVertexBuffer9* texture_VB;

	int used_VBs;
public:
	gMeshDynamicContainer();
	~gMeshDynamicContainer();
	void Load(const gResourceData *resource);
	gMeshDynamicData GetMeshData();
};
#endif
