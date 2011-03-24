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
			union 
			{
				struct 
				{
					unsigned char m_cNormalW, m_cNormalX, m_cNormalY, m_cNormalZ;
				};
				int m_vNormal;
			};
			union 
			{
				struct 
				{
					unsigned char m_cTangentW, m_cTangentX, m_cTangentY, m_cTangentZ;
				};
				int m_vTangent;
			};
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
		std::string m_Name;
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
	};
};

#endif

