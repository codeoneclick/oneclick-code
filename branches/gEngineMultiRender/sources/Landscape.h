#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_
#include "Dummy.h"
#include "VertexBuffer.h"
#include "StructExt.h"

namespace Enviroment
{
	class Landscape : public CDummy
	{
	private :
		unsigned int   m_Width;
		unsigned int   m_Height;
		float          **m_MapData;
		void CalculateTBN(CVertexBuffer::SVertexVTTBN *_vertexData,unsigned int *_indexData, unsigned int _nVerteces,unsigned int _nIndeces);
	public :
		Landscape();
		virtual void Load(std::string _fileName);
		virtual void Update();
		virtual void Render();
	};
};

#endif