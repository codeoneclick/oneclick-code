#include "m3_Camera.h"

m3_Camera::m3_Camera()
{
	vPosition = Vector3d(0.0f,0.0f,0.0f);
	vRotation = Vector3d(0.0f,0.0f,0.0f);
	vLookAt   = Vector3d(0.0f,0.0f,0.0f);
	_fRotationAngleXZ = 0.0f;
	_fRotationAngleY  = 0.0f;
	_fCameraMoveSpeed = 0.5f;
	_fCameraRotationSpeed = 1.0f;
	mProjection = MatrixProjection(45.0f, (float)320 / (float)240, 0.1f,1000.0f);
}

void m3_Camera::MoveForward()
{
    vLookAt.x += (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void m3_Camera::MoveBackward()
{
    vLookAt.x  -= (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void m3_Camera::MoveRight()
{
    vLookAt.x += (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void m3_Camera::MoveLeft()
{
    vLookAt.x  -= (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void m3_Camera::RotateLeft()
{
     _fRotationAngleXZ -= _fCameraRotationSpeed;
}

void m3_Camera::RotateRight()
{
     _fRotationAngleXZ += _fCameraRotationSpeed;
}


void m3_Camera::Update()
{
	if( m3_Input::mLeftDown )
	{
		int diffx = m3_Input::mCurrentPosition.x - m3_Input::mLastPosition.x; 
		int diffy = m3_Input::mCurrentPosition.y - m3_Input::mLastPosition.y; 

		m3_Input::mLastPosition.x = m3_Input::mCurrentPosition.x;
		m3_Input::mLastPosition.y = m3_Input::mCurrentPosition.y;

		_fRotationAngleXZ += (float) diffx/1.0f;
		//_fRotationAngleY += (float) diffy/1.0f;
	}

	if(m3_Input::ePressRotateLeft)
		RotateLeft();

	if( m3_Input::ePressRotateRight)
		RotateRight();

	if(m3_Input::ePressForward)
		MoveForward();

	if(m3_Input::ePressBackward)
		MoveBackward();

	if(m3_Input::ePressLeft)
		RotateLeft();//MoveLeft();

	if(m3_Input::ePressRight)
		RotateRight();//MoveRight();

	vRotation.y = _fRotationAngleXZ * 0.0174532925f;
	vRotation.x = _fRotationAngleY * 0.0174532925f;
        
    vPosition.x = vLookAt.x + cos(-(vRotation.y) + 1.57f)*-32.0f;
    vPosition.z = vLookAt.z + sin(-(vRotation.y) + 1.57f)*-32.0f;
	vPosition.y = vLookAt.y + 24.0f;
	//vPosition.y = vLookAt.y + sin(-(vRotation.x) + 1.57f)*-25.0f;

	mView = MatrixView(vPosition,vLookAt,Vector3d(0.0f,1.0f,0.0f));
}