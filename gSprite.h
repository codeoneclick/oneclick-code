#pragma once
#include <d3dx9.h>
#include <math.h>	
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <winbase.h>

using namespace std;

class gSprite
{
private :
    IDirect3DTexture9* texture;
	ID3DXSprite* Sprite;
	int timer;
	int last_timer;
	int current_frame;
	int frame_count;
	RECT texture_rectangle;
	D3DXMATRIX world_matrix;

	LPDIRECT3DDEVICE9 *device;
public :
	gSprite(LPDIRECT3DDEVICE9 *device);
	~gSprite() ;
	void SetTexture(std::string filename);
	void Update();
	void Render();
	inline void SetTimer(int timer) { this->timer = timer; }
	inline void SetFrameCount(int frame_count) { this->frame_count = frame_count; }

	D3DXVECTOR3 Position;
};
