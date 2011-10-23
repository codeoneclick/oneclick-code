#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vector3d.h"
#include "Matrix4x4.h"
#include "Input.h"

class Camera
{
	private :
		float _fRotationAngleY;
		float _fRotationAngleXZ;
		void MoveForward();
		void MoveBackward();
		void MoveRight();
		void MoveLeft();
		void RotateLeft();
		void RotateRight();
		float _fCameraMoveSpeed;
		float _fCameraRotationSpeed;

		void _UpdateFrustumPlanes();
		float _frustumPlanes[6][4];

	public :
		Vector3d vPosition;
		Vector3d vRotation;
		Vector3d vLookAt;
		Vector3d vUp;
		Matrix4x4 mView;
		Matrix4x4 mProjection;
		Camera();
		void Update();
		bool IsBoundingSphereInFrustum( float x, float z, float fRadius );
};

#endif