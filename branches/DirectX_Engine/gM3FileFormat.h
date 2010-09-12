#pragma once
#ifndef _G_M3FILEFORMAT_H_
#define _G_M3FILEFORMAT_H_

#include <d3dx9.h>  
#include "gTypes.h"

struct gM3Header
{
    char id[4];
    uint32 tagsOffset;
    uint32 nTags;
    uint32 unknown_01;
    uint32 unknown_02;
};

struct gM3Tag 
{
	char tagName[4];
	uint32 blockOffset;
	uint32 blockSize;
	uint32 version;
};

struct gM3VertexBlock
{
	D3DXVECTOR3 position;
	char boneWeight[4];
    char boneIndex[4];
    char normal[4];
    uint16 uv[2];
    uint32 d1;
    uint32 d2;
};
#endif