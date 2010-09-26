#include "TextureController.h"

using namespace Controller;

CTextureController::CTextureController()
{
	InitializeCriticalSection( &_m_critical_section );
}

CTextureController::~CTextureController()
{

}

Core::CTexture* CTextureController::Load(std::string _value, Core::CTexture::TEXTURE_EXTENSION  _ext)
{
	std::map<std::string,Core::CTexture*>::iterator resource_iterator = _m_resource_container.find(_value);
	
	if(resource_iterator != _m_resource_container.end())
	{
		return resource_iterator->second;
	}
	else
	{
		_m_resource_container[_value] = new Core::CTexture();
		_m_resource_container[_value]->m_extension = _ext;
		EnterCriticalSection( &_m_critical_section );
		_m_request_container.push_back(_value);	
		LeaveCriticalSection( &_m_critical_section );	
		return _m_resource_container[_value];
	}
}

void CTextureController::WorkInPreloadingThread()
{
	if(!_m_request_container.size()) return;
	EnterCriticalSection( &_m_critical_section );
	std::vector<std::string>::iterator request_iterator = _m_request_container.begin();
	while(request_iterator != _m_request_container.end())
	{
		_m_resource_container[*request_iterator]->ReadData(*request_iterator);
		++request_iterator;
	}
	LeaveCriticalSection( &_m_critical_section );		
}

void CTextureController::WorkInMainThread()
{
	std::vector<std::string>::iterator request_iterator = _m_request_container.begin();
	if(request_iterator != _m_request_container.end())
	{
		if(_m_resource_container[*request_iterator]->m_is_read_data)
		{
			_m_resource_container[*request_iterator]->Commit(*request_iterator);
			EnterCriticalSection( &_m_critical_section );
			_m_request_container.erase(request_iterator);
			LeaveCriticalSection( &_m_critical_section );
		}
	}
}