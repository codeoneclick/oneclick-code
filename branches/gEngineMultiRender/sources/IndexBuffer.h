#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_
#include "VBExtension.h"
#include "Vector3d.h"

class CIndexBuffer
{
	protected :
		unsigned int _addr_ptr;
		unsigned int _nIndeces;
		unsigned int *_ib_data;
	public :
		CIndexBuffer();
		~CIndexBuffer();
		unsigned int* Create(unsigned int nIndeces);
		void  Commit();
		unsigned int* Lock();
		void  Unlock();
		void  Enable();
		void  Disable();
		const unsigned int GetNumIndeces() { return _nIndeces; }
};

#endif
