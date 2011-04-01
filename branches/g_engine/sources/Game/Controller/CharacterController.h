#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "../../Core/Camera.h"
#include "../Enviroment/Landscape.h"
#include "../Enviroment/Model.h"
#include "RenderController.h"
#include <stdlib.h>
#include <string>
#include <map>

#define TO_RAD 0.0174532925f
#define UPDATE_INTERVAL 8

namespace Enviroment
{
class CharacterController
{
private :
	Camera* m_camera;
	CDummy* m_character;
	CDummy* m_landscape;
	float GetLandscapeHeight(float _fPosition_x,float _fPosition_z);
	math::Vector3d GetLandscapeRotation(math::Vector3d _vPosition);
	float GetRotationFromNormal(math::Vector3d _vPosition_01,math::Vector3d _vPosition_02);
	
	void KeyboardController();
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void RotateLeft();
	void RotateRight();

	float m_currentMoveSpeed;
	float m_minMoveSpeed;
	float m_maxForwardMoveSpeed;
	float m_maxBackwardMoveSpeed;
	float m_moveAcceleration;
	float m_rotationSpeed;
	float m_dragFactor;

	math::Vector3d m_vPosition;
	math::Vector3d m_vRotation;

	bool IsReadyForUpdate();
public :
	CharacterController(Camera* _camera, CDummy* _character, CDummy* _landscape);
	void Update(DWORD time);
};
};

#endif