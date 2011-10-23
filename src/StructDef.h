#ifndef _STRUCTDEF_H_
#define _STRUCTDEF_H_

#include <vector>
#include <string>
#include <map>
#include "Vector3d.h"

#define WATER_LEVEL 25.0f
#define HEIGHTMAP_LEVEL 0.2f
#define GRASS_01_LEVEL 27.5f
#define GRASS_02_LEVEL 32.5f

struct Vector2d
{
	float x,y;
};

struct Vector4d
{
	float x,y,z,w;
};

struct VertexData
{
	Vector3d vPosition;
	Vector2d vTexCoord;
	Vector3d vNormal;
	Vector3d vTangent;
	Vector3d vBinormal;
	Vector4d vExtValue;
};

struct MeshChunkBlock
{
	unsigned int* indecesPtr;
	unsigned int nIndeces;
};

struct VertexBufferEnv
{
	VertexData *vertexDataPtr;
	unsigned int nVerteces;
	unsigned int vertexBufferId;
};

struct IndexBufferEnv
{
	unsigned int* indecesPtr;
	unsigned int nIndeces;
	unsigned int indexBufferId;
};

struct VertexBufferPtr
{
	VertexData *vertexDataPtr;
	unsigned int nVerteces;
	unsigned int vertexBufferId;

	unsigned int nIndeces;
	unsigned int *indecesPtr;
	unsigned int indexBufferId;

	unsigned int nChunks;
	std::map<std::string,MeshChunkBlock*> chunkIndecesPtr;

	bool bPosition;
	bool bTexCoord;
	bool bNormal;
	bool bTangent;
	bool bBinormal;
	bool bExtValue;

	VertexBufferPtr()
	{
		vertexDataPtr = NULL;
		nVerteces = 0;
		vertexBufferId = 0;
		indexBufferId = 0;
		nIndeces = 0;
		indecesPtr = NULL;
		nChunks = NULL;

		bPosition = false;
		bTexCoord = false;
		bNormal = false;
		bTangent = false;
		bBinormal = false;
		bExtValue = false;
	}
};

#endif
