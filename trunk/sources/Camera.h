#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Windows.h"
#include "Vector3d.h"
#include "Matrix4x4.h"

namespace Enviroment
{
class Camera
{
	private :
		float _fRotationAngleY;
		float _fRotationAngleXZ;
		float _fCameraMoveSpeed;
		float _fCameraRotationSpeed;
		float _fNearPlane;
		float _fFarPlane;

		void _MoveForward();
		void _MoveBackward();
		void _MoveRight();
		void _MoveLeft();
		void _RotateLeft();
		void _RotateRight();
	public :
		math::vector::Vector3d vPosition;
		math::vector::Vector3d vRotation;
		math::vector::Vector3d vLookAt;
		math::vector::Vector3d vUp;
		math::matrix::Matrix4x4 mView;
		math::matrix::Matrix4x4 mProjection;
		Camera();
		void Update();
};
};

#endif