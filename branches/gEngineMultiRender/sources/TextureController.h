#ifndef _TEXTURECONTROLLER_H_
#define _TEXTURECONTROLLER_H_

#include <string>
#include <map>
#include <vector>
#include "DDS.h"
#include "Texture.h"


namespace Controller
{
	class CTextureController
	{
	private :
		CRITICAL_SECTION _m_critical_section;

		std::map<std::string,Core::CTexture*> _m_resource_container;
		std::vector<std::string> _m_request_container;
	public :
		CTextureController();
		~CTextureController();
		Core::CTexture* Load(std::string _value, Core::CTexture::TEXTURE_EXTENSION  _ext);

		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif