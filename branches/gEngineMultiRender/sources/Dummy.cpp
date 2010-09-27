#include "Dummy.h"
#include "Game.h"
#include "Resource.h"

using namespace Enviroment;

CDummy::CDummy()
{
	_mView       = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView;
	_mProjection = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection;

	_vCameraPosition = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
	_vLightDirection = new math::Vector3d(0.0f,-1.0f,0.0f);

	vPosition = math::Vector3d(0.0f,0.0f,0.0f);
	vRotation = math::Vector3d(0.0f,0.0f,0.0f);
	vScale    = math::Vector3d(1.0f,1.0f,1.0f);

	//_shader = new Core::CShader();
    //_shader->Create("basic");
}

void CDummy::_UpdateMatrix()
{
	_mTranslation = math::Translation(vPosition);
	_mRotationX = math::RotationX(vRotation.x);
	_mRotationY = math::RotationY(vRotation.y);
	_mRotationZ = math::RotationZ(vRotation.z);
	_mScale = math::Scale(vScale);
	_mRotation = _mRotationY*_mRotationZ*_mRotationX;
	_mWorld = _mScale*_mRotation*_mTranslation;
	_mWorldViewProjection = _mWorld * (*_mView) * (*_mProjection);
}