#pragma once
#ifndef _G_LIGHT_H_
#define _G_LIGHT_H_

#include <d3dx9.h>

class gLight
{
private :
	ID3DXMesh* Mesh;
	D3DXMATRIX translation_matrix;
	D3DXMATRIX matrix_scale;
	D3DXMATRIX matrix_world;
	ID3DXEffect* Effect;
public :
	D3DXVECTOR3 light_position;
	float light_rotation;
	D3DXVECTOR3 Position;
	float angle;

	D3DXVECTOR4 light_direction;
	//float light_power;
	D3DXVECTOR4 light_ambient_color;
	gLight();
	void Update();
	void Render();
};

#endif