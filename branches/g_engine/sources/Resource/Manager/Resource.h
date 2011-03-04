#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "../Controller/TextureController.h"
#include "../Controller/MeshController.h"
#include "../Controller/ShaderController.h"

class CResource
{
	friend DWORD __stdcall PreloadingThread(void* _value);

	private :
		static const std::string TEXTURE_CONTROLLER;
		static const std::string MESH_CONTROLLER;
		static const std::string SHADER_CONTROLLER;

	private :
		static std::map<std::string,Controller::IResourceController*> m_controllers;

		static HANDLE m_Thread;
	public :
		static Controller::CMeshController *GetMeshControllerInstance();
		static Controller::CTextureController *GetTextureControllerInstance();
		static Controller::CShaderController *GetShaderControllerInstance();

		static void Enable();
		static void Disable();

		static void Update();
};

#endif