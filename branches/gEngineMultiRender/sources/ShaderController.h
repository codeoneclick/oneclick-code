#ifndef _SHADERCONTROLLER_H_
#define _SHADERCONTROLLER_H_

#include "ShaderExtension.h"
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include "Shader.h"

namespace Controller
{
	class CShaderController
	{
	private :
		CRITICAL_SECTION _m_critical_section;

		std::map<std::string,Core::CShader*> _m_resource_container;
		std::vector<std::string> _m_request_container;

	public :
		CShaderController();
		~CShaderController();
		Core::CShader* Load(std::string _value);
		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif