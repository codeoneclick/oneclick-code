#include "VertexBuffer.h"
#include "Device.h"

CVertexBuffer::CVertexBuffer()
{
	_m_ogl_addr = 0;
	_m_dx_addr = NULL;
	_m_vertex_count = 0;
	_m_vb_data = NULL;
	_m_element_size = 0;
	_m_declaration.m_ElementCount = 0;
	_m_declaration.m_Elements = NULL;
	_prt_vertex_declaration = NULL;
}

CVertexBuffer::~CVertexBuffer()
{
	if(_m_vb_data != NULL)
	{
		delete[] _m_vb_data;
		_m_vb_data = NULL;
	}
}

void* CVertexBuffer::Load(unsigned int vertex_count, unsigned int element_size)
{
	_m_element_size = element_size;
	_m_vertex_count = vertex_count;

	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		Core::CDevice::GetD3DDevice()->CreateVertexBuffer(vertex_count * element_size,D3DUSAGE_WRITEONLY,NULL,D3DPOOL_DEFAULT,&_m_dx_addr,NULL);
		_m_dx_addr->Lock(0,vertex_count * element_size, (void**)&_m_vb_data,D3DLOCK_NOSYSLOCK);
	}
	else
	{
		if(_m_vb_data != NULL)
		{
			delete[] _m_vb_data;
			_m_vb_data = NULL;
		}
		_m_vb_data = new char[_m_vertex_count * _m_element_size]; 
	}
	
	return _m_vb_data;
}

void CVertexBuffer::CommitVRAM()
{

	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		_m_dx_addr->Unlock();
	}
	else
	{
		Extension::VBExtension::glGenBuffersARB( 1, &_m_ogl_addr );							
		Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, _m_ogl_addr );		
		Extension::VBExtension::glBufferDataARB( GL_ARRAY_BUFFER_ARB, _m_vertex_count * _m_element_size, _m_vb_data, GL_STATIC_DRAW_ARB );
		Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	}
}

void *CVertexBuffer::Lock()
{
	void *_lock_vb_data = NULL;
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		_m_dx_addr->Lock(0,_m_vertex_count * _m_element_size, (void**)&_lock_vb_data,D3DLOCK_NOSYSLOCK);
	}
	else
	{
		_lock_vb_data = Extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	}
	return _lock_vb_data;
} 

void CVertexBuffer::Unlock()
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		_m_dx_addr->Unlock();
	}
	else
	{
		Extension::VBExtension::glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
	}
}

void CVertexBuffer::SetDeclaration(SVertexDeclaration &_declaration)
{
	_m_declaration = _declaration;

	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		D3DVERTEXELEMENT9 *dx_vertex_declaration = new D3DVERTEXELEMENT9[_m_declaration.m_ElementCount + 1];
		for( unsigned int i = 0; i < _m_declaration.m_ElementCount; ++i)
		{
			dx_vertex_declaration[i].Stream = 0;
			dx_vertex_declaration[i].Offset = _m_declaration.m_Elements[i].m_Offset;
			dx_vertex_declaration[i].Type = _m_declaration.m_Elements[i].m_Size - 1;
			dx_vertex_declaration[i].Method = D3DDECLMETHOD_DEFAULT;
			dx_vertex_declaration[i].Usage = _m_declaration.m_Elements[i].m_Type;
			dx_vertex_declaration[i].UsageIndex = _m_declaration.m_Elements[i].m_Index;
		}

		dx_vertex_declaration[_m_declaration.m_ElementCount].Stream = 0xFF;
		dx_vertex_declaration[_m_declaration.m_ElementCount].Offset = 0;
		dx_vertex_declaration[_m_declaration.m_ElementCount].Type = D3DDECLTYPE_UNUSED;
		dx_vertex_declaration[_m_declaration.m_ElementCount].Method = 0;
		dx_vertex_declaration[_m_declaration.m_ElementCount].Usage = 0;
		dx_vertex_declaration[_m_declaration.m_ElementCount].UsageIndex = 0;
		
		Core::CDevice::GetD3DDevice()->CreateVertexDeclaration(dx_vertex_declaration,&_prt_vertex_declaration);
		delete[] dx_vertex_declaration;
	}
}

void CVertexBuffer::Enable()
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		Core::CDevice::GetD3DDevice()->SetVertexDeclaration(_prt_vertex_declaration);
		Core::CDevice::GetD3DDevice()->SetStreamSource( 0,_m_dx_addr, 0, _m_element_size);
	}
	else
	{
		for( unsigned int i = 0; i < _m_declaration.m_ElementCount; ++i)
		{
			switch(_m_declaration.m_Elements[i].m_Type)
			{
			case ELEMENT_POSITION :
				{
					Extension::VBExtension::glBindBufferARB(GL_ARRAY_BUFFER_ARB, _m_ogl_addr);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(_m_declaration.m_Elements[i].m_Size, GL_FLOAT, _m_element_size, (void*)_m_declaration.m_Elements[i].m_Offset );
				}
				break;
			case ELEMENT_NORMAL :
				{
					glEnableClientState(GL_NORMAL_ARRAY);
					glNormalPointer(GL_FLOAT, _m_element_size, (void*)_m_declaration.m_Elements[i].m_Offset);
				}
				break;
			case ELEMENT_TEXCOORD :
				{
					Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE0 + _m_declaration.m_Elements[i].m_Index);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glTexCoordPointer(_m_declaration.m_Elements[i].m_Size, GL_FLOAT, _m_element_size, (void*)_m_declaration.m_Elements[i].m_Offset);
				}
				break;
			case ELEMENT_TANGENT :

				break;
			case ELEMENT_BINORMAL :

				break;
			}
		}
	}
}

void CVertexBuffer::Disable()
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D) return;
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE0);
	Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );	
}