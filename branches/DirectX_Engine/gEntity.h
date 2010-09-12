#pragma once
#ifndef _G_ENTITY_H_
#define _G_ENTITY_H_

#include <d3dx9.h>
#include "gCore.h"

class gEntity
{
protected :
	HRESULT directXResult;
	LPD3DXBUFFER errorString;

	D3DXMATRIX  mWorld;
	D3DXMATRIX  mTranslation;
	D3DXMATRIX  mRotation;
	D3DXMATRIX  mRotationX;
	D3DXMATRIX	mRotationY;
	D3DXMATRIX	mRotationZ;
	D3DXMATRIX  mScale;

	D3DXMATRIX  *mProjection;
	D3DXMATRIX  *mView;

	D3DXMATRIX  mWorldView;
	D3DXMATRIX  mWorldViewInverse;

public:
	gEntity();

	virtual void Update() = 0;

	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vRotation;
	D3DXVECTOR3 vScale;
};
#endif