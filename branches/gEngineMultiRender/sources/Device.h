#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <windows.h>		
#include <gl\gl.h>		
#include <gl\glu.h>
#include <string>
#include <d3dx9.h>
#include "Window.h"

namespace Core
{
	class CDevice : public CWindow
	{
	private :
		void CreateD3DContext();
		void CreateOGLContext();
	protected :
		static LPDIRECT3DDEVICE9 m_D3DDevice;
		static DEVICETYPE m_DeviceType;
		void CreateDevice(unsigned int _width, unsigned int _height, unsigned int _bpp, DEVICETYPE _device_type);
	public :
		__forceinline static LPDIRECT3DDEVICE9 GetDevice() { return m_D3DDevice; }
	`	__forceinline static LPDIRECT3DDEVICE9 GetDeviceType() { return m_DeviceType; }

		enum DEVICETYPE { D3D = 0, OGL };
	};
};

#endif