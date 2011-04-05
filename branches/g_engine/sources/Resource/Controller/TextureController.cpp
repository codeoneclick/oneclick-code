#include "TextureController.h"
#include "../../Core/CGlobal.h"


using namespace Controller;

CTextureController::CTextureController()
{
	InitializeCriticalSection( &m_criticalSection );
	math::Vector3d *p = NULL;
	p = new math::Vector3d();
	createNullPtr(p);
}

CTextureController::~CTextureController()
{

}

Core::ITexture* CTextureController::Load(std::string _value, Core::ITexture::TEXTURE_EXTENSION  _ext)
{
	std::map<std::string,Core::ITexture*>::iterator resource_iterator = _m_resource_container.find(_value);
	

	if(resource_iterator != _m_resource_container.end())
	{
		return resource_iterator->second;
	}
	else
	{
		if(_ext == Core::ITexture::DDS_CUBE_EXT)
			_m_resource_container[_value] = Core::CGlobal::GetDevice()->CreateTextureCube();
		else
			_m_resource_container[_value] = Core::CGlobal::GetDevice()->CreateTexture();
		_m_resource_container[_value]->m_extension = _ext;
		EnterCriticalSection( &m_criticalSection );
		m_requestList.push_back(_value);	
		LeaveCriticalSection( &m_criticalSection );	
		return _m_resource_container[_value];
	}
}

void CTextureController::createNullPtr(math::Vector3d *&_ptr)
{
	if(_ptr != NULL)
	{
		delete _ptr;
		_ptr = NULL;
	}
}

void CTextureController::Update()
{
	if(!m_requestList.size()) return;
	EnterCriticalSection( &m_criticalSection );
	std::vector<std::string>::iterator request_iterator = m_requestList.begin();
	while(request_iterator != m_requestList.end())
	{
		_m_resource_container[*request_iterator]->ReadFromFile(*request_iterator);
		++request_iterator;
	}
	LeaveCriticalSection( &m_criticalSection );	

	request_iterator = m_requestList.begin();
	if(request_iterator != m_requestList.end())
	{
		if(_m_resource_container[*request_iterator]->m_is_read_data)
		{
			_m_resource_container[*request_iterator]->CommitToVRAM();
			EnterCriticalSection( &m_criticalSection );
			m_requestList.erase(request_iterator);
			LeaveCriticalSection( &m_criticalSection );
		}
	}
}
