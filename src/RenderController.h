#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_

#include "window.h"
#include "FB.h"
#include "RenderScreenPlane.h"

enum RenderTextureType
{
	RENDER_SIMPLE_TEXTURE = 0,
	RENDER_SHADOWMAP_TEXTURE,
	RENDER_REFLECTION_TEXTURE,
	RENDER_REFRACTION_TEXTURE
};

enum RenderType
{
	RENDER_SIMPLE = 0,
	RENDER_POST
};

struct RenderTexture
{
	unsigned int textureId;
	unsigned int frameBufferId;
	unsigned int renderBufferId;
	unsigned int width;
	unsigned int height;
	RenderTexture(unsigned int _textureId,unsigned int _width,unsigned int _height,unsigned int _frameBufferId,unsigned int _renderBufferId)
	{
		textureId = _textureId;
		frameBufferId = _frameBufferId;
		renderBufferId = _renderBufferId;
		width = _width;
		height = _height;
	}
};

#define SIMPLE_POST_TEXTURE_WIDTH  800
#define SIMPLE_POST_TEXTURE_HEIGHT 600

#define SHADOWMAP_POST_TEXTURE_WIDTH 512
#define SHADOWMAP_POST_TEXTURE_HEIGHT 512

#define REFLECTION_POST_TEXTURE_WIDTH 512
#define REFLECTION_POST_TEXTURE_HEIGHT 512

#define REFRACTION_POST_TEXTURE_WIDTH 512
#define REFRACTION_POST_TEXTURE_HEIGHT 512

class RenderController
{
	private :
		static RenderTexture _simpleTexture;
		static RenderTexture _shadowmapTexture;
		static RenderTexture _reflectionTexture; 
		static RenderTexture _refractionTexture; 

		static RenderScreenPlane _renderScreenPlane;

		static void  _EnableRenderToTexture(RenderTexture *textureData);
		static void  _EnableRenderToCubeTexture(RenderTexture *textureData, unsigned int cubeSurface);
		static void  _DisableRenderToTexture();
		static void  _Render(RenderTextureType _type);
		static void  _RenderScreenPlane(const RenderTexture *textureData);
		static void _OrthoEnable();
		static void _OrthoDisable();
	public :
		static void Load();
		static void RenderToTexture(RenderTextureType _type);
		static unsigned int GetRenderTexture(RenderTextureType _type);
		static void Render(RenderType _type);
};

#endif
