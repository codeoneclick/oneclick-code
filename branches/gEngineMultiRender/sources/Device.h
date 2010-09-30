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
	public :
		enum DEVICETYPE { D3D = 0, OGL };
	private :
		void CreateD3DContext();
		void CreateOGLContext();

		HGLRC m_handleGLRC;
		LPDIRECT3D9 m_handleD3D;
	protected :
		static LPDIRECT3DDEVICE9 m_D3DDevice;
		static DEVICETYPE m_DeviceType;
		void _CreateDevice(unsigned int _width, unsigned int _height, unsigned int _bpp, DEVICETYPE _device_type);
	public :
		CDevice();
		__forceinline static LPDIRECT3DDEVICE9 GetD3DDevice() { return m_D3DDevice; }
		__forceinline static DEVICETYPE GetDeviceType() { return m_DeviceType; }
	};
};

#endif