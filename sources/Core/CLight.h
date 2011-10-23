#ifndef _CLIGHT_H_
#define _CLIGHT_H_
#include "Windows.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix4x4.h"

#define PI_VALUE 3.141592654f

namespace Enviroment
{
	class CLight
	{
	private :
		float m_Time;
		float m_TimeIncValue;
		math::Vector3d m_Direction;
	public :
		CLight();
		void Update();
		inline math::Vector3d GetDirection() { return m_Direction; }
		inline float &GetTime() { return m_Time; }
	};
};

#endif