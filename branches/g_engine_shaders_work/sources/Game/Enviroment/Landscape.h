#ifndef CLANDSCAPE_H
#define CLANDSCAPE_H

#include "Dummy.h"

namespace Enviroment
{
	class CLandscape : public CDummy
	{
		struct SVertexStreamMesh
		{
			math::Vector3d m_vPosition;
			math::Vector2d m_vTexCoord;
			math::Vector3d m_vNormal;
			math::Vector3d m_vTangent;
		};

		struct SVertexStreamSplatting
		{
			union 
			{
				struct 
				{
					unsigned char m_cSplattingLayer_01, m_cSplattingLayer_02, m_cSplattingLayer_03, m_cSplattingLayer_04;
				};
				int m_vSplatting;
			};
		};

		struct SChunk
		{
			math::Vector2d m_Index;
			bool m_bVisible;
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
		std::string m_FirstChunkName;
	public :
		CLandscape();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
		__forceinline float** GetHeightData() { return m_MapData; }
		__forceinline unsigned int GetWidth() { return m_Width; }
		__forceinline unsigned int GetHeight() { return m_Height; }
		__forceinline float GetScaleFactor() { return m_MapScaleFactor; }
		__forceinline float GetHeightFactor() { return m_MapHeightFactor; }
		void RefreshVB(int _streamId);
		void DrawTraces(float _x, float _z);
	};
};

#endif

