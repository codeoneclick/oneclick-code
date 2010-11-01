#include "Mesh.h"
#include "Render.h"

using namespace Core;

CMesh::CMesh()
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
	m_Shader = NULL;

	for(unsigned int i = 0; i < 8; ++i)
		m_TextureArray[i] = NULL;
}

void CMesh::Draw()
{
	m_Shader->Enable();
	m_VertexBuffer->Enable();
	m_IndexBuffer->Enable();
	Core::CGlobal::GetRender()->Draw(m_VertexBuffer->GetVertexCount(),m_IndexBuffer->GetIndexCount(),m_IndexBuffer->GetPrimitiveCount());
	m_VertexBuffer->Disable();
	m_IndexBuffer->Disable();
	m_Shader->Disable();
}