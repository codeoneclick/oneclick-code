#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "TextureController.h"
#include "MeshController.h"
#include "ShaderController.h"

class CResource
{
	friend DWORD __stdcall PreloadingThread(void* _value);
	private :
		static Controller::CTextureController *m_TextureController;
		static Controller::CMeshController *m_MeshController;
		static Controller::CShaderController *m_ShaderController;

		static HANDLE m_Thread;
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