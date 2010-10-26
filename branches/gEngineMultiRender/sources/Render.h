#ifndef _RENDER_H_
#define _RENDER_H_

#include "Core/IDevice.h"

namespace Core
{
	class CRender
	{
	private :

	public :
		CRender();
		~CRender();
		static void BeginRender();
		static void EndRender();
		static void SetViewport(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height);
		static void Draw(unsigned int _vertex_count,unsigned int _index_count,unsigned int _primitive_count);
	};
};

#endif