#include "IndexBuffer.h"

CIndexBuffer::CIndexBuffer()
{
	_addr_ptr  = 0;
	_nIndeces = 0;
	_ib_data = NULL;
}

CIndexBuffer::~CIndexBuffer()
{
	if(_ib_data != NULL)
	{
		delete[] _ib_data;
		_ib_data = NULL;
	}
}

unsigned int* CIndexBuffer::Create(unsigned int nIndeces)
{
	_nIndeces = nIndeces;

	if(_ib_data != NULL)
	{
		delete[] _ib_data;
		_ib_data = NULL;
	}
	_ib_data = new unsigned int[_nIndeces]; 
	return _ib_data;
}

void CIndexBuffer::Commit()
{
	if(_addr_ptr != 0)
	{
		Extension::VBExtension::glDeleteBuffersARB(1,&_addr_ptr);
		_addr_ptr = 0;
	}

	Extension::VBExtension::glGenBuffersARB( 1, &_addr_ptr );							
	Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _addr_ptr );		
	Extension::VBExtension::glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _nIndeces * sizeof(unsigned int), _ib_data, GL_STATIC_DRAW_ARB );
	Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );

	if(_ib_data != NULL)
	{
		delete[] _ib_data;
		_ib_data = NULL;
	}
}

unsigned int *CIndexBuffer::Lock()
{
	unsigned int *_lock_ib_data = (unsigned int*)Extension::VBExtension::glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	return _lock_ib_data;
} 

void CIndexBuffer::Unlock()
{
	Extension::VBExtension::glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);
}

void CIndexBuffer::Enable()
{
	Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _addr_ptr );
}

void CIndexBuffer::Disable()
{
	Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
}