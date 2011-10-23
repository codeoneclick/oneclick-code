#ifndef _TEXTURESERVICE_H_
#define _TEXTURESERVICE_H_

#include <string>
#include <map>
#include <vector>

#include "LoaderDDS.h"

DWORD __stdcall textureLoadThread(LPVOID value);

class TextureService
{
	private :
		std::map<std::string,GLuint> _textureContainer;
		std::map<std::string,DDS_IMAGE_DATA*> _textureDataContainer;
		std::vector<std::string> _requestTexture;
		
		HANDLE _thread;
		CRITICAL_SECTION textureRequestCriticalSection;

		void _insertTextureData(std::string key);
		void _insertTexture(std::string key, GLuint value);
	public :
		GLint GetTexture(std::string value);
		TextureService();
		void _textureLoadThread();
};

#endif