#pragma once
class gFog
{
private :

	float fog_start;
	float fog_end;
	D3DXVECTOR3 color;

public :
	gFog();
	~gFog();
	inline void SetColor(D3DXVECTOR3 color) { this->color = color; Device->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(this->color.x,this->color.y,this->color.z,0.0f));}
	inline D3DXVECTOR3 GetColor() { return this->color; }
	inline void SetFogStart(float fog_start) { this->fog_start = fog_start; Device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&this->fog_start)); }
	inline float GetFogStart() { return this->fog_start; }
	inline void SetFogEnd(float fog_end) { this->fog_end = fog_end;   Device->SetRenderState(D3DRS_FOGEND,   *(DWORD *)(&fog_end));}
	inline float GetFogEnd() { return this->fog_end; }
	inline void Enable() {   Device->SetRenderState(D3DRS_FOGENABLE, FALSE);  }
	inline void Disable() {  Device->SetRenderState(D3DRS_FOGENABLE, FALSE); }
};



gFog::gFog(){
	this->color = D3DXVECTOR3(1.0f,1.0f,0.0f);
	Device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
}

gFog::~gFog(){
}

