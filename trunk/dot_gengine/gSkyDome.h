#pragma once
#ifndef _G_SKYDOME_H_
#define _G_SKYDOME_H_

#include "gModel3D.h"

class gSkyDome
{
private :
    IDirect3DTexture9* clouds_textures_color;
	IDirect3DTexture9* clouds_textures_normal;
	IDirect3DTexture9* sky_textures_normal;
	IDirect3DTexture9* new_cloud_textures_normal;


	D3DXCOLOR fog_color;
	ID3DXMesh* Mesh;
	ID3DXEffect* Effect;

	ID3DXMesh* _Mesh;

	//ID3DXMesh* Mesh_H;
	ID3DXMesh* mesh;
	//ID3DXEffect* Effect_H;

	float day_time;
	float cloud_animation;

	float sky_intensive;

	float time_length;
	int timer;

	D3DXVECTOR4 light_direction;

	float timer_speed;

	float night_timer;
	float rise_timer;
	float day_timer;
	float evning_timer;

	float clouds_timer;

	bool time_am;

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scale_matrix;
	D3DXMATRIX world_matrix;

public :
	int Id;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Color;
	D3DXMATRIX matrix;

	float fTheta;

	float fog_amount;

public :
	gSkyDome();
	~gSkyDome() ;
	void Create(int id,ID3DXEffect* Effect,ID3DXEffect* Effect_H);
	void Render();
	void Update();
	D3DXVECTOR4 GetSunColor(float fTheta, int nTurbidity);
};

#endif

