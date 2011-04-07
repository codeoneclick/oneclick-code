#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Windows.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix4x4.h"
#include "../Game/Enviroment/Dummy.h"

namespace Enviroment
{
class Camera
{
	private :
		float m_fRotationAngleY;
		float m_fRotationAngleXZ;
		float m_fCameraMoveSpeed;
		float m_fCameraRotationSpeed;
		float m_fNearPlane;
		float m_fFarPlane;
		float m_fFov;
		float m_fDistance;
		float m_aFrustumPlanes[6][4];

		CDummy *m_target;

		void MoveForward();
		void MoveBackward();
		void MoveRight();
		void MoveLeft();
		void RotateLeft();
		void RotateRight();
		void RefreshFrustumPlanes();

		void MouseController();
		void KeyboardController();
		
	public :
		math::Vector3d vPosition;
		math::Vector3d vRotation;
		math::Vector3d vLookAt;
		math::Vector3d vUp;
		math::Matrix4x4 mView;
		math::Matrix4x4 mProjection;
		Camera();
		void Update();
		bool IsBoundingSphereInFrustum( float _x, float _z, float _fRadius );
		inline void SetTarget(CDummy *_target) { m_target = _target; };
		inline void SetDistanceToTarget(float _distance) { m_fDistance = _distance; }

		math::Vector3d m_LightDir;
};
};

#endif