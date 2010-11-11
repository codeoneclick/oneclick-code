#ifndef CRENDERD3D_H
#define CRENDERD3D_H

#include <d3dx9.h>
#include "IRender.h"

namespace Core
{
	class CRenderD3D : public IRender
	{
	private :
		LPDIRECT3DSURFACE9 m_OldRenderSurface;
		LPDIRECT3DSURFACE9 m_OldStencilSurface;
		LPDIRECT3DSURFACE9 m_CurrentStencilSurface;
		D3DVIEWPORT9 m_OldViewport;
	public :
		CRenderD3D();
		~CRenderD3D();
		virtual void BeginRender();
		virtual void EndRender();
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count);
		virtual void BeginRenderTarget(ITexture *_texture);
		virtual void EndRenderTarget();
	};
};

#endif
