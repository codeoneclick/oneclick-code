#include "Camera.h"
#include "Window.h"
#include "Input.h"
using namespace Enviroment;

Camera::Camera()
{
	vPosition = math::vector::Vector3d(0.0f,0.0f,0.0f);
	vRotation = math::vector::Vector3d(0.0f,0.0f,0.0f);
	vLookAt   = math::vector::Vector3d(0.0f,0.0f,0.0f);
	vUp       = math::vector::Vector3d(0.0f,1.0f,0.0f);
	_fRotationAngleXZ = 0.0f;
	_fRotationAngleY  = 0.0f;
	_fCameraMoveSpeed = 0.5f;
	_fCameraRotationSpeed = 1.0f;
	_fNearPlane = 0.1f;
	_fFarPlane  = 1000.0f;
	mProjection = math::matrix::MatrixProjection(45.0f, (float)core::Window::Width / (float)core::Window::Height, _fNearPlane, _fFarPlane);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, core::Window::Width / core::Window::Height, _fNearPlane, _fFarPlane);
}

void Camera::_MoveForward()
{
    vLookAt.x += (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::_MoveBackward()
{
    vLookAt.x  -= (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::_MoveRight()
{
    vLookAt.x += (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::_MoveLeft()
{
    vLookAt.x  -= (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::_RotateLeft()
{
     _fRotationAngleXZ -= _fCameraRotationSpeed;
}

void Camera::_RotateRight()
{
     _fRotationAngleXZ += _fCameraRotationSpeed;
}


void Camera::Update()
{
	if( core::Input::mouseR )
	{
		int diffx = core::Input::currentMousePosition.x - core::Input::oldMousePosition.x; 
		int diffy = core::Input::currentMousePosition.y - core::Input::oldMousePosition.y; 

		core::Input::oldMousePosition.x = core::Input::currentMousePosition.x;
		core::Input::oldMousePosition.y = core::Input::currentMousePosition.y;
		
		if(diffx < 0)
			_MoveRight();
		if(diffx > 0)
			_MoveLeft();
		if(diffy > 0)
			_MoveForward();
		if(diffy < 0)
			_MoveBackward();

	}

	if(core::Input::keys[VK_LEFT])
		_RotateLeft();

	if(core::Input::keys[VK_RIGHT])
		_RotateRight();

	if(core::Input::keys[VK_UP])
		_MoveForward();

	if(core::Input::keys[VK_DOWN])
		_MoveBackward();

	vRotation.y = _fRotationAngleXZ * 0.0174532925f;
	vRotation.x = _fRotationAngleY * 0.0174532925f;
    vPosition.y = 32.0f;
	vLookAt.y = 0.0f;
    vPosition.x = vLookAt.x + cos(-(vRotation.y) + 1.57f)* - 32.0f;
    vPosition.z = vLookAt.z + sin(-(vRotation.y) + 1.57f)* - 32.0f;

	mView = math::matrix::MatrixView(vPosition,vLookAt,vUp);
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glMultMatrixf(mView.m);
}