#ifndef _SHADERCONTROLLER_H_
#define _SHADERCONTROLLER_H_

#include "ShaderExtension.h"
#include "StructExt.h"
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include "Shader.h"

class CShaderController
{
	private :
		std::map<std::string,CShader::CGShader*> _shaderContainer;
		std::vector<std::string> _requestShader;
		
		HANDLE _thread;
		CRITICAL_SECTION shaderRequestCriticalSection;

		void _insertShader(std::string key);
	public :
		void _shaderLoadThread();
		CShader::CGShader* GetShader(std::string value);
		CShaderController();	
};

#endif