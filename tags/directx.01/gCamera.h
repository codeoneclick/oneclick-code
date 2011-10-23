#pragma once
#ifndef _G_CAMERA_H_
#define _G_CAMERA_H_

#include <d3dx9.h>
#include "gWindow.h"
#include "gMatrix4x4.h"
#include "gVector3D.h"

#define CAMERA_WHEEL_XZ_SPEED 4.0f
#define CAMERA_WHEEL_Y_SPEED  8.0f

class gCamera
{
private :
	D3DXVECTOR3 vUp;
	//float _cameraWheel;
public :
	gCamera();
	~gCamera();
	void Update();

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 LookAt;
	float lookAtAngle;

	D3DXMATRIX view;
	D3DXMATRIX projection;

	float XZDistance;
	float YDistance;

};
#endif
