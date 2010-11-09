#ifndef IRENDER_H
#define IRENDER_H

#include "windows.h"

namespace Core
{
	class IRender
	{
	public :
		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count) = 0;
		virtual void Spitout() = 0;
		virtual void SpitoutTo(HWND _handle) = 0;
	};
};

#endif
