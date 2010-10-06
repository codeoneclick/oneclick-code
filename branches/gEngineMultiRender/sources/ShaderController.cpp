#include "ShaderController.h"

using namespace Controller;

CShaderController::CShaderController()
{
	InitializeCriticalSection( &m_CriticalSection );
}

CShaderController::~CShaderController()
{

}

Core::CShader* CShaderController::Load(std::string _fileName)
{
	std::map<std::string,Core::CShader*>::iterator resourceIterator = m_ResourceContainer.find(_fileName);
	
	if(resourceIterator != m_ResourceContainer.end())
	{
		return resourceIterator->second;
	}
	else
	{
		m_ResourceContainer[_fileName] = new Core::CShader();
		EnterCriticalSection( &m_CriticalSection );
		m_RequestList.push_back(_fileName);	
		LeaveCriticalSection( &m_CriticalSection );	
		return m_ResourceContainer[_fileName];
	}
}

void CShaderController::WorkInPreloadingThread()
{
	if(!m_ResourceContainer.size()) return;
	EnterCriticalSection( &m_CriticalSection );
	std::vector<std::string>::iterator requestIterator = m_RequestList.begin();
	while(requestIterator != m_RequestList.end())
	{
		m_ResourceContainer[*requestIterator]->ReadData(*requestIterator);
		++requestIterator;
	}
	LeaveCriticalSection( &m_CriticalSection );		
}

void CShaderController::WorkInMainThread()
{
	std::vector<std::string>::iterator requestIterator = m_RequestList.begin();
	if(requestIterator != m_RequestList.end())
	{
		if(m_ResourceContainer[*requestIterator]->m_is_read_data)
		{
			m_ResourceContainer[*requestIterator]->Commit(*requestIterator);
			EnterCriticalSection( &m_CriticalSection );
			m_RequestList.erase(requestIterator);
			LeaveCriticalSection( &m_CriticalSection );
		}
	}
}