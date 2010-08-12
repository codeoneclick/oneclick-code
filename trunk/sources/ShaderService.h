#ifndef _SHADERSERVICE_H_
#define _SHADERSERVICE_H_

#include "ShaderExtension.h"
#include "StructExt.h"
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>

namespace service
{

class ShaderService
{
	private :
		std::map<std::string,type::CGShader*> _shaderContainer;
		std::vector<std::string> _requestShader;
		
		HANDLE _thread;
		CRITICAL_SECTION shaderRequestCriticalSection;

		void _insertShader(std::string key);
	public :
		void _shaderLoadThread();
		type::CGShader* GetShader(std::string value);
		ShaderService();	
};
};

#endif