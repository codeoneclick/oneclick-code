#pragma once
#ifndef _M3_CAMERA_H_
#define _M3_CAMERA_H_
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vector3d.h"
#include "Matrix4x4.h"
#include "m3_Input.h"

class m3_Camera
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

	public :
		Vector3d vPosition;
		Vector3d vRotation;
		Vector3d vLookAt;
		Matrix4x4 mView;
		Matrix4x4 mProjection;
		m3_Camera();
		void Update();
};

#endif