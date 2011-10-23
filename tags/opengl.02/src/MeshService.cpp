#include "MeshService.h"


DWORD __stdcall __meshLoadThread(LPVOID value)
{
	((MeshService*)value)->_meshLoadThread();
	return 0;
}

MeshService::MeshService()
{
	InitializeCriticalSection( &meshRequestCriticalSection );
	_thread = CreateThread(NULL,NULL,__meshLoadThread,this,NULL,NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_NORMAL);
}

void MeshService::_insertMeshData(std::string key)
{
	std::map<std::string,VertexBufferPtr*>::iterator meshDataIterator = _meshDataContainer.find(key);
	if(meshDataIterator == _meshDataContainer.end())
		_meshDataContainer.insert(std::pair<std::string,VertexBufferPtr*>(key,Loader3DS::LoadFileData(key)));
}

void MeshService::_insertMesh(std::string key,VertexBufferPtr* value)
{
	Loader3DS::WriteInVideoMemory(value);

	std::vector<std::string>::iterator _requestIterator = _requestMeshContainer.begin();
	while(_requestIterator != _requestMeshContainer.end())
	{
		if(key == (*_requestIterator))
		{
			EnterCriticalSection( &meshRequestCriticalSection );
			_requestMeshContainer.erase(_requestIterator);
			LeaveCriticalSection( &meshRequestCriticalSection );
			return;
		}
		++_requestIterator;
	}
}

VertexBufferPtr* MeshService::GetMesh(std::string value)
{
	std::map<std::string,VertexBufferPtr*>::iterator meshIterator = _meshDataContainer.find(value);
	if(meshIterator != _meshDataContainer.end())
		if((*meshIterator).second->vertexBufferId != 0)
			return meshIterator->second;

	std::vector<std::string>::iterator _requestIterator = _requestMeshContainer.begin();
	while(_requestIterator != _requestMeshContainer.end())
	{
		if(value == (*_requestIterator))
		{
			std::map<std::string,VertexBufferPtr*>::iterator meshDataIterator = _meshDataContainer.find(value);
			if(meshDataIterator != _meshDataContainer.end())
			{
				_insertMesh(value,(*meshDataIterator).second);
				return _meshDataContainer[value];
			}
			else
				return NULL;
		}
		else
			return NULL;
							
		++_requestIterator;
	}
	EnterCriticalSection( &meshRequestCriticalSection );
	_requestMeshContainer.push_back(value);	
	LeaveCriticalSection( &meshRequestCriticalSection );		

	return NULL;
}

void MeshService::_meshLoadThread()
{
	while(TRUE)
	{
		Sleep(1);
		if(!_requestMeshContainer.size())
			continue;
		EnterCriticalSection( &meshRequestCriticalSection );
		std::vector<std::string>::iterator _requestIterator = _requestMeshContainer.begin();
		while(_requestIterator != _requestMeshContainer.end())
		{
			_insertMeshData(*_requestIterator);
			++_requestIterator;
		}
		LeaveCriticalSection( &meshRequestCriticalSection );		
	}
}

