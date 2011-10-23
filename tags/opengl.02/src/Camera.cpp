#include "Camera.h"

Camera::Camera()
{
	vPosition = Vector3d(0.0f,0.0f,0.0f);
	vRotation = Vector3d(0.0f,0.0f,0.0f);
	vLookAt   = Vector3d(64.0f,0.0f,64.0f);
	vUp       = Vector3d(0.0f,1.0f,0.0f);
	_fRotationAngleXZ = 0.0f;
	_fRotationAngleY  = 0.0f;
	_fCameraMoveSpeed = 0.5f;
	_fCameraRotationSpeed = 1.0f;
	mProjection = MatrixProjection(45.0f, (float)800 / (float)600, 0.1f,1000.0f);
}

void Camera::MoveForward()
{
    vLookAt.x += (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::MoveBackward()
{
    vLookAt.x  -= (float)sin(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)cos(_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::MoveRight()
{
    vLookAt.x += (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z += (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::MoveLeft()
{
    vLookAt.x  -= (float)cos(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
    vLookAt.z  -= (float)sin(-_fRotationAngleXZ*0.0174532925f) * _fCameraMoveSpeed;
}

void Camera::RotateLeft()
{
     _fRotationAngleXZ -= _fCameraRotationSpeed;
}

void Camera::RotateRight()
{
     _fRotationAngleXZ += _fCameraRotationSpeed;
}


void Camera::Update()
{
	if( Input::mLeftDown )
	{
		int diffx = Input::mCurrentPosition.x - Input::mLastPosition.x; 
		int diffy = Input::mCurrentPosition.y - Input::mLastPosition.y; 

		Input::mLastPosition.x = Input::mCurrentPosition.x;
		Input::mLastPosition.y = Input::mCurrentPosition.y;

		_fRotationAngleXZ += (float) diffx/1.0f;
	}

	if(Input::ePressRotateLeft)
		RotateLeft();

	if( Input::ePressRotateRight)
		RotateRight();

	if(Input::ePressForward)
		MoveForward();

	if(Input::ePressBackward)
		MoveBackward();

	if(Input::ePressLeft)
		RotateLeft();

	if(Input::ePressRight)
		RotateRight();

	vRotation.y = _fRotationAngleXZ * 0.0174532925f;
	vRotation.x = _fRotationAngleY * 0.0174532925f;
        
    vPosition.x = vLookAt.x + cos(-(vRotation.y) + 1.57f)* - 16.0f;
    vPosition.z = vLookAt.z + sin(-(vRotation.y) + 1.57f)* - 16.0f;

	mView = MatrixView(vPosition,vLookAt,vUp);

	_UpdateFrustumPlanes();
}


void Camera::_UpdateFrustumPlanes()
{
	Matrix4x4 mViewProjection = mView * mProjection;
	float t;
    //
    // Extract the frustum's right clipping plane and normalize it.
    //

	_frustumPlanes[0][0] = mViewProjection.m[ 3] - mViewProjection.m[ 0];
    _frustumPlanes[0][1] = mViewProjection.m[ 7] - mViewProjection.m[ 4];
    _frustumPlanes[0][2] = mViewProjection.m[11] - mViewProjection.m[ 8];
    _frustumPlanes[0][3] = mViewProjection.m[15] - mViewProjection.m[12];

    t = (float) sqrt( _frustumPlanes[0][0] * _frustumPlanes[0][0] + 
                      _frustumPlanes[0][1] * _frustumPlanes[0][1] + 
                      _frustumPlanes[0][2] * _frustumPlanes[0][2] );

    _frustumPlanes[0][0] /= t;
    _frustumPlanes[0][1] /= t;
    _frustumPlanes[0][2] /= t;
    _frustumPlanes[0][3] /= t;

    //
    // Extract the frustum's left clipping plane and normalize it.
    //

    _frustumPlanes[1][0] = mViewProjection.m[ 3] + mViewProjection.m[ 0];
    _frustumPlanes[1][1] = mViewProjection.m[ 7] + mViewProjection.m[ 4];
    _frustumPlanes[1][2] = mViewProjection.m[11] + mViewProjection.m[ 8];
    _frustumPlanes[1][3] = mViewProjection.m[15] + mViewProjection.m[12];

    t = (float) sqrt( _frustumPlanes[1][0] * _frustumPlanes[1][0] + 
                      _frustumPlanes[1][1] * _frustumPlanes[1][1] + 
                      _frustumPlanes[1][2] * _frustumPlanes[1][2] );

    _frustumPlanes[1][0] /= t;
    _frustumPlanes[1][1] /= t;
    _frustumPlanes[1][2] /= t;
    _frustumPlanes[1][3] /= t;

    //
    // Extract the frustum's bottom clipping plane and normalize it.
    //

    _frustumPlanes[2][0] = mViewProjection.m[ 3] + mViewProjection.m[ 1];
    _frustumPlanes[2][1] = mViewProjection.m[ 7] + mViewProjection.m[ 5];
    _frustumPlanes[2][2] = mViewProjection.m[11] + mViewProjection.m[ 9];
    _frustumPlanes[2][3] = mViewProjection.m[15] + mViewProjection.m[13];

    t = (float) sqrt( _frustumPlanes[2][0] * _frustumPlanes[2][0] + 
                      _frustumPlanes[2][1] * _frustumPlanes[2][1] + 
                      _frustumPlanes[2][2] * _frustumPlanes[2][2] );

    _frustumPlanes[2][0] /= t;
    _frustumPlanes[2][1] /= t;
    _frustumPlanes[2][2] /= t;
    _frustumPlanes[2][3] /= t;

    //
    // Extract the frustum's top clipping plane and normalize it.
    //

    _frustumPlanes[3][0] = mViewProjection.m[ 3] - mViewProjection.m[ 1];
    _frustumPlanes[3][1] = mViewProjection.m[ 7] - mViewProjection.m[ 5];
    _frustumPlanes[3][2] = mViewProjection.m[11] - mViewProjection.m[ 9];
    _frustumPlanes[3][3] = mViewProjection.m[15] - mViewProjection.m[13];

    t = (float) sqrt( _frustumPlanes[3][0] * _frustumPlanes[3][0] + 
                      _frustumPlanes[3][1] * _frustumPlanes[3][1] + 
                      _frustumPlanes[3][2] * _frustumPlanes[3][2] );

    _frustumPlanes[3][0] /= t;
    _frustumPlanes[3][1] /= t;
    _frustumPlanes[3][2] /= t;
    _frustumPlanes[3][3] /= t;

    //
    // Extract the frustum's far clipping plane and normalize it.
    //

    _frustumPlanes[4][0] = mViewProjection.m[ 3] - mViewProjection.m[ 2];
    _frustumPlanes[4][1] = mViewProjection.m[ 7] - mViewProjection.m[ 6];
    _frustumPlanes[4][2] = mViewProjection.m[11] - mViewProjection.m[10];
    _frustumPlanes[4][3] = mViewProjection.m[15] - mViewProjection.m[14];

    t = (float) sqrt( _frustumPlanes[4][0] * _frustumPlanes[4][0] +  
                      _frustumPlanes[4][1] * _frustumPlanes[4][1] + 
                      _frustumPlanes[4][2] * _frustumPlanes[4][2] );

    _frustumPlanes[4][0] /= t;
    _frustumPlanes[4][1] /= t;
    _frustumPlanes[4][2] /= t;
    _frustumPlanes[4][3] /= t;

    //
    // Extract the frustum's near clipping plane and normalize it.
    //

    _frustumPlanes[5][0] = mViewProjection.m[ 3] + mViewProjection.m[ 2];
    _frustumPlanes[5][1] = mViewProjection.m[ 7] + mViewProjection.m[ 6];
    _frustumPlanes[5][2] = mViewProjection.m[11] + mViewProjection.m[10];
    _frustumPlanes[5][3] = mViewProjection.m[15] + mViewProjection.m[14];

    t = (float) sqrt( _frustumPlanes[5][0] * _frustumPlanes[5][0] + 
                      _frustumPlanes[5][1] * _frustumPlanes[5][1] + 
                      _frustumPlanes[5][2] * _frustumPlanes[5][2] );

    _frustumPlanes[5][0] /= t;
    _frustumPlanes[5][1] /= t;
    _frustumPlanes[5][2] /= t;
    _frustumPlanes[5][3] /= t;
}


bool Camera::IsBoundingSphereInFrustum( float x, float z, float fRadius )
{
    for( int i = 0; i < 6; ++i )
    {
        if( _frustumPlanes[i][0] * z +
            _frustumPlanes[i][1] * 0 +
            _frustumPlanes[i][2] * x +
            _frustumPlanes[i][3] <= -fRadius )
            return false;
    }

    return true;
}