#ifndef _MESHSERVICE_H_
#define _MESHSERVICE_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "Loader3DS.h"

DWORD __stdcall __meshLoadThread(LPVOID value);

namespace service
{
class MeshService
{
	private :
		std::map<std::string,type::VertexBufferData*> _meshDataContainer;
		std::vector<std::string> _requestMeshContainer;
		
		HANDLE _thread;
		CRITICAL_SECTION meshRequestCriticalSection;

		void _insertMeshData(std::string key);
		void _insertMesh(std::string key,type::VertexBufferData* value);
	public :
		type::VertexBufferData* GetMesh(std::string value);
		MeshService();
		void _meshLoadThread();
};
};
#endif