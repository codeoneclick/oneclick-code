#include "Dummy.h"
#include "Game.h"
#include "Resource.h"
#include "Dummy.h"

using namespace Enviroment;

CDummy::CDummy()
{
	m_mView       = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView;
	m_mProjection = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection;

	m_vCameraPosition = &Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
	m_vLightDirection = new math::Vector3d(0.0f,-1.0f,0.0f);

	m_vPosition = math::Vector3d(0.0f,0.0f,0.0f);
	m_vRotation = math::Vector3d(0.0f,0.0f,0.0f);
	m_vScale    = math::Vector3d(1.0f,1.0f,1.0f);
}

void CDummy::RefreshMatrix()
{
	m_mTranslation = math::Translation(m_vPosition);
	m_mRotationX = math::RotationX(m_vRotation.x);
	m_mRotationY = math::RotationY(m_vRotation.y);
	m_mRotationZ = math::RotationZ(m_vRotation.z);
	m_mScale = math::Scale(m_vScale);
	m_mRotation = m_mRotationY * m_mRotationZ * m_mRotationX;
	m_mWorld = m_mScale * m_mRotation * m_mTranslation;
	m_mWorldViewProjection = m_mWorld * (*m_mView) * (*m_mProjection);
}