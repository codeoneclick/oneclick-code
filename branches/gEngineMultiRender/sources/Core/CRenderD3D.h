#ifndef CRENDERD3D_H
#define CRENDERD3D_H

#include "IRender.h"

namespace Core
{
	class CRenderD3D : public IRender
	{
	public :
		CRenderD3D();
		~CRenderD3D();
		virtual void BeginRender();
		virtual void EndRender();
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count);
	};
};

#endif
