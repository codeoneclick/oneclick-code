#ifndef _TEXTURECONTROLLER_H_
#define _TEXTURECONTROLLER_H_

#include "../../Core/ITexture.h"
#include "IResourceController.h"
#include <list>
#include "../../Math/Vector3d.h"

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
		void createNullPtr(math::Vector3d *&_ptr);
		virtual void Update();
	};
};

#endif