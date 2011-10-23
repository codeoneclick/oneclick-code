#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "TextureService.h"
#include "MeshService.h"
#include "ShaderService.h"
#include "MapService.h"

class Resource
{
	private :
		static TextureService    *_textureServiceInstance;
		static bool              _textureServiceSingleFlag;

		static MeshService       *_meshServiceInstance;
		static bool              _meshServiceSingleFlag;

		static ShaderService     *_shaderServiceInstance;
		static bool              _shaderServiceSingleFlag;

		static MapService        *_mapServiceInstance;
		static bool              _mapServiceSingleFlag;

	public :
		static MeshService       *MeshContainer();
		static TextureService    *TextureContainer();
		static ShaderService     *ShaderContainer();
		static MapService        *MapContainer();
};

#endif