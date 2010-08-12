#include "TextureService.h"

using namespace service;

DWORD __stdcall textureLoadThread(LPVOID value)
{
	((TextureService*)value)->_textureLoadThread();
	return 0;
}

TextureService::TextureService()
{
	InitializeCriticalSection( &textureRequestCriticalSection );
	_thread = CreateThread(NULL,NULL,textureLoadThread,this,NULL,NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_LOWEST);
}

void TextureService::_insertTextureData(std::string key)
{
	std::map<std::string,type::DDSImageData*>::iterator textureDataIterator = _textureDataContainer.find(key);
	if(textureDataIterator == _textureDataContainer.end())
		_textureDataContainer.insert(std::pair<std::string,type::DDSImageData*>(key,loader::LoaderDDS::LoadImageData(key)));
}

void TextureService::_insertTexture(std::string key, GLuint value)
{
	_textureContainer.insert(std::pair<std::string,GLuint>(key,value));
	std::vector<std::string>::iterator _requestIterator = _requestTexture.begin();
	while(_requestIterator != _requestTexture.end())
	{
		if(key == (*_requestIterator))
		{
			EnterCriticalSection( &textureRequestCriticalSection );
			_requestTexture.erase(_requestIterator);
			LeaveCriticalSection( &textureRequestCriticalSection );
			return;
		}
		++_requestIterator;
	}
}

GLint TextureService::GetTexture(std::string value)
{
	std::map<std::string,GLuint>::iterator textureIterator = _textureContainer.find(value);
	if(textureIterator != _textureContainer.end())
		return textureIterator->second;
	else
	{
		std::vector<std::string>::iterator _requestIterator = _requestTexture.begin();
		while(_requestIterator != _requestTexture.end())
		{
			if(value == (*_requestIterator))
			{
				std::map<std::string,type::DDSImageData*>::iterator textureDataIterator = _textureDataContainer.find(value);
				if(textureDataIterator != _textureDataContainer.end())
				{
					GLuint textureId =  loader::LoaderDDS::Load(_textureDataContainer.find(value)->second);
					_insertTexture(value,textureId);
					_textureDataContainer.erase(textureDataIterator);
					return textureId;
				}
				else
					return 0;
			}
			++_requestIterator;
		}
		EnterCriticalSection( &textureRequestCriticalSection );
		_requestTexture.push_back(value);	
		LeaveCriticalSection( &textureRequestCriticalSection );		

		return 0;
	}
}

void TextureService::_textureLoadThread()
{
	while(TRUE)
	{
		Sleep(1000);
		if(!_requestTexture.size())
			continue;
		EnterCriticalSection( &textureRequestCriticalSection );
		std::vector<std::string>::iterator _requestIterator = _requestTexture.begin();
		while(_requestIterator != _requestTexture.end())
		{
			_insertTextureData(*_requestIterator);
			++_requestIterator;
		}
		LeaveCriticalSection( &textureRequestCriticalSection );		
	}
}