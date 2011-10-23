#pragma once
#ifndef _G_MAPSSERVICE_H_
#define _G_MAPSSERVICE_H_

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "gVertex.h"
#include "gMap.h"

using namespace std;

#define FILE_MAP_SIZE 256
#define MAP_SIZE 64
#define NUMBER_OF_MAPS 16

class gMapsService
{
	// VARIBLES
private :
	float **map_heightmap;
	gMapTileMask** map_tile_mask;
	gMapDecoration** map_decoration_mask;
	std::vector<gMap*> map;
	// FUNCTION
private :
	
    // VARIBLES
public :

	// FUNCTION
public :

	void Load();
	void Save();
	float Height(float position_x,float position_z);

	D3DXVECTOR2 Normal(float position_x,float position_z);

	__forceinline std::vector<gMap*> Maps() { return this->map; }
	
	__forceinline float** GetMapHeightMap() { return this->map_heightmap; }
	__forceinline gMapTileMask** GetMapTileMask() { return this->map_tile_mask; }
	__forceinline gMapDecoration** GetMapDecorationMask() { return this->map_decoration_mask; }

	void AutoGenerateMapTiles();
};

#endif

