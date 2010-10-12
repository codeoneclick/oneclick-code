#include "MeshController.h"

using namespace Controller;

CMeshController::CMeshController()
{
	m_WorkingPath = "Content\\models\\";
	InitializeCriticalSection( &m_CriticalSection );
	LoadDefault();
}

CMeshController::~CMeshController()
{

}

void CMeshController::LoadDefault()
{
	m_Default_vb = new CVertexBuffer();
	m_Default_ib = new CIndexBuffer();
}

void CMeshController::ReadData(std::string _value)
{
	std::map<std::string,void*>::iterator dataIterator = m_DataContainer.find(_value);
	if(dataIterator == m_DataContainer.end())
		switch(m_ResourceContainer[_value]->m_Extension)
		{
			case Core::CMesh::EXT_3DS :
			{
				m_DataContainer[_value] = Loader::C3DS::ReadData(_value);
			}
			break;
		}
		
}

Core::CMesh* CMeshController::Load(std::string _value, Core::CMesh::MESH_EXTENSION _extension)
{
	std::map<std::string,Core::CMesh*>::iterator meshIterator = m_ResourceContainer.find(_value);
	if(meshIterator != m_ResourceContainer.end())
			return meshIterator->second;
	else
	{
		m_ResourceContainer[_value] = new Core::CMesh();
		m_ResourceContainer[_value]->m_VertexBuffer = m_Default_vb;
		m_ResourceContainer[_value]->m_IndexBuffer = m_Default_ib;
		m_ResourceContainer[_value]->m_Extension = _extension;
		EnterCriticalSection( &m_CriticalSection );
		m_RequestList.push_back(_value);	
		LeaveCriticalSection( &m_CriticalSection );	
		return m_ResourceContainer[_value];
	}
}

void CMeshController::WorkInMainThread()
{
	std::vector<std::string>::iterator requestIterator = m_RequestList.begin();
	if(requestIterator != m_RequestList.end())
	{
		std::map<std::string,void*>::iterator dataIterator = m_DataContainer.find((*requestIterator));
		if(dataIterator != m_DataContainer.end())
		{
			switch(m_ResourceContainer[(*requestIterator)]->m_Extension)
			{
				case Core::CMesh::EXT_3DS :
				{
					Loader::C3DS::Commit((Loader::C3DS::S3DSFile*)dataIterator->second,m_ResourceContainer[(*requestIterator)]);
					m_DataContainer.erase(dataIterator);
				}
				break;
			}
			EnterCriticalSection( &m_CriticalSection );
			m_RequestList.erase(requestIterator);
			LeaveCriticalSection( &m_CriticalSection );
		}
	}
}

void CMeshController::WorkInPreloadingThread()
{
	if(!m_RequestList.size()) return;

	EnterCriticalSection( &m_CriticalSection );
	std::vector<std::string>::iterator requestIterator = m_RequestList.begin();
	while(requestIterator != m_RequestList.end())
	{
		ReadData(*requestIterator);
		++requestIterator;
	}
	LeaveCriticalSection( &m_CriticalSection );		
}
