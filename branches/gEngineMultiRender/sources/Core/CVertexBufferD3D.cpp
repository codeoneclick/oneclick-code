#include "CVertexBufferD3D.h"
#include "IDevice.h"

using namespace Core;

CVertexBufferD3D::CVertexBufferD3D()
{
	for(unsigned int i = 0; i < k_MAX_STREAM_COUNT; ++i)
		m_addr[i] = NULL;
	m_declarationRef = NULL;
}

CVertexBufferD3D::~CVertexBufferD3D()
{

}

void* CVertexBufferD3D::Load(unsigned int _vertexCount, unsigned int _elementSize, unsigned int _streamId)
{
	m_elementSize[_streamId] = _elementSize;
	m_vertexCount = _vertexCount;
	
	Core::IDevice::Ref()->CreateVertexBuffer(m_vertexCount * m_elementSize[_streamId],D3DUSAGE_WRITEONLY,NULL,D3DPOOL_DEFAULT,&m_addr[_streamId],NULL);
	m_addr[_streamId]->Lock(0,m_vertexCount * m_elementSize[_streamId], (void**)&m_data,D3DLOCK_NOSYSLOCK);
	
	return m_data;
}

void CVertexBufferD3D::CommitToVRAM(unsigned int _streamId)
{
	Unlock(_streamId);
}

void* CVertexBufferD3D::Lock(unsigned int _streamId)
{
	m_addr[_streamId]->Lock(0,m_vertexCount * m_elementSize[_streamId], (void**)&m_data,D3DLOCK_NOSYSLOCK);
	return m_data;
}

void CVertexBufferD3D::Unlock(unsigned int _streamId)
{
	m_addr[_streamId]->Unlock();
}

void CVertexBufferD3D::SetDeclaration(Core::IVertexBuffer::SVertexDeclaration &_declaration)
{
	m_declaration = _declaration;
	D3DVERTEXELEMENT9 *dx_vertex_declaration = new D3DVERTEXELEMENT9[m_declaration.m_ElementCount + 1];
	for( unsigned int i = 0; i < m_declaration.m_ElementCount; ++i)
	{
		dx_vertex_declaration[i].Stream = m_declaration.m_Elements[i].m_stream;
		dx_vertex_declaration[i].Offset = m_declaration.m_Elements[i].m_offset;
		dx_vertex_declaration[i].Type = m_declaration.m_Elements[i].m_size;
		dx_vertex_declaration[i].Method = D3DDECLMETHOD_DEFAULT;
		dx_vertex_declaration[i].Usage = m_declaration.m_Elements[i].m_type;
		dx_vertex_declaration[i].UsageIndex = m_declaration.m_Elements[i].m_index;
	}

	dx_vertex_declaration[m_declaration.m_ElementCount].Stream = 0xFF;
	dx_vertex_declaration[m_declaration.m_ElementCount].Offset = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].Type = D3DDECLTYPE_UNUSED;
	dx_vertex_declaration[m_declaration.m_ElementCount].Method = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].Usage = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].UsageIndex = 0;
		
	Core::IDevice::Ref()->CreateVertexDeclaration(dx_vertex_declaration,&m_declarationRef);
	delete[] dx_vertex_declaration;
}

void CVertexBufferD3D::Enable()
{
	for(unsigned int i = 0; i < k_MAX_STREAM_COUNT; ++i)
	{
		if(m_addr[i] == NULL) 
			continue;
		Core::IDevice::Ref()->SetStreamSource( i, m_addr[i], 0, m_elementSize[i]);
	}
}

void CVertexBufferD3D::Disable()
{

}

void CVertexBufferD3D::EnableDeclaration()
{
	if(m_declarationRef == NULL) 
		return;
	Core::IDevice::Ref()->SetVertexDeclaration(m_declarationRef);
}