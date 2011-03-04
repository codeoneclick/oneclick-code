#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>		
#include <string>

namespace Core
{
	class CWindow
	{	
	protected :
		void _CreateWindow(unsigned int _width, unsigned int _height, unsigned int _bpp);
		static HDC m_handleDC;			
		static HWND	m_handleWindow;		
		static HINSTANCE m_handleInstance;	
	public  :
		CWindow();	
		void  SetText(std::string text);
		__forceinline static HDC GetHDC() { return m_handleDC; }			
		__forceinline static HWND GetHWND(){ return	m_handleWindow;	}	
		__forceinline static HINSTANCE GetHINSTANCE() {return	m_handleInstance; }	
		static unsigned int m_Width;
		static unsigned int m_Height;
		static bool m_Fullscreen;

		virtual void Update(DWORD time) = 0;
		virtual void Render() = 0;
	};
};

#endif