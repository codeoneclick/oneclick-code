#ifndef EDITBRUSH_H
#define EDITBRUSH_H

#include "Dummy.h"
#include "Landscape.h"

namespace Enviroment
{
	class CEditBrush : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vExtValue;
		};

	private :
		unsigned int   m_Width;
		unsigned int   m_Height;
		std::string    m_Name;
		CLandscape*    m_Landscape;
		float		   m_heightOffset;
		math::Vector2d m_brush2DPosition;
		float		   m_workingRadius;
	public :
		CEditBrush(CLandscape* _landscape);
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
		inline  void Set2DPosition(math::Vector2d _position) { m_brush2DPosition = _position; };
		inline  void SetWorkingRadius(float _value) { m_workingRadius = _value; };
	};
};

#endif

