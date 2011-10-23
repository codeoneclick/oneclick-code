#ifndef _SOARINGISLAND_H_
#define _SOARINGISLAND_H_

#include "Dummy.h"

namespace Enviroment
{
	class CSoaringIsland : public CDummy
	{
		struct SVertex
		{
			math::Vector3d vPosition;
			math::Vector2d vTexCoord;
			math::Vector3d vNormal;
			math::Vector3d vTangent;
			math::Vector3d vBinormal;
			math::Vector4d vSplatting;
			float fDiscard;
		};

	private :
		float m_TopElementHeightMult;
		float m_BottomElementHeightMult;
		float m_TopElementDiscardOffset;
		float m_BottomElementDiscardOffset;
		float m_MapScaleFactor;
		float m_TextureScaleFactor;
		unsigned int   m_Width;
		unsigned int   m_Height;
		float          **m_MapData;
		void ReadData(std::string _fileName);
	public :
		CSoaringIsland();
		virtual void Load(std::string _fileName);
		virtual void Update();
		virtual void Render();

	};
};

#endif

