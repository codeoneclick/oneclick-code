#include "ShaderController.h"
#include "../../Core/CGlobal.h"

using namespace Controller;

CShaderController::CShaderController()
{
	InitializeCriticalSection( &m_criticalSection );
}

CShaderController::~CShaderController()
{

}

Core::IShader* CShaderController::Load(std::string _fileName)
{
	std::map<std::string,Core::IShader*>::iterator resourceIterator = m_ResourceContainer.find(_fileName);
	
	if(resourceIterator != m_ResourceContainer.end())
	{
		return resourceIterator->second;
	}
	else
	{
		m_ResourceContainer[_fileName] = Core::CGlobal::GetDevice()->CreateShader();
		EnterCriticalSection( &m_criticalSection );
		m_requestList.push_back(_fileName);	
		LeaveCriticalSection( &m_criticalSection );	
		return m_ResourceContainer[_fileName];
	}
}

void CShaderController::Update()
{
	if(!m_ResourceContainer.size()) return;
	EnterCriticalSection( &m_criticalSection );
	std::vector<std::string>::iterator requestIterator = m_requestList.begin();
	while(requestIterator != m_requestList.end())
	{
		m_ResourceContainer[*requestIterator]->ReadData(*requestIterator);
		++requestIterator;
	}
	LeaveCriticalSection( &m_criticalSection );	

	requestIterator = m_requestList.begin();
	if(requestIterator != m_requestList.end())
	{
		if(m_ResourceContainer[*requestIterator]->m_is_read_data)
		{
			m_ResourceContainer[*requestIterator]->Commit(*requestIterator);
			EnterCriticalSection( &m_criticalSection );
			m_requestList.erase(requestIterator);
			LeaveCriticalSection( &m_criticalSection );
		}
	}
}
