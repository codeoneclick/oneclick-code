#ifndef _MAPSERVICE_H_
#define _MAPSERVICE_H_

#include <string>
#include <map>
#include "StructDef.h"
#include "VB.h"

#define MAP_SIZE  256

#define CHUNK_SIZE  64

struct VertexBufferPtrExt
{
	VertexData *vertexDataPtr;
	unsigned int nVerteces;
	unsigned int vertexBufferId;
};

struct MapData
{
	float **_heightmapMainData;
	float **_heightmapExtData;
};

struct GrassParam
{
	Vector3d vPosition;
	float fWidth;
	float fHeight;
	int   iType;
};

class MapService
{
	public :
		VertexBufferEnv *_heightmapVB;
		VertexBufferEnv *_waterVB;
		VertexBufferEnv *_grassVB;

		IndexBufferEnv  *_tilesetIB;

		IndexBufferEnv  ***_heightmapIB;
		IndexBufferEnv  ***_waterIB;
		IndexBufferEnv  ***_grassIB;

		float **_heightmap;

		std::map<std::string,VertexBufferPtr*> _tilesetContainer;
	private :
		void _ReadMapFile(char *filename);

		void _WriteHeightmapVBInVideoMemory();
		void _WriteWaterVBInVideoMemory();
		void _WriteGrassVBInVideoMemory();

		void _WriteHeightmapIBInVideoMemory(unsigned int indexX, unsigned int indexY);
		void _WriteWaterIBInVideoMemory(unsigned int indexX, unsigned int indexY);
		void _WriteGrassIBInVideoMemory(unsigned int indexX, unsigned int indexY);
		void _WriteTilesetIBInVideoMemory();

		void _CalculateTBN(unsigned int nIndeces,VertexData *valueVB, unsigned int *valueIB);

	public :
		MapService(char *filename);
		std::vector<GrassParam> grassPositionList;
};

#endif