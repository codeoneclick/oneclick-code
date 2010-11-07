#ifndef CVERTEXBUFFERD3D_H
#define CVERTEXBUFFERD3D_H

#include <d3dx9.h>

#include "IVertexBuffer.h"

namespace Core
{
	class CVertexBufferD3D : public IVertexBuffer 
	{
	private :
		IDirect3DVertexBuffer9* m_addr;
		LPDIRECT3DVERTEXDECLARATION9 m_declaration_ref;
	public :
		CVertexBufferD3D();
		~CVertexBufferD3D();

		virtual void* Load(unsigned int _vertex_count, unsigned int _element_size);
		virtual void CommitToVRAM();
		virtual void SetDeclaration(SVertexDeclaration &_declaration);
		virtual void* Lock();
		virtual void Unlock();
		virtual void Enable();
		virtual void Disable();
	};
};

#endif