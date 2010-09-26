#include "VertexBuffer.h"

CVertexBuffer::CVertexBuffer()
{
	_addr_ptr  = 0;
	_nVerteces = 0;
	_vb_data = NULL;
	_vertexSize = 0;
}

CVertexBuffer::~CVertexBuffer()
{
	if(_vb_data != NULL)
	{
		delete[] _vb_data;
		_vb_data = NULL;
	}
}

void* CVertexBuffer::Create(unsigned int nVerteces, unsigned int vertexSize)
{
	_vertexSize = vertexSize;
	_nVerteces   = nVerteces;

	if(_vb_data != NULL)
	{
		delete[] _vb_data;
		_vb_data = NULL;
	}
	_vb_data = new char[_nVerteces * _vertexSize]; 
	return _vb_data;
}

void CVertexBuffer::Commit()
{
	if(_addr_ptr != 0)
	{
		Extension::VBExtension::glDeleteBuffersARB(1,&_addr_ptr);
		_addr_ptr = 0;
	}

	Extension::VBExtension::glGenBuffersARB( 1, &_addr_ptr );							
	Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, _addr_ptr );		
	Extension::VBExtension::glBufferDataARB( GL_ARRAY_BUFFER_ARB, _nVerteces * _vertexSize, _vb_data, GL_STATIC_DRAW_ARB );
	Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );		

	if(_vb_data != NULL)
	{
		delete[] _vb_data;
		_vb_data = NULL;
	}
}

void *CVertexBuffer::Lock()
{
	void *_lock_vb_data = Extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	return _lock_vb_data;
} 

void CVertexBuffer::Unlock()
{
	Extension::VBExtension::glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
}

void CVertexBuffer::Enable()
{
	if(_vertexSize == 0) 
		return;
	unsigned int _offset = 0;
	Extension::VBExtension::glBindBufferARB(GL_ARRAY_BUFFER_ARB, _addr_ptr);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, _vertexSize, (void*)_offset );
	_offset += 3 * sizeof(float);
	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, _vertexSize, (void*)_offset);
	_offset += 2 * sizeof(float);

	if(_vertexSize == sizeof(CVertexBuffer::SVertexVT)) 
		return;
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, _vertexSize, (void*)_offset);
	_offset += 3 * sizeof(float);
	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE1);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, _vertexSize, (void*)_offset);
	_offset += 3 * sizeof(float);
	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE2);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, _vertexSize, (void*)_offset);
	_offset += 3 * sizeof(float);

	if(_vertexSize == sizeof(CVertexBuffer::SVertexVTTBN)) 
		return;

	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(4, GL_FLOAT, _vertexSize, (void*)_offset);
}

void CVertexBuffer::Disable()
{
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	Extension::VBExtension::glClientActiveTextureCoordARB(GL_TEXTURE0);
	Extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );	
}