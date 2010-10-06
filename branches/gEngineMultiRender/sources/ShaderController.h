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
		CRITICAL_SECTION m_CriticalSection;
		std::map<std::string,Core::CShader*> m_ResourceContainer;
		std::vector<std::string> m_RequestList;

	public :
		CShaderController();
		~CShaderController();
		Core::CShader* Load(std::string _fileName);
		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif