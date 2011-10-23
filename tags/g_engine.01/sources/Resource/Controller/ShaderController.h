#ifndef _SHADERCONTROLLER_H_
#define _SHADERCONTROLLER_H_

#include "IResourceController.h"
#include "../../Core/IShader.h"

namespace Controller
{
	class CShaderController : public IResourceController
	{
	private :
		std::map<std::string,Core::IShader*> m_ResourceContainer;

	public :
		CShaderController();
		~CShaderController();
		Core::IShader* Load(std::string _fileName);
		virtual void Update();
	};
};

#endif