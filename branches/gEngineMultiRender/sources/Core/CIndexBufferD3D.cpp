#include "CIndexBufferD3D.h"
#include "IDevice.h"

using namespace Core;

CIndexBufferD3D::CIndexBufferD3D()
{
	m_addr = NULL;
}

CIndexBufferD3D::~CIndexBufferD3D()
{

}

unsigned int* CIndexBufferD3D::Load(unsigned int _index_count)
{
	m_index_count = _index_count;
	Core::IDevice::GetDeviceRef()->CreateIndexBuffer( m_index_count * sizeof(unsigned int),D3DUSAGE_WRITEONLY,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&m_addr,NULL);
	m_addr->Lock(0, m_index_count * sizeof(unsigned int), (void**)&m_data, D3DLOCK_NOSYSLOCK);
	return m_data;
}

void CIndexBufferD3D::CommitToVRAM()
{
	 m_addr->Unlock();
}

unsigned int* CIndexBufferD3D::Lock()
{
	m_addr->Lock(0, m_index_count * sizeof(unsigned int), (void**)&m_data, D3DLOCK_NOSYSLOCK);
	return m_data;
}

void CIndexBufferD3D::Unlock()
{
	 m_addr->Unlock();
}

void CIndexBufferD3D::Enable()
{
	Core::IDevice::GetDeviceRef()->SetIndices(m_addr);
}

void CIndexBufferD3D::Disable()
{

}