/*#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_
#include <d3dx9.h>
#include "VBExtension.h"
#include "Vector3d.h"

class CIndexBuffer
{
	protected :
		unsigned int _m_ogl_addr;
		IDirect3DIndexBuffer9* _m_dx_addr;

		unsigned int _m_index_count;

		unsigned int *_m_ib_data;

	public :
		CIndexBuffer();
		~CIndexBuffer();
		unsigned int*  Load(unsigned int index_count);
		void CommitVRAM();
		unsigned int* Lock();
		void Unlock();
		void Enable();
		void Disable();
		const unsigned int GetIndexCount() { return _m_index_count; }
		const unsigned int GetPrimitiveCount() { return _m_index_count / 3; }
};

#endif*/
