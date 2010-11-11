#ifndef IRENDER_H
#define IRENDER_H

#include "ITexture.h"

namespace Core
{
	class IRender
	{
	public :
		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count) = 0;
		virtual void BeginRenderTarget(ITexture *_texture) = 0;
		virtual void EndRenderTarget() = 0;
	};
};

#endif
