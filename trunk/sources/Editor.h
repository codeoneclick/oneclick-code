#ifndef _EDITOR_H_
#define _EDITOR_H_
#include "Input.h"
#include "Vector3d.h"
#include "StructExt.h"

namespace edit
{

struct TileType
{
	math::vector::Vector2d vTexCoord[6];
};


/*
2 - LD
3 - RD
4 - LU
5 - RU
6 - L
7 - R
8 - D
9 - U
*/

struct tileLey
{
	char tileType;
	char leyerType;
};

class Editor
{
private :
	static unsigned int _currentTileType;
	static math::vector::Vector3d _mouse3dPosition;
	static type::VertexBuffer *_landscapeVertexBufferPtr;
	static TileType _tileType[16][16];
	static eTyleType _tileMerge[16][16];
    static void _EditTile();
	static void _SetTile(int startPointIndex, type::VertexData * _vPtr, eTyleType tileType);
	static eTyleType _CheckTile(int startPointIndex, type::VertexData * _vPtr, eTyleType tileType);
	static void _Get3DMousePosition(int x, int y);
	static void _Tiling(int x, int y, TILE_TEXTURE_LEVEL brush);
	static char levelMap[256][256];
	static tileLey tile_map[256][256];
	static void SetTileset(int x,int y,char brushLevel);
	static void SetTile(int x,int y,char brushLevel, eTyleType tileType);
public :
	static void Update(DWORD time);
	static void InitTileType();
};
};
#endif