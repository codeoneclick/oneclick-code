#pragma once
#ifndef _G_GROUND_H_
#define _G_GROUND_H_

#include "gTypes.h"
#include "gModel3D.h"

class gGround : public gModel3D
{
private :
	bool			 _water_enable;

	RenderLODFlags flag;

	GroundFlags    _mapChankLoadFlag;

	unsigned int _mapChankIndexI;
	unsigned int _mapChankIndexJ;

	float** _mapHeightsReference;
	gMapTileMask** _mapTextureMaskReference;
	gMapDecoration** _mapDecorationMaskReference;

	gMeshOptions*  _CalculateLODMeshOptions();

	void _CreateSimpleVertexBuffer();
	void _CreateIndexBuffer();
	
	virtual void _WriteToDeviceVertexBuffer();
	virtual void _WriteToDeviceIndexBuffer();

public :
	gGround();
	~gGround() ;

	virtual void Load(const gResourceData *resource);
	virtual void Update();
	virtual void Render();
	
	void SetHighChankMap();
	void SetMiddleChankMap();
	void SetLowChankMap();
	void UnloadChankMap();

	void SetMapChankIndex(unsigned int indexI,unsigned int indexJ);
	void SetMapHeights(float** mapHeightsReference);
	void SetTextureMask(gMapTileMask** mapTextureMaskReference);
	void SetDecorationMask(gMapDecoration** mapDecorationMaskReference);

	void EditGround();

	__forceinline void SetRenderFlag(RenderLODFlags flag) { this->flag = flag; }
	__forceinline bool WaterEnable() { return this->_water_enable; }
};

#endif