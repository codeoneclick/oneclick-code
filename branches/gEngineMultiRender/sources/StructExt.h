#ifndef _STRUCTEXT_H_
#define _STRUCTEXT_H_
#include <windows.h>
#include <string>
#include <map>
#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "Vector3d.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

//enum eTyleType { T_C_01 = 0, T_C_02, T_LD, T_RD, T_LU, T_RU, T_L, T_R, T_D, T_U, T_LD_EXT, T_RD_EXT, T_RU_EXT, T_LU_EXT };
enum eTyleType { T_C_02 = 0, T_LD, T_RD, T_LU, T_RU, T_L, T_D, T_DIAG_01, T_DIAG_02, T_U, T_R, T_RD_EXT, T_LD_EXT, T_RU_EXT, T_LU_EXT, T_C_01 };

#define TILE_CENTER_02		0
#define TILE_LEFT_DOWN		1
#define TILE_RIGHT_DOWN		2
#define TILE_LEFT_UP		3
#define TILE_RIGHT_UP		4
#define TILE_LEFT			5
#define TILE_DOWN           6
#define TILE_DIAG_LEFT		7
#define TILE_DIAG_RIGHT		8
#define TILE_DIAG_LEFT_EXT  9 
#define TILE_DIAG_RIGHT_EXT 10   
#define TILE_UP             11
#define TILE_RIGHT          12
#define TILE_RIGHT_DOWN_EXT 13
#define TILE_LEFT_DOWN_EXT  14
#define TILE_RIGHT_UP_EXT   15
#define TILE_LEFT_UP_EXT    16
#define TILE_CENTER_01      17



enum TILE_TEXTURE_LEVEL { LEVEL_01 = 0, LEVEL_02, LEVEL_03, LEVEL_MAX };

struct v3
{
	float x,y,z;
};

struct v2
{
	float x,y;
};

struct mVertexData
{
	v3 vPosition;
	v2 vTexCoord;
};

namespace type
{

struct CGShader
{
	CGcontext   context;
	CGprofile   vertexProfile;
	CGprofile   pixelProfile;
	CGprogram   vertexProgram;
	CGprogram   pixelProgram;
};

struct STexture
{
	enum EXTENSION { _DDS = 0, _PNG = 1 };
	unsigned int addr_ptr;
	std::string  name;
	EXTENSION extension;
};

struct SMesh
{
	enum EXTENSION { _3DS = 0, _M2, _M3 };
	EXTENSION extension;

	CVertexBuffer *vertexBuffer;
	CIndexBuffer  *indexBuffer;
};

struct CGShaderParameters
{
	CGparameter texture[8];
	CGparameter mWorldViewProjection;
	CGparameter mWorld;
	CGparameter mView;
	CGparameter mProjection;
	CGparameter vCameraPosition;
	CGparameter vLightDirection;
	CGparameter iColor;

	CGShaderParameters()
	{
		for(unsigned int i = 0; i < 8; ++i)
			texture[i] = NULL;
		mWorldViewProjection = NULL;
		mWorld = NULL;
		mView = NULL;
		mProjection = NULL;
		vCameraPosition = NULL;
		vLightDirection = NULL;	
		iColor = NULL;
	}
};

struct VertexData
{
	math::Vector3d vPosition;
	math::Vector2d vTexCoord;
	math::Vector3d vNormal;
	math::Vector3d vTangent;
	math::Vector3d vBinormal;
	eTyleType vExtValue;
};

struct ChunkData
{
	unsigned int* indexBufferAddr;
	unsigned int nIndeces;
};

struct VertexBuffer
{
	unsigned int nVerteces;
	unsigned int vertexBufferAddr;
};

struct IndexBuffer
{
	unsigned int nIndeces;
	unsigned int indexBufferAddr;
};

struct ChunkBuffer
{
	unsigned int nChunks;
	std::map<std::string,ChunkData*> chunkData;
};

struct VertexDeclaration
{
	bool bPosition;
	bool bTexCoord;
	bool bNormal;
	bool bTangent;
	bool bBinormal;
	bool bExtValue;

	VertexDeclaration()
	{
		bPosition = false;
		bTexCoord = false;
		bNormal = false;
		bTangent = false;
		bBinormal = false;
		bExtValue = false;
	}
};

struct VertexBufferData
{
	VertexData  *vertexDataPtr;
	unsigned int nVerteces;
	unsigned int vertexBufferId;

	unsigned int nIndeces;
	unsigned int *indecesPtr;
	unsigned int indexBufferId;

	ChunkBuffer  *chunkBuffer;

	bool bPosition;
	bool bTexCoord;
	bool bNormal;
	bool bTangent;
	bool bBinormal;
	bool bExtValue;

	VertexBufferData()
	{
		vertexDataPtr = NULL;
		nVerteces = 0;
		vertexBufferId = 0;
		indexBufferId = 0;
		nIndeces = 0;
		indecesPtr = NULL;

		bPosition = false;
		bTexCoord = false;
		bNormal = false;
		bTangent = false;
		bBinormal = false;
		bExtValue = false;
	}
};


};

#endif