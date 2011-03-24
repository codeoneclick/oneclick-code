#ifndef _IRESOURCECONTROLLER_H_
#define _IRESOURCECONTROLLER_H_

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

namespace Controller
{
	class IResourceController
	{
	protected :
		std::vector<std::string> m_requestList;
		CRITICAL_SECTION m_criticalSection;
	public :
		virtual void Update() = 0;
	};
};

#endif