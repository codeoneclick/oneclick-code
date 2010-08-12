#include "Resource.h"

CTextureController *Resource::_textureControllerInstance = NULL;

CTextureController *Resource::GetTextureControllerInstance()
{	
	if(_textureControllerInstance == NULL)
	{
		_textureControllerInstance = new CTextureController();
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

CShaderController *Resource::_shaderControllerInstance = NULL;

CShaderController *Resource::GetShaderControllerInstance()
{
	if(_shaderControllerInstance == NULL)
	{
		_shaderControllerInstance = new CShaderController();
	}
	return _shaderControllerInstance;
}
