#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_
#include "Window.h"
#include "Core/ITexture.h"
#include <stdlib.h>
#include <string>
#include <map>

namespace Video
{

#define SCREEN_TEXTURE_WIDTH  1024
#define SCREEN_TEXTURE_HEIGHT 768

#define REFLECTION_TEXTURE_WIDTH 512
#define REFLECTION_TEXTURE_HEIGHT 512

#define REFRACTION_TEXTURE_WIDTH 512
#define REFRACTION_TEXTURE_HEIGHT 512

	class CRenderController
	{
	public :

	enum ERenderTexture
	{
		SCREEN_TEXTURE = 0,
		REFLECTION_TEXTURE,
		REFRACTION_TEXTURE,
	};

	private :
		static std::map<ERenderTexture,Core::ITexture*> m_RenderTargetTextureContainer;
		static void TextureEnable();
		static void TextureDisable();
	public  :
		static void Init();
		static void Render2Texture(ERenderTexture value);
		static void Render(ERenderTexture value);
		static void RenderPost();
		__forceinline static Core::ITexture *GetRenderTargetTexture(ERenderTexture _value) { return m_RenderTargetTextureContainer[_value]; }
	};
};

#endif