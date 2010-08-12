#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_
#include "Window.h"

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
	struct SRenderTexture
	{
		unsigned int texture_addr;
		unsigned int frame_buffer_addr;
		unsigned int render_buffer_addr;
		unsigned int width;
		unsigned int height;
		SRenderTexture(unsigned int _texture_addr,unsigned int _frame_buffer_addr,unsigned int _render_buffer_addr,unsigned int _width,unsigned int _height)
		{
			texture_addr = _texture_addr;
			frame_buffer_addr = _frame_buffer_addr;
			render_buffer_addr = _render_buffer_addr;
			width = _width;
			height = _height;
		}
	};

	enum ERenderTexture
	{
		SCREEN_TEXTURE = 0,
		REFLECTION_TEXTURE,
		REFRACTION_TEXTURE,
	};

	struct SClipSetting
	{
		float fClipInc;
		float fClipHeight;
	};


private :
	static SRenderTexture _screenTexture;
	static SRenderTexture _reflectionTexture; 
	static SRenderTexture _refractionTexture;

	static void _TextureEnable(SRenderTexture *texture);
	static void _TextureDisable();
public  :
	static void Load();
	static void Render2Texture(ERenderTexture value);
	static const unsigned int GetRenderTexture(ERenderTexture value);
	static void Render();
	static SClipSetting clipSetting;
};
};

#endif