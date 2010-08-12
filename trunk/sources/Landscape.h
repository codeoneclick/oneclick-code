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
		unsigned int   _width;
		unsigned int   _height;
		float          **_heightmap;
		void _CalculateTBN(CVertexBuffer::SVertexVTTBN *vertexData,unsigned int *indexData, unsigned int nVerteces,unsigned int nIndeces);
	public :
		Landscape();
		virtual void Load(std::string value);
		virtual void Update();
		virtual void Render();
};
};

#endif