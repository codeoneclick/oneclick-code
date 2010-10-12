#ifndef _SOARINGISLAND_H_
#define _SOARINGISLAND_H_

#include "Dummy.h"

namespace Enviroment
{
	class CSoaringIsland : public CDummy
	{
	private :
		Core::CMesh *m_TopElement;
		Core::CMesh *m_BottomElement;

		unsigned int   m_Width;
		unsigned int   m_Height;
		float          **m_MapData;
		void CalculateTBN(CVertexBuffer::SVertexVTTBN *_vertexData,unsigned int *_indexData, unsigned int _nVerteces,unsigned int _nIndeces);
	public :
		CSoaringIsland();
		virtual void Load(std::string _fileName);
		virtual void Update();
		virtual void Render();

	};
};

#endif

