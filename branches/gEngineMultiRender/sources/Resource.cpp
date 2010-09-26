#include "Resource.h"

DWORD __stdcall PreloadingThread(void* value)
{
	Resource::WorkInPreloadingTread();
    return NULL;
}

HANDLE Resource::m_thread = NULL;

Controller::CTextureController *Resource::_textureControllerInstance = NULL;

Controller::CTextureController *Resource::GetTextureControllerInstance()
{	
	if(_textureControllerInstance == NULL)
	{
		_textureControllerInstance = new Controller::CTextureController();
	}
	return _textureControllerInstance;
}

CMeshController *Resource::_meshControllerInstance = NULL;

CMeshController *Resource::GetMeshControllerInstance()
{	
	if(_meshControllerInstance == NULL)
	{
		_meshControllerInstance = new CMeshController();
	}
	return _meshControllerInstance;
}

Controller::CShaderController *Resource::_shaderControllerInstance = NULL;

Controller::CShaderController *Resource::GetShaderControllerInstance()
{
	if(_shaderControllerInstance == NULL)
	{
		_shaderControllerInstance = new Controller::CShaderController();
	}
	return _shaderControllerInstance;
}

void Resource::Enable()
{
	m_thread = CreateThread(NULL,NULL,PreloadingThread,NULL,NULL,NULL);
	SetThreadPriority(m_thread,THREAD_PRIORITY_LOWEST);
}

void Resource::Disable()
{

}

void Resource::WorkInPreloadingTread()
{
	while(true)
	{
		Sleep(1000);
		
		if(_textureControllerInstance != NULL) 
			_textureControllerInstance->WorkInPreloadingThread();
		if(_shaderControllerInstance != NULL)
			_shaderControllerInstance->WorkInPreloadingThread();
	}
}

void Resource::WorkInMainTread()
{
		if(_textureControllerInstance != NULL) 
			_textureControllerInstance->WorkInMainThread();
		if(_shaderControllerInstance != NULL)
			_shaderControllerInstance->WorkInMainThread();
}
