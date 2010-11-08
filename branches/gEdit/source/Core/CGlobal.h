#ifndef _CGLOBAL_H_
#define _CGLOBAL_H_

#include "IDevice.h"
#include "IRender.h"

namespace Core
{
	class CGlobal
	{
	public :
		enum RENDER_DEVICE { D3D = 0, OGL };
	private :
		static IDevice *m_Device;
		static IRender *m_Render;
		static HWND	m_HWND;	
		static unsigned int m_Width;
		static unsigned int m_Height;
		static RENDER_DEVICE m_RenderDeviceType;
	public :
		static IDevice *GetDevice();
		static IRender *GetRender();
		static __forceinline void SetRenderDeviceType(RENDER_DEVICE _type) { m_RenderDeviceType = _type;}
		static __forceinline unsigned int GetWidth() { return m_Width; }
		static __forceinline unsigned int GetHeight() { return m_Height; }
		static __forceinline HWND GetHWND() { return m_HWND; }
		static __forceinline void SetWidth(unsigned int _width) { m_Width = _width; }
		static __forceinline void SetHeight(unsigned int _height) { m_Height = _height; }
		static __forceinline void SetHWND(HWND _HWND) { m_HWND = _HWND; }
	};
};

#endif
