#include "Camera.h"
#include "Window.h"
#include "Input.h"

using namespace Enviroment;

#define TO_RAD 0.0174532925f

Camera::Camera()
{
	vPosition = math::Vector3d(0.0f,0.0f,0.0f);
	vRotation = math::Vector3d(0.0f,0.0f,0.0f);
	vLookAt   = math::Vector3d(0.0f,0.0f,0.0f);
	vUp       = math::Vector3d(0.0f,1.0f,0.0f);
	m_fFov = 45.0f;
	m_fRotationAngleXZ = 0.0f;
	m_fRotationAngleY  = 0.0f;
	m_fCameraMoveSpeed = 0.5f;
	m_fCameraRotationSpeed = 0.5f;
	m_fNearPlane = 0.1f;
	m_fFarPlane  = 1024.0f;
	m_fDistance = 8.0f;
	mProjection = math::MatrixProjection(m_fFov, (float)Core::CWindow::m_Width / (float)Core::CWindow::m_Height, m_fNearPlane, m_fFarPlane);
}

void Camera::MoveForward()
{
    vLookAt.x += (float)sin(m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
    vLookAt.z += (float)cos(m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
}

void Camera::MoveBackward()
{
    vLookAt.x  -= (float)sin(m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
    vLookAt.z  -= (float)cos(m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
}

void Camera::MoveRight()
{
    vLookAt.x += (float)cos(-m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
    vLookAt.z += (float)sin(-m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
}

void Camera::MoveLeft()
{
    vLookAt.x  -= (float)cos(-m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
    vLookAt.z  -= (float)sin(-m_fRotationAngleXZ*TO_RAD) * m_fCameraMoveSpeed;
}

void Camera::RotateLeft()
{
     m_fRotationAngleXZ -= m_fCameraRotationSpeed;
}

void Camera::RotateRight()
{
     m_fRotationAngleXZ += m_fCameraRotationSpeed;
}


void Camera::Update()
{
	//KeyboardController();

	vRotation.y = m_fRotationAngleXZ * TO_RAD;
	//vRotation.x = m_fRotationAngleY * TO_RAD;
    vPosition.x = vLookAt.x + cos(-(vRotation.y) + 1.57f)* - m_fDistance;
    vPosition.z = vLookAt.z + sin(-(vRotation.y) + 1.57f)* - m_fDistance;

	mView = math::MatrixView(vPosition,vLookAt,vUp);
	RefreshFrustumPlanes();
}

void Camera::MouseController()
{
	if( core::Input::mouseR )
	{
		int diffx = core::Input::currentMousePosition.x - core::Input::oldMousePosition.x; 
		int diffy = core::Input::currentMousePosition.y - core::Input::oldMousePosition.y; 

		core::Input::oldMousePosition.x = core::Input::currentMousePosition.x;
		core::Input::oldMousePosition.y = core::Input::currentMousePosition.y;
		
		if(diffx < 0)
			MoveRight();
		if(diffx > 0)
			MoveLeft();
		if(diffy > 0)
			MoveForward();
		if(diffy < 0)
			MoveBackward();
	}

	if( core::Input::mouseL )
	{
		int diffx = core::Input::currentMousePosition.x - core::Input::oldMousePosition.x; 
		int diffy = core::Input::currentMousePosition.y - core::Input::oldMousePosition.y; 

		core::Input::oldMousePosition.x = core::Input::currentMousePosition.x;
		core::Input::oldMousePosition.y = core::Input::currentMousePosition.y;

		if(diffx < 0)
			RotateLeft();
		if(diffx > 0)
			RotateRight();
	}
}

void Camera::KeyboardController()
{
	if(core::Input::keys[VK_LEFT])
		RotateLeft();

	if(core::Input::keys[VK_RIGHT])
		RotateRight();

	if(core::Input::keys[VK_UP])
		MoveForward();

	if(core::Input::keys[VK_DOWN])
		MoveBackward();
}

void Camera::RefreshFrustumPlanes()
{
	math::Matrix4x4 mViewProjection = mView * mProjection;
	float t;

    //
    // Extract the frustum's right clipping plane and normalize it.
    //

	m_aFrustumPlanes[0][0] = mViewProjection.m[ 3] - mViewProjection.m[ 0];
    m_aFrustumPlanes[0][1] = mViewProjection.m[ 7] - mViewProjection.m[ 4];
    m_aFrustumPlanes[0][2] = mViewProjection.m[11] - mViewProjection.m[ 8];
    m_aFrustumPlanes[0][3] = mViewProjection.m[15] - mViewProjection.m[12];

    t = (float) sqrt( m_aFrustumPlanes[0][0] * m_aFrustumPlanes[0][0] + 
                      m_aFrustumPlanes[0][1] * m_aFrustumPlanes[0][1] + 
                      m_aFrustumPlanes[0][2] * m_aFrustumPlanes[0][2] );

    m_aFrustumPlanes[0][0] /= t;
    m_aFrustumPlanes[0][1] /= t;
    m_aFrustumPlanes[0][2] /= t;
    m_aFrustumPlanes[0][3] /= t;

    //
    // Extract the frustum's left clipping plane and normalize it.
    //

    m_aFrustumPlanes[1][0] = mViewProjection.m[ 3] + mViewProjection.m[ 0];
    m_aFrustumPlanes[1][1] = mViewProjection.m[ 7] + mViewProjection.m[ 4];
    m_aFrustumPlanes[1][2] = mViewProjection.m[11] + mViewProjection.m[ 8];
    m_aFrustumPlanes[1][3] = mViewProjection.m[15] + mViewProjection.m[12];

    t = (float) sqrt( m_aFrustumPlanes[1][0] * m_aFrustumPlanes[1][0] + 
                      m_aFrustumPlanes[1][1] * m_aFrustumPlanes[1][1] + 
                      m_aFrustumPlanes[1][2] * m_aFrustumPlanes[1][2] );

    m_aFrustumPlanes[1][0] /= t;
    m_aFrustumPlanes[1][1] /= t;
    m_aFrustumPlanes[1][2] /= t;
    m_aFrustumPlanes[1][3] /= t;

    //
    // Extract the frustum's bottom clipping plane and normalize it.
    //

    m_aFrustumPlanes[2][0] = mViewProjection.m[ 3] + mViewProjection.m[ 1];
    m_aFrustumPlanes[2][1] = mViewProjection.m[ 7] + mViewProjection.m[ 5];
    m_aFrustumPlanes[2][2] = mViewProjection.m[11] + mViewProjection.m[ 9];
    m_aFrustumPlanes[2][3] = mViewProjection.m[15] + mViewProjection.m[13];

    t = (float) sqrt( m_aFrustumPlanes[2][0] * m_aFrustumPlanes[2][0] + 
                      m_aFrustumPlanes[2][1] * m_aFrustumPlanes[2][1] + 
                      m_aFrustumPlanes[2][2] * m_aFrustumPlanes[2][2] );

    m_aFrustumPlanes[2][0] /= t;
    m_aFrustumPlanes[2][1] /= t;
    m_aFrustumPlanes[2][2] /= t;
    m_aFrustumPlanes[2][3] /= t;

    //
    // Extract the frustum's top clipping plane and normalize it.
    //

    m_aFrustumPlanes[3][0] = mViewProjection.m[ 3] - mViewProjection.m[ 1];
    m_aFrustumPlanes[3][1] = mViewProjection.m[ 7] - mViewProjection.m[ 5];
    m_aFrustumPlanes[3][2] = mViewProjection.m[11] - mViewProjection.m[ 9];
    m_aFrustumPlanes[3][3] = mViewProjection.m[15] - mViewProjection.m[13];

    t = (float) sqrt( m_aFrustumPlanes[3][0] * m_aFrustumPlanes[3][0] + 
                      m_aFrustumPlanes[3][1] * m_aFrustumPlanes[3][1] + 
                      m_aFrustumPlanes[3][2] * m_aFrustumPlanes[3][2] );

    m_aFrustumPlanes[3][0] /= t;
    m_aFrustumPlanes[3][1] /= t;
    m_aFrustumPlanes[3][2] /= t;
    m_aFrustumPlanes[3][3] /= t;

    //
    // Extract the frustum's far clipping plane and normalize it.
    //

    m_aFrustumPlanes[4][0] = mViewProjection.m[ 3] - mViewProjection.m[ 2];
    m_aFrustumPlanes[4][1] = mViewProjection.m[ 7] - mViewProjection.m[ 6];
    m_aFrustumPlanes[4][2] = mViewProjection.m[11] - mViewProjection.m[10];
    m_aFrustumPlanes[4][3] = mViewProjection.m[15] - mViewProjection.m[14];

    t = (float) sqrt( m_aFrustumPlanes[4][0] * m_aFrustumPlanes[4][0] +  
                      m_aFrustumPlanes[4][1] * m_aFrustumPlanes[4][1] + 
                      m_aFrustumPlanes[4][2] * m_aFrustumPlanes[4][2] );

    m_aFrustumPlanes[4][0] /= t;
    m_aFrustumPlanes[4][1] /= t;
    m_aFrustumPlanes[4][2] /= t;
    m_aFrustumPlanes[4][3] /= t;

    //
    // Extract the frustum's near clipping plane and normalize it.
    //

    m_aFrustumPlanes[5][0] = mViewProjection.m[ 3] + mViewProjection.m[ 2];
    m_aFrustumPlanes[5][1] = mViewProjection.m[ 7] + mViewProjection.m[ 6];
    m_aFrustumPlanes[5][2] = mViewProjection.m[11] + mViewProjection.m[10];
    m_aFrustumPlanes[5][3] = mViewProjection.m[15] + mViewProjection.m[14];

    t = (float) sqrt( m_aFrustumPlanes[5][0] * m_aFrustumPlanes[5][0] + 
                      m_aFrustumPlanes[5][1] * m_aFrustumPlanes[5][1] + 
                      m_aFrustumPlanes[5][2] * m_aFrustumPlanes[5][2] );

    m_aFrustumPlanes[5][0] /= t;
    m_aFrustumPlanes[5][1] /= t;
    m_aFrustumPlanes[5][2] /= t;
    m_aFrustumPlanes[5][3] /= t;
}

bool Camera::IsBoundingSphereInFrustum( float x, float z, float fRadius )
{
    for( int i = 0; i < 6; ++i )
    {
        if( m_aFrustumPlanes[i][0] * z +
            m_aFrustumPlanes[i][1] * 0 +
            m_aFrustumPlanes[i][2] * x +
            m_aFrustumPlanes[i][3] <= -fRadius )
            return false;
    }

    return true;
}