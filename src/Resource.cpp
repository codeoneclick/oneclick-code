#include "Resource.h"

TextureService *Resource::_textureServiceInstance = NULL;
bool Resource::_textureServiceSingleFlag = false;

TextureService *Resource::TextureContainer()
{
	if(_textureServiceSingleFlag)
		return _textureServiceInstance;
	else
	{
		_textureServiceSingleFlag = true;
		_textureServiceInstance = new TextureService();
		return _textureServiceInstance;
	}
}

MeshService *Resource::_meshServiceInstance = NULL;
bool Resource::_meshServiceSingleFlag = false;

MeshService *Resource::MeshContainer()
{
	if(_meshServiceSingleFlag)
		return _meshServiceInstance;
	else
	{
		_meshServiceSingleFlag = true;
		_meshServiceInstance = new MeshService();
		return _meshServiceInstance;
	}
}


ShaderService *Resource::_shaderServiceInstance = NULL;
bool Resource::_shaderServiceSingleFlag = false;

ShaderService *Resource::ShaderContainer()
{
	if(_shaderServiceSingleFlag)
		return _shaderServiceInstance;
	else
	{
		_shaderServiceSingleFlag = true;
		_shaderServiceInstance = new ShaderService();
		return _shaderServiceInstance;
	}
}


MapService *Resource::_mapServiceInstance = NULL;
bool Resource::_mapServiceSingleFlag = false;

MapService *Resource::MapContainer()
{
	if(_mapServiceSingleFlag)
		return _mapServiceInstance;
	else
	{
		_mapServiceSingleFlag = true;
		_mapServiceInstance = new MapService("Content\\maps\\map.raw");
		return _mapServiceInstance;
	}
}