#include "Dummy.h"
#include "Game.h"
#include "Resource.h"

using namespace Enviroment;

CDummy::CDummy()
{
	_mView       = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView;
	_mProjection = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection;

	_vCameraPosition = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
	_vLightDirection = new math::vector::Vector3d(0.0f,-1.0f,0.0f);

	vPosition = math::vector::Vector3d(0.0f,0.0f,0.0f);
	vRotation = math::vector::Vector3d(0.0f,0.0f,0.0f);
	vScale    = math::vector::Vector3d(1.0f,1.0f,1.0f);

	_shader = new CShader();
    _shader->Create("basic");
}

void CDummy::_UpdateMatrix()
{
	_mTranslation = math::matrix::Translation(vPosition);
	_mRotationX = math::matrix::RotationX(vRotation.x);
	_mRotationY = math::matrix::RotationY(vRotation.y);
	_mRotationZ = math::matrix::RotationZ(vRotation.z);
	_mScale = math::matrix::Scale(vScale);
	_mRotation = _mRotationY*_mRotationZ*_mRotationX;
	_mWorld = _mScale*_mRotation*_mTranslation;
	_mWorldViewProjection = _mWorld * (*_mView) * (*_mProjection);
}