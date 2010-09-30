#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>		
#include <string>

namespace Core
{
	class CWindow
	{	
	protected :
		void CreateWindow(unsigned int _width, unsigned int _height, unsigned int _bpp);
		HDC			m_handleDC;			
		HWND		m_handleWindow;		
		HINSTANCE	m_handleInstance;	
	public  :
		CWindow();	
		void  SetText(std::string text);
		static unsigned int m_Width;
		static unsigned int m_Height;
		static bool m_Fullscreen;
	};
};

#endif