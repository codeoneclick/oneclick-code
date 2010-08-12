#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "TextureController.h"
#include "MeshController.h"
#include "ShaderController.h"

class Resource
{
	private :
		static CTextureController *_textureControllerInstance;
		static CMeshController    *_meshControllerInstance;
		static CShaderController  *_shaderControllerInstance;
	public :
		static CMeshController    *GetMeshControllerInstance();
		static CTextureController *GetTextureControllerInstance();
		static CShaderController  *GetShaderControllerInstance();
};

#endif