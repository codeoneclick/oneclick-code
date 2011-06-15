#include "CLight.h"

using namespace Enviroment;


CLight::CLight()
{
	m_Time = 0.0f;
	m_TimeIncValue = 0.01f;
	m_Direction = math::Vector3d(0.0f,1.0f,0.0f);
}

void CLight::Update()
{
	m_Time += m_TimeIncValue;
	m_Direction.x = 0.0f;
	m_Direction.y = (float)cos(m_Time * 0.1f);
	m_Direction.z = (float)sin(m_Time * 0.1f);	
	m_Direction.normalize();
}