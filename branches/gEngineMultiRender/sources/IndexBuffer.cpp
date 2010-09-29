#include "IndexBuffer.h"
#include "Window.h"

CIndexBuffer::CIndexBuffer()
{
	_m_ogl_addr = 0;
	_m_dx_addr = NULL;
	_m_index_count = 0;
	_m_ib_data = NULL;
}

CIndexBuffer::~CIndexBuffer()
{
	if(_m_ib_data != NULL)
	{
		delete[] _m_ib_data;
		_m_ib_data = NULL;
	}
}

unsigned int* CIndexBuffer::Load(unsigned int index_count)
{
	_m_index_count = index_count;

	if(core::Window::m_D3DRender)
	{
		core::Window::m_D3DDevice->CreateIndexBuffer( _m_index_count*sizeof(unsigned int),D3DUSAGE_WRITEONLY,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&_m_dx_addr,NULL);
		_m_dx_addr->Lock(0, _m_index_count*sizeof(unsigned int), (void**)&_m_ib_data, D3DLOCK_NOSYSLOCK);
	}
	else
	{
		if(_m_ib_data != NULL)
		{
			delete[] _m_ib_data;
			_m_ib_data = NULL;
		}
		_m_ib_data = new unsigned int[_m_index_count]; 
	}
	return _m_ib_data;
}

void CIndexBuffer::CommitVRAM()
{

	if(core::Window::m_D3DRender)
	{
		 _m_dx_addr->Unlock();
	}
	else
	{
		Extension::VBExtension::glGenBuffersARB( 1, &_m_ogl_addr );							
		Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _m_ogl_addr );		
		Extension::VBExtension::glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _m_index_count * sizeof(unsigned int), _m_ib_data, GL_STATIC_DRAW_ARB );
		Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	}

}

unsigned int *CIndexBuffer::Lock()
{
	unsigned int *_lock_ib_data = NULL;
	if(core::Window::m_D3DRender)
	{
		_m_dx_addr->Lock(0, _m_index_count*sizeof(unsigned int), (void**)&_lock_ib_data, D3DLOCK_NOSYSLOCK);
	}
	else
	{
		_lock_ib_data = (unsigned int*)Extension::VBExtension::glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	}
	return _lock_ib_data;
} 

void CIndexBuffer::Unlock()
{
	if(core::Window::m_D3DRender)
	{
		_m_dx_addr->Unlock();
	}
	else
	{
		Extension::VBExtension::glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);
	}
}

void CIndexBuffer::Enable()
{
	if(core::Window::m_D3DRender)
	{
		core::Window::m_D3DDevice->SetIndices(_m_dx_addr);
	}
	else
	{
		Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _m_ogl_addr );
	}
}

void CIndexBuffer::Disable()
{
	Extension::VBExtension::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
}