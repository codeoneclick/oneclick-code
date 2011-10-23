#pragma once
#ifndef _G_VERTEX_H_
#define _G_VERTEX_H_

#include <d3dx9.h>

struct gPickVertex{
	D3DXVECTOR3 position;
	gPickVertex(){}
};

struct gVertex{
    D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texture;
    D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;
	D3DXVECTOR4 layer_0;
	D3DXVECTOR4 layer_1;
	//float instance;
	gVertex(){}
};

struct gMeshVertex{
    D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texture;
    D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;
	D3DXVECTOR4 layer_0;
	D3DXVECTOR4 layer_1;
	gMeshVertex(){}
};

/*struct struct_map_mask {
		BYTE r;
		BYTE g;
		BYTE b;
};*/

enum gPlantsEnum {PLANT_NONE = 0, PLANT_GRASS, PLANT_FLOWER, PLANT_REED};
enum gRockEnum   {ROCK_NONE = 0, ROCK_SMALL, ROCK_MEDDIUM, ROCK_BIG};

struct gMapDecoration
{
	gPlantsEnum plantsFlag;
	gRockEnum rockFlag;
	float road;
};

struct gMapTileMask
{
	float grass;
	float rock;
	float sand;
	float snow;
};

struct gmv
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texture;
};



#endif