#include "TextureController.h"

DWORD __stdcall TextureLoadThread(void* value)
{
	((CTextureController*)value)->_LoadThread();
	return 0;
}

CTextureController::CTextureController()
{
	_path = "Content\\textures\\";
	InitializeCriticalSection( &_criticalSection );
	_thread = CreateThread(NULL, NULL, TextureLoadThread, this, NULL, NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_LOWEST);
	_LoadDefault();
	_work = true;
}

CTextureController::~CTextureController()
{
	_work = false;
}

void CTextureController::_LoadDefault()
{
	Loader::CDDS::SDDSFile *default_data = Loader::CDDS::ReadData(_path + "grass_nh.dds");
	_default_addr_ptr = Loader::CDDS::Commit(default_data);
}

void CTextureController::_ReadData(std::string value)
{
	std::map<std::string,void*>::iterator dataIterator = _data.find(value);
	if(dataIterator == _data.end())
		switch(_container[value]->extension)
		{
			case type::STexture::_DDS :
			{
				_data[value] = Loader::CDDS::ReadData(value);		
			}
			break;
			case type::STexture::_PNG :
			{

			}
			break;
		}
}

type::STexture* CTextureController::Load(std::string value, type::STexture::EXTENSION extension)
{
	std::map<std::string,type::STexture*>::iterator textureIterator = _container.find(value);
	if(textureIterator != _container.end())
			return textureIterator->second;
	else
	{
		_container[value] = new type::STexture();
		_container[value]->addr_ptr = _default_addr_ptr;
		_container[value]->extension = extension;
		_container[value]->name = value;
		EnterCriticalSection( &_criticalSection );
		_requestList.push_back(value);	
		LeaveCriticalSection( &_criticalSection );	
		return _container[value];
	}
}

void CTextureController::Update()
{
	std::vector<std::string>::iterator _requestIterator = _requestList.begin();
	if(_requestIterator != _requestList.end())
	{
		std::map<std::string,void*>::iterator dataIterator = _data.find((*_requestIterator));
		if(dataIterator != _data.end())
		{
			switch(_container[(*_requestIterator)]->extension)
			{
				case type::STexture::_DDS :
				{
					_container[(*_requestIterator)]->addr_ptr = Loader::CDDS::Commit((Loader::CDDS::SDDSFile*)dataIterator->second);
					_data.erase(dataIterator);
				}
				break;
				case type::STexture::_PNG :
				{

				}
				break;
			}
			EnterCriticalSection( &_criticalSection );
			_requestList.erase(_requestIterator);
			LeaveCriticalSection( &_criticalSection );
		}
	}
}

void CTextureController::_LoadThread()
{
	while(_work)
	{
		Sleep(1000);
		if(!_requestList.size())
			continue;
		EnterCriticalSection( &_criticalSection );
		std::vector<std::string>::iterator _requestIterator = _requestList.begin();
		while(_requestIterator != _requestList.end())
		{
			_ReadData(*_requestIterator);
			++_requestIterator;
		}
		LeaveCriticalSection( &_criticalSection );		
	}
}