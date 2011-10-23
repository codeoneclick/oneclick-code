#include "gCamera.h"

gCamera::gCamera()
{
	this->Position  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->LookAt    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->lookAtAngle = 0.0f;

	this->XZDistance = 128.0f;
	this->YDistance = 32.0f;
	//this->_cameraWheel = 128.0f;
	this->vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	//D3DXMatrixPerspectiveFovLH(&projection, D3DXToRadian(45.0f), (float)(gWindow::wndWidth/gWindow::wndHeight), 0.5f, 10000.0f);
	gMatrix4x4 mP = MatrixProjection(D3DXToRadian(45.0f), (float)(gWindow::wndWidth/gWindow::wndHeight), 0.5f, 10000.0f);
	for(int i = 0; i < 4;++i)
		for(int j = 0; j < 4; ++j)
			projection.m[i][j] = mP.m[i*4 + j];
}

gCamera::~gCamera()
{

}

void gCamera::Update()
{
	if((::GetAsyncKeyState('Z') & 0x8000f ) && (this->XZDistance > CAMERA_WHEEL_XZ_SPEED))
	{
		this->XZDistance -= CAMERA_WHEEL_XZ_SPEED;
		this->YDistance  += CAMERA_WHEEL_Y_SPEED;
	}

	if((::GetAsyncKeyState('X') & 0x8000f ) && (this->YDistance > this->LookAt.y))
	{
		this->XZDistance += CAMERA_WHEEL_XZ_SPEED;
		this->YDistance  -= CAMERA_WHEEL_Y_SPEED;
	}
	gMatrix4x4 mV = MatrixView(gVector3D(this->Position.x,this->Position.y,this->Position.z),gVector3D(this->LookAt.x,this->LookAt.y,this->LookAt.z),gVector3D(0.0f,1.0f,0.0f));
	for(int i = 0; i < 4;++i)
		for(int j = 0; j < 4; ++j)
		this->view.m[i][j] = mV.m[i*4 + j];
	
}
