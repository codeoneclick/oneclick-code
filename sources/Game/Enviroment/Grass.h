#ifndef CGRASS_H
#define CGRASS_H

#include "Dummy.h"

namespace Enviroment
{
	class CGrass : public CDummy
	{
		struct SVertex
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
		};

		struct SChunk
		{
			math::Vector2d m_Index;
			bool m_bVisible;
		};

		unsigned int   m_Width;
		unsigned int   m_Height;
		float **m_MapData;
		void ReadData(std::string _fileName);

	public :
		CGrass();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
	};
};

#endif

