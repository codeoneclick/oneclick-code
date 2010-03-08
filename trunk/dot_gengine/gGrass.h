#pragma once
#ifndef _G_GRASS_H_
#define _G_GRASS_H_

#include <d3dx9.h>
#include <vector>

#include "gCamera.h"
#include "gLight.h"
#include "gVertex.h"
#include "gCore.h"
#include "gDevice.h"

class gGrass
{
private :
    IDirect3DTexture9* grass_texture_color;

	ID3DXMesh* mesh;

	std::vector<float> position_x;
	std::vector<float> position_z;

	gCamera *camera;
	gLight *light;
	float **heightmap;

	ID3DXEffect* Effect;

	bool is_create;

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scale_matrix;
	DWORD grass_num_vertices, grass_num_primitives;

	int map_index_i;
	int map_index_j;

	int Random(int min, int max);

public :
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Color;
	D3DXMATRIX matrix;
public :
	gGrass();
	~gGrass() ;
	void Create(float **map_heightmap,gMapDecoration **map_tile_mask,int map_index_i,int map_index_j);
	void Render();
	void Update();
	void Textures();
};

#endif