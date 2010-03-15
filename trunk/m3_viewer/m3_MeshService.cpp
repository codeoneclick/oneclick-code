#include "m3_MeshService.h"


DWORD __stdcall meshLoadThread(LPVOID value)
{
	((m3_MeshService*)value)->_meshLoadThread();
	return 0;
}

m3_MeshService::m3_MeshService()
{
	InitializeCriticalSection( &meshRequestCriticalSection );
	_thread = CreateThread(NULL,NULL,meshLoadThread,this,NULL,NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_NORMAL);
}


void m3_MeshService::_insertMeshData(std::string key)
{
	std::map<std::string,m3_VertexBufferPtr*>::iterator meshDataIterator = _meshDataContainer.find(key);
	if(meshDataIterator == _meshDataContainer.end())
		_meshDataContainer.insert(std::pair<std::string,m3_VertexBufferPtr*>(key,NULL));
}


void m3_MeshService::_insertMesh(std::string key, m3_VertexBufferID *value)
{
	_meshContainer.insert(std::pair<std::string,m3_VertexBufferID*>(key,value));
	std::vector<std::string>::iterator _requestIterator = _requestMesh.begin();
	while(_requestIterator != _requestMesh.end())
	{
		if(key == (*_requestIterator))
		{
			EnterCriticalSection( &meshRequestCriticalSection );
			_requestMesh.erase(_requestIterator);
			LeaveCriticalSection( &meshRequestCriticalSection );
			return;
		}
		++_requestIterator;
	}
}

m3_VertexBufferID* m3_MeshService::GetMesh(std::string value)
{
	std::map<std::string,m3_VertexBufferID*>::iterator meshIterator = _meshContainer.find(value);
	if(meshIterator != _meshContainer.end())
		return meshIterator->second;
	else
	{
		std::vector<std::string>::iterator _requestIterator = _requestMesh.begin();
		while(_requestIterator != _requestMesh.end())
		{
			if(value == (*_requestIterator))
			{
				std::map<std::string,m3_VertexBufferPtr*>::iterator meshDataIterator = _meshDataContainer.find(value);
				if(meshDataIterator != _meshDataContainer.end())
				{
					//GLuint textureId =  m3_DDSLoader::Load(_textureDataContainer.find(value)->second);
					_insertMesh(value,NULL);
					_meshDataContainer.erase(meshDataIterator);
					return NULL;
				}
				else
					return NULL;
			}
			++_requestIterator;
		}
		EnterCriticalSection( &meshRequestCriticalSection );
		_requestMesh.push_back(value);	
		LeaveCriticalSection( &meshRequestCriticalSection );		

		return NULL;
	}
}

void m3_MeshService::_meshLoadThread()
{
	while(TRUE)
	{
		Sleep(1000);
		if(!_requestMesh.size())
			continue;
		EnterCriticalSection( &meshRequestCriticalSection );
		std::vector<std::string>::iterator _requestIterator = _requestMesh.begin();
		while(_requestIterator != _requestMesh.end())
		{
			_insertMeshData(*_requestIterator);
			++_requestIterator;
		}
		LeaveCriticalSection( &meshRequestCriticalSection );		
	}
}