#include "gEntity.h"

gEntity::gEntity()
{
	this->vPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->vRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->vScale    = D3DXVECTOR3(1.0f,1.0f,1.0f);

	D3DXMatrixIdentity(&this->mWorld);

	this->mProjection = &gCore::Camera()->projection;
	this->mView		  = &gCore::Camera()->view;

	this->directXResult = NULL;
	this->errorString = NULL;
}
