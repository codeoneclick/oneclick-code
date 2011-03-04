#include "Resource.h"

DWORD __stdcall PreloadingThread(void* value)
{
	CResource::WorkInPreloadingTread();
    return NULL;
}

HANDLE CResource::m_Thread = NULL;

Controller::CTextureController *CResource::m_TextureController = NULL;

Controller::CTextureController *CResource::GetTextureControllerInstance()
{	
	if(m_TextureController == NULL)
	{
		m_TextureController = new Controller::CTextureController();
	}
	return m_TextureController;
}

Controller::CMeshController *CResource::m_MeshController = NULL;

Controller::CMeshController *CResource::GetMeshControllerInstance()
{	
	if(m_MeshController == NULL)
	{
		m_MeshController = new Controller::CMeshController();
	}
	return m_MeshController;
}

Controller::CShaderController *CResource::m_ShaderController = NULL;

Controller::CShaderController *CResource::GetShaderControllerInstance()
{
	if(m_ShaderController == NULL)
	{
		m_ShaderController = new Controller::CShaderController();
	}
	return m_ShaderController;
}

void CResource::Enable()
{
	m_Thread = CreateThread(NULL,NULL,PreloadingThread,NULL,NULL,NULL);
	SetThreadPriority(m_Thread,THREAD_PRIORITY_LOWEST);
}

void CResource::Disable()
{

}

void CResource::WorkInPreloadingTread()
{
	while(true)
	{
		Sleep(1000);
		if(m_TextureController != NULL) 
			m_TextureController->WorkInPreloadingThread();
		if(m_ShaderController != NULL)
			m_ShaderController->Update();
		if(m_MeshController != NULL)
			m_MeshController->Update();

		if(m_TextureController != NULL) 
			m_TextureController->WorkInMainThread();
	}
}

void CResource::WorkInMainTread()
{
		
}
