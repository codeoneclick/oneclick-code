#include "CVertexBufferD3D.h"
#include "IDevice.h"

using namespace Core;

CVertexBufferD3D::CVertexBufferD3D()
{
	m_addr = NULL;
}

CVertexBufferD3D::~CVertexBufferD3D()
{

}

void* CVertexBufferD3D::Load(unsigned int _vertex_count, unsigned int _element_size)
{
	m_element_size = _element_size;
	m_vertex_count = _vertex_count;

	Core::IDevice::Ref()->CreateVertexBuffer(m_vertex_count * m_element_size,D3DUSAGE_WRITEONLY,NULL,D3DPOOL_DEFAULT,&m_addr,NULL);
	m_addr->Lock(0,m_vertex_count * m_element_size, (void**)&m_data,D3DLOCK_NOSYSLOCK);
	
	return m_data;
}

void CVertexBufferD3D::CommitToVRAM()
{
	m_addr->Unlock();
}

void* CVertexBufferD3D::Lock()
{
	m_addr->Lock(0,m_vertex_count * m_element_size, (void**)&m_data,D3DLOCK_NOSYSLOCK);
	return m_data;
}

void CVertexBufferD3D::Unlock()
{
	m_addr->Unlock();
}

void CVertexBufferD3D::SetDeclaration(Core::IVertexBuffer::SVertexDeclaration &_declaration)
{
	m_declaration = _declaration;
	D3DVERTEXELEMENT9 *dx_vertex_declaration = new D3DVERTEXELEMENT9[m_declaration.m_ElementCount + 1];
	for( unsigned int i = 0; i < m_declaration.m_ElementCount; ++i)
	{
		dx_vertex_declaration[i].Stream = 0;
		dx_vertex_declaration[i].Offset = m_declaration.m_Elements[i].m_Offset;
		dx_vertex_declaration[i].Type = m_declaration.m_Elements[i].m_Size;
		dx_vertex_declaration[i].Method = D3DDECLMETHOD_DEFAULT;
		dx_vertex_declaration[i].Usage = m_declaration.m_Elements[i].m_Type;
		dx_vertex_declaration[i].UsageIndex = m_declaration.m_Elements[i].m_Index;
	}

	dx_vertex_declaration[m_declaration.m_ElementCount].Stream = 0xFF;
	dx_vertex_declaration[m_declaration.m_ElementCount].Offset = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].Type = D3DDECLTYPE_UNUSED;
	dx_vertex_declaration[m_declaration.m_ElementCount].Method = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].Usage = 0;
	dx_vertex_declaration[m_declaration.m_ElementCount].UsageIndex = 0;
		
	Core::IDevice::Ref()->CreateVertexDeclaration(dx_vertex_declaration,&m_declaration_ref);
	delete[] dx_vertex_declaration;
}

void CVertexBufferD3D::Enable()
{
	if(m_addr == NULL) return;
	Core::IDevice::Ref()->SetVertexDeclaration(m_declaration_ref);
	Core::IDevice::Ref()->SetStreamSource( 0,m_addr, 0, m_element_size);
}

void CVertexBufferD3D::Disable()
{

}