#ifndef _MESHCONTROLLER_H_
#define _MESHCONTROLLER_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "3DS.h"

class CMeshController
{
	friend DWORD __stdcall MeshLoadThread(void* value);
	private :
		std::map<std::string,type::SMesh*> _container;
		std::map<std::string,void*> _data;
		std::vector<std::string> _requestList;
		CVertexBuffer *_default_vb;
		CIndexBuffer *_default_ib;
		
		HANDLE _thread;
		CRITICAL_SECTION _criticalSection;
		bool _work;
		std::string _path;

		void _ReadData(std::string key);
		void _LoadThread();
		void _LoadDefault();
	public :
		CMeshController();
		~CMeshController();
		type::SMesh* Load(std::string value, type::SMesh::EXTENSION extension);
		void SetPath(std::string path) { _path = path; }
		void Update();
};

#endif