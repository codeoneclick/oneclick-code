#include "gSprite.h"

gSprite::gSprite(LPDIRECT3DDEVICE9 *device){
	this->current_frame = 0;
	this->frame_count = 29; // FIX
	this->last_timer = 0;
	this->texture = NULL;
	texture_rectangle.top = 0;
	texture_rectangle.bottom = 1;
	texture_rectangle.left = 0;
	texture_rectangle.right = 1;
	D3DXCreateSprite(*device, &Sprite);

	this->device = device;
}

gSprite::~gSprite(){
	if(this->texture != NULL){
		this->texture->Release();
		this->texture = NULL;
	}
}

void gSprite::SetTexture(std::string filename){
	D3DXCreateTextureFromFile(*device, filename.c_str(), &this->texture);
}

void gSprite::Update(){
   int current_timer = GetTickCount();
   if(current_timer - last_timer > this->timer){
	   ++this->current_frame;
	   this->last_timer = current_timer;
	   if(this->current_frame > frame_count)
		   this->current_frame = 0;
	}
   
   int i = this->current_frame / 6; 
   int j = this->current_frame % 6; 
   texture_rectangle.top = j*64;
   texture_rectangle.left = i*64;
   texture_rectangle.bottom = (j+1)*64;
   texture_rectangle.right = (i+1)*64;
}

void gSprite::Render(){
  // (*device)->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
   this->Sprite->Begin(D3DXSPRITE_OBJECTSPACE);
   D3DXMatrixIdentity(&this->world_matrix);
   this->Sprite->SetTransform(&this->world_matrix);
   this->Sprite->Draw(this->texture, &this->texture_rectangle, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, D3DCOLOR_XRGB(255, 255, 255));
   this->Sprite->End();
  // (*device)->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}