#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "TextureController.h"
#include "MeshController.h"
#include "ShaderController.h"

class Resource
{
	friend DWORD __stdcall PreloadingThread(void* _value);
	private :
		static Controller::CTextureController *_textureControllerInstance;
		static Controller::CMeshController *_meshControllerInstance;
		static Controller::CShaderController *_shaderControllerInstance;

		static HANDLE m_thread;
	public :
		static Controller::CMeshController *GetMeshControllerInstance();
		static Controller::CTextureController *GetTextureControllerInstance();
		static Controller::CShaderController *GetShaderControllerInstance();

		static void Enable();
		static void Disable();

		static void WorkInMainTread();
		static void WorkInPreloadingTread();
};

#endif