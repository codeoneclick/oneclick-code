#include "Resource.h"

const std::string CResource::TEXTURE_CONTROLLER = "TEXTURE_CONTROLLER";
const std::string CResource::MESH_CONTROLLER = "MESH_CONTROLLER";
const std::string CResource::SHADER_CONTROLLER = "SHADER_CONTROLLER";

std::map<std::string,Controller::IResourceController*> CResource::m_controllers;

DWORD __stdcall PreloadingThread(void* value)
{
	CResource::Update();
    return NULL;
}

HANDLE CResource::m_Thread = NULL;

Controller::CTextureController *CResource::GetTextureControllerInstance()
{	
	if(m_controllers[TEXTURE_CONTROLLER] == NULL)
	{
		m_controllers[TEXTURE_CONTROLLER] = new Controller::CTextureController();
	}
	return (Controller::CTextureController*)m_controllers[TEXTURE_CONTROLLER];
}

Controller::CMeshController *CResource::GetMeshControllerInstance()
{	
	if(m_controllers[MESH_CONTROLLER] == NULL)
	{
		m_controllers[MESH_CONTROLLER] = new Controller::CMeshController();
	}
	return (Controller::CMeshController*)m_controllers[MESH_CONTROLLER];
}

Controller::CShaderController *CResource::GetShaderControllerInstance()
{
	if(m_controllers[SHADER_CONTROLLER] == NULL)
	{
		m_controllers[SHADER_CONTROLLER] = new Controller::CShaderController();
	}
	return (Controller::CShaderController*)m_controllers[SHADER_CONTROLLER];
}

void CResource::Enable()
{
	m_Thread = CreateThread(NULL,NULL,PreloadingThread,NULL,NULL,NULL);
	SetThreadPriority(m_Thread,THREAD_PRIORITY_HIGHEST);
}

void CResource::Disable()
{

}

void CResource::Update()
{
	while(true)
	{
		Sleep(1);
		std::map<std::string,Controller::IResourceController*>::iterator beginIterator = m_controllers.begin();
		std::map<std::string,Controller::IResourceController*>::iterator endIterator = m_controllers.end();

		while(beginIterator != endIterator)
		{
			(*beginIterator).second->Update();
			beginIterator++;
		}
	}
}
