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
		std::map<std::string,Core::CMesh*> m_ResourceContainer;
		std::map<std::string,void*> m_DataContainer;
		std::vector<std::string> m_RequestList;
		Core::IVertexBuffer *m_Default_vb;
		Core::IIndexBuffer *m_Default_ib;
		
		CRITICAL_SECTION m_CriticalSection;
		std::string m_WorkingPath;

		void ReadData(std::string _value);
		void LoadDefault();
	public :
		CMeshController();
		~CMeshController();
		Core::CMesh* Load(std::string _value, Core::CMesh::MESH_EXTENSION _extension);
		void SetPath(std::string _workingPath) { m_WorkingPath = _workingPath; }
		void WorkInMainThread();
		void WorkInPreloadingThread();
	};
};

#endif