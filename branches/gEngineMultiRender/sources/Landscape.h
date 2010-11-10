#ifndef CLANDSCAPE_H
#define CLANDSCAPE_H

#include "Dummy.h"

namespace Enviroment
{
	class CLandscape : public CDummy
	{
		struct SVertex
		{
			math::Vector3d vPosition;
			math::Vector2d vTexCoord;
			math::Vector3d vNormal;
			math::Vector3d vTangent;
			math::Vector3d vBinormal;
			math::Vector4d vSplatting;
		};

	private :
		float m_MapScaleFactor;
		float m_TextureScaleFactor;
		unsigned int   m_Width;
		unsigned int   m_Height;
		float          **m_MapData;
		void ReadData(std::string _fileName);
	public :
		CLandscape();
		virtual void Load(std::string _fileName);
		virtual void Update();
		virtual void Render();
		__forceinline float** GetHeightData() { return m_MapData; }
		__forceinline unsigned int GetWidth() { return m_Width; }
		__forceinline unsigned int GetHeight() { return m_Height; }
		__forceinline float GetScaleFactor() { return m_MapScaleFactor; }
	};
};

#endif

