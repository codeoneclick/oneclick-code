#ifndef CVERTEXBUFFERD3D_H
#define CVERTEXBUFFERD3D_H

#include <d3dx9.h>
#include <vector>
#include "IVertexBuffer.h"

namespace Core
{
	class CVertexBufferD3D : public IVertexBuffer 
	{
	private :
		IDirect3DVertexBuffer9* m_addr[k_MAX_STREAM_COUNT];
		LPDIRECT3DVERTEXDECLARATION9 m_declarationRef;
	public :
		CVertexBufferD3D();
		~CVertexBufferD3D();

		virtual void* Load(unsigned int _vertexCount, unsigned int _elementSize, unsigned int _streamId);
		virtual void CommitToVRAM(unsigned int _streamId);
		virtual void SetDeclaration(SVertexDeclaration &_declaration);
		virtual void* Lock(unsigned int _streamId);
		virtual void Unlock(unsigned int _streamId);
		virtual void Enable();
		virtual void Disable();
		virtual void EnableDeclaration();
		virtual void CopyVertexBufferRef(IVertexBuffer *_value, unsigned int _srcStreamId, unsigned int _dstStreamId) { 
																m_addr[_dstStreamId] = ((CVertexBufferD3D*)_value)->m_addr[_srcStreamId]; 
																m_elementSize[_dstStreamId] = ((CVertexBufferD3D*)_value)->m_elementSize[_srcStreamId];
																m_vertexCount = ((CVertexBufferD3D*)_value)->m_vertexCount;
															 }
	};
};

#endif