#ifndef _MESHCONTROLLER_H_
#define _MESHCONTROLLER_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "3DS.h"

namespace Controller
{
	class CMeshController
	{
	private :
		std::map<std::string,type::SMesh*> m_ResourceContainer;
		std::map<std::string,void*> m_DataContainer;
		std::vector<std::string> m_RequestList;
		CVertexBuffer *m_Default_vb;
		CIndexBuffer *m_Default_ib;
		
		CRITICAL_SECTION m_CriticalSection;
		std::string m_WorkingPath;

		void ReadData(std::string _value);
		void LoadDefault();
	public :
		CMeshController();
		~CMeshController();
		type::SMesh* Load(std::string _value, type::SMesh::EXTENSION _extension);
		void SetPath(std::string _workingPath) { m_WorkingPath = _workingPath; }
		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif