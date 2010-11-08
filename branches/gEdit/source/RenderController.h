#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H

#include "Camera.h"
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

namespace Video
{
	class CRenderController
	{
	public :
		enum E_VIEWPORT { VIEWPORT_TOP = 0, VIEWPORT_FRONT, VIEWPORT_LEFT, VIEWPORT_PERSPECTIVE };
		enum E_FILLMODE { MODE_SOLID = 0, MODE_WIREFRAME };
		enum E_RENDERTARGET { RENDER_SIMPLE = 0, RENDER_TEXTURE };
		struct SViewportSetting
		{
			E_FILLMODE m_FillMode;
			E_RENDERTARGET m_RenderTarget;
			int m_X,m_Y;
			unsigned int m_Width, m_Height; 
		};
	private :
		static void TextureEnable();
		static void TextureDisable();
		static void RenderViewport(E_VIEWPORT _value);
		static std::map<E_VIEWPORT,Enviroment::Camera*> m_Camera;
		static std::map<E_VIEWPORT,SViewportSetting*> m_ViewportSetting;
	public  :
		static void Init();
		static void Render2Texture();
		static void Render();
		static __forceinline Enviroment::Camera* GetCamera(E_VIEWPORT _value) { return m_Camera[_value]; }
	};
};

#endif