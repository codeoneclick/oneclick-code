#include "MeshController.h"

using namespace Controller;

CMeshController::CMeshController()
{
	m_workingPath = "Content\\models\\";
	InitializeCriticalSection( &m_criticalSection );
	LoadDefault();
}

CMeshController::~CMeshController()
{

}

void CMeshController::LoadDefault()
{
	m_Default_vb = Core::CGlobal::GetDevice()->CreateVertexBuffer();
	m_Default_ib = Core::CGlobal::GetDevice()->CreateIndexBuffer();
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
		EnterCriticalSection( &m_criticalSection );
		m_requestList.push_back(_value);	
		LeaveCriticalSection( &m_criticalSection );	
		return m_ResourceContainer[_value];
	}
}

void CMeshController::Update()
{
	if(!m_requestList.size()) return;

	EnterCriticalSection( &m_criticalSection );
	std::vector<std::string>::iterator requestIterator = m_requestList.begin();
	while(requestIterator != m_requestList.end())
	{
		ReadData(*requestIterator);
		++requestIterator;
	}
	LeaveCriticalSection( &m_criticalSection );		

	requestIterator = m_requestList.begin();
	if(requestIterator != m_requestList.end())
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
			EnterCriticalSection( &m_criticalSection );
			m_requestList.erase(requestIterator);
			LeaveCriticalSection( &m_criticalSection );
		}
	}
}
