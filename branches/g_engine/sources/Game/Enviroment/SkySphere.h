#ifndef CSKYSPHERE_H
#define CSKYSPHERE_H

#include "Dummy.h"

namespace Enviroment
{
	class CSkySphere : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
		};

		struct SXVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
			char value[12];
		};

		ID3DXMesh* m_d3dMesh;

		math::Vector3d GetSunColor(float _theta, int _turbidity);

	public :
		CSkySphere();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
	};
};

#endif

