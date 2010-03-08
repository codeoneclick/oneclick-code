#pragma once
#ifndef _M3_FILEFORMAT_H_
#define _M3_FILEFORMAT_H_

#include "m3_TypeDef.h"

struct m3_CheckVersion 
{
	uint32 values[17];
	uint32 version;
};

struct m3_Header
{
    char id[4];
    uint32 tagsOffset;
    uint32 nTags;
    uint32 unknown_01;
    uint32 unknown_02;
};

struct m3_Tag 
{
	char tagName[4];
	uint32 blockOffset;
	uint32 blockSize;
	uint32 version;
};

struct m3_VertexBlockExt
{
	float position[3];
	char boneWeight[4];
    char boneIndex[4];
    char normal[4];
    uint16 uv[2];
	uint8 unknValues[8];
};

struct m3_VertexBlock
{
    float position[3];
    char boneWeight[4];
    char boneIndex[4];
    char normal[4];  
    uint16 uv[2];
    uint8 unknValues[10];
};

struct m3_CalcNomralBlock
{
	float normal[3];
};

#endif