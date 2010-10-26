#ifndef _SHADERCONTROLLER_H_
#define _SHADERCONTROLLER_H_

#include "ShaderExtension.h"
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include "Core/IShader.h"

namespace Controller
{
	class CShaderController
	{
	private :
		CRITICAL_SECTION m_CriticalSection;
		std::map<std::string,Core::IShader*> m_ResourceContainer;
		std::vector<std::string> m_RequestList;

	public :
		CShaderController();
		~CShaderController();
		Core::IShader* Load(std::string _fileName);
		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif