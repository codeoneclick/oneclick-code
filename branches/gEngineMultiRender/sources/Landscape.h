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

		struct SChunk
		{
			math::Vector2d index;
			bool bVisible;
		};

	private :
		float m_MapScaleFactor;
		float m_MapHeightFactor;
		float m_TextureScaleFactor;
		unsigned int m_ChunkSize;
		unsigned int   m_Width;
		unsigned int   m_Height;
		float          **m_MapData;
		std::map<std::string,SChunk> m_ChunkArray;
		void ReadData(std::string _fileName);
		std::string m_Name;
		std::string m_FirstChunkName;
	public :
		CLandscape();
		virtual void Load(std::string _fileName);
		virtual void Update();
		virtual void Render();
		__forceinline float** GetHeightData() { return m_MapData; }
		__forceinline unsigned int GetWidth() { return m_Width; }
		__forceinline unsigned int GetHeight() { return m_Height; }
		__forceinline float GetScaleFactor() { return m_MapScaleFactor; }
		__forceinline float GetHeightFactor() { return m_MapHeightFactor; }
	};
};

#endif

