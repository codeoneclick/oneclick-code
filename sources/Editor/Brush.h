#ifndef BRUSH_H
#define BRUSH_H

#include "../Game/Enviroment/Dummy.h"
#include "../Game/Enviroment/Landscape.h"

namespace Enviroment
{
	class CBrush : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d<float> m_vExtValue;
		};

	private :
		unsigned int   m_Width;
		unsigned int   m_Height;
		std::string    m_Name;
		CLandscape*    m_Landscape;
		float		   m_heightOffset;
		math::Vector2d<float> m_brush2DPosition;
		float		   m_workingRadius;
	public :
		CBrush(CLandscape* _landscape);
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
		inline  void Set2DPosition(math::Vector2d<float> _position) { m_brush2DPosition = _position; };
		inline  void SetWorkingRadius(float _value) { m_workingRadius = _value; };
	};
};

#endif

