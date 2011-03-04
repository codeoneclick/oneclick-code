#ifndef _TEXTURECONTROLLER_H_
#define _TEXTURECONTROLLER_H_

#include "../../Core/ITexture.h"
#include "IResourceController.h"

namespace Controller
{
	class CTextureController : public IResourceController
	{
	private :
		std::map<std::string,Core::ITexture*> _m_resource_container;
	public :
		CTextureController();
		~CTextureController();
		Core::ITexture* Load(std::string _value, Core::ITexture::TEXTURE_EXTENSION  _ext);
		
		virtual void Update();
	};
};

#endif