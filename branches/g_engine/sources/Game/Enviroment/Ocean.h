#ifndef _OCEAN_H_
#define _OCEAN_H_

#include <string>
#include <math.h>
#include "Dummy.h"
#include "../../Math/Matrix4x4.h"

namespace Enviroment
{
class COcean : public CDummy
{
	struct SVertex
	{
		math::Vector3d vPosition;
		math::Vector2d vTexCoord;
	};
	private :
		unsigned int   m_Width;
		unsigned int   m_Height;
	public :
		COcean();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
};
};

#endif