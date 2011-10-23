#ifndef CINDEXBUFFERD3D_H
#define CINDEXBUFFERD3D_H

#include <d3dx9.h>

#include "IIndexBuffer.h"

namespace Core
{
	class CIndexBufferD3D : public IIndexBuffer 
	{
	private :
		IDirect3DIndexBuffer9* m_addr;
	public :
		CIndexBufferD3D();
		~CIndexBufferD3D();

		virtual unsigned int*  Load(unsigned int _index_count);
		virtual void CommitToVRAM();
		virtual unsigned int* Lock();
		virtual void Unlock();
		virtual void Enable();
		virtual void Disable();
	};
};

#endif