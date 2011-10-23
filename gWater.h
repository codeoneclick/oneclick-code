#pragma once
#ifndef _G_WATER_H_
#define _G_WATER_H_

#include <d3dx9.h>

#include "gCamera.h"
#include "gLight.h"

class gWater
{
private :
	ID3DXMesh* Mesh;

	HRESULT D3D_Result;

	ID3DXEffect* Effect;

	gCamera *camera;
	gLight *light;

	D3DXMATRIX world_matrix;
	D3DXMATRIX world_view_projection_matrix;
	D3DXMATRIX view_invert_matrix;
	
	DWORD water_num_vertices, water_num_primitives;
public :
	gWater();
	~gWater();
	void Create(int map_index_i,int map_index_j);
	void Render();
	void Update();
	void Textures();

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
};

#endif