#include "MeshController.h"

DWORD __stdcall MeshLoadThread(LPVOID value)
{
  ((CMeshController*)value)->_LoadThread();
	return 0;
}

CMeshController::CMeshController()
{
	_path = "Content\\models\\";
	InitializeCriticalSection( &_criticalSection );
	_thread = CreateThread(NULL,NULL,MeshLoadThread,this,NULL,NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_LOWEST);
	_LoadDefault();
	_work = true;
}

CMeshController::~CMeshController()
{
	_work = false;
}

void CMeshController::_LoadDefault()
{
	_default_vb = new CVertexBuffer();
	_default_ib = new CIndexBuffer();
}

void CMeshController::_ReadData(std::string value)
{
	std::map<std::string,void*>::iterator dataIterator = _data.find(value);
	if(dataIterator == _data.end())
		switch(_container[value]->extension)
		{
			case type::SMesh::_3DS :
			{
				_data[value] = Loader::C3DS::ReadData(value);
			}
			break;
			case type::SMesh::_M2 :
			{

			}
			break;
			case type::SMesh::_M3 :
			{

			}
			break;
		}
		
}

type::SMesh* CMeshController::Load(std::string value, type::SMesh::EXTENSION extension)
{
	std::map<std::string,type::SMesh*>::iterator meshIterator = _container.find(value);
	if(meshIterator != _container.end())
			return meshIterator->second;
	else
	{
		_container[value] = new type::SMesh();
		_container[value]->vertexBuffer = _default_vb;
		_container[value]->indexBuffer = _default_ib;
		_container[value]->extension = extension;
		EnterCriticalSection( &_criticalSection );
		_requestList.push_back(value);	
		LeaveCriticalSection( &_criticalSection );	
		return _container[value];
	}
}

void CMeshController::Update()
{
	std::vector<std::string>::iterator _requestIterator = _requestList.begin();
	if(_requestIterator != _requestList.end())
	{
		std::map<std::string,void*>::iterator dataIterator = _data.find((*_requestIterator));
		if(dataIterator != _data.end())
		{
			switch(_container[(*_requestIterator)]->extension)
			{
				case type::SMesh::_3DS :
				{
					Loader::C3DS::Commit((Loader::C3DS::S3DSFile*)dataIterator->second,_container[(*_requestIterator)]);
					_data.erase(dataIterator);
				}
				break;
				case type::SMesh::_M2 :
				{

				}
				break;
			}
			EnterCriticalSection( &_criticalSection );
			_requestList.erase(_requestIterator);
			LeaveCriticalSection( &_criticalSection );
		}
	}
}

void CMeshController::_LoadThread()
{
	while(_work)
	{
		Sleep(1000);
		if(!_requestList.size())
			continue;
		EnterCriticalSection( &_criticalSection );
		std::vector<std::string>::iterator _requestIterator = _requestList.begin();
		while(_requestIterator != _requestList.end())
		{
			_ReadData(*_requestIterator);
			++_requestIterator;
		}
		LeaveCriticalSection( &_criticalSection );		
	}
}
