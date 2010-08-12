#ifndef _TEXTURECONTROLLER_H_
#define _TEXTURECONTROLLER_H_

#include <string>
#include <map>
#include <vector>
#include "DDS.h"

class CTextureController
{
	friend DWORD __stdcall TextureLoadThread(void* value);
	
	private :
		std::map<std::string,type::STexture*>       _container;
		std::map<std::string,void*> _data;
		std::vector<std::string>                    _requestList;
		unsigned int                                _default_addr_ptr;
		
		HANDLE                                      _thread;
		CRITICAL_SECTION                            _criticalSection;
		bool                                        _work;
		std::string                                 _path;
		
		void _ReadData(std::string value);
		void _LoadThread();
		void _LoadDefault();
	public :
		CTextureController();
		~CTextureController();
		type::STexture* Load(std::string value, type::STexture::EXTENSION extension);
		void SetPath(std::string path) { _path = path; }
		void Update();
};

#endif