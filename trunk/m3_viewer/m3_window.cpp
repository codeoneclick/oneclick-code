#include "m3_Window.h"

int				m3_Window::wndHeight	= 600;
int				m3_Window::wndWidth	= 800;
HWND			m3_Window::hWindow	= NULL;
bool			m3_Window::fullScreen = false;
WNDCLASSEX      m3_Window::wndClass   = WNDCLASSEX();

void m3_Window::Load()
{
	 /*wndClass.cbSize = sizeof(WNDCLASSEX);           
	 wndClass.style = CS_OWNDC | CS_DBLCLKS;      
	 wndClass.lpfnWndProc = m3_Input::wndProc;                
	 wndClass.cbClsExtra = 0;                        
     wndClass.cbWndExtra = 0;                       
     wndClass.hInstance = GetModuleHandle(NULL);                 
     wndClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
     wndClass.hCursor = LoadCursor(NULL, IDC_HAND); 
     wndClass.hbrBackground = NULL;                  
     wndClass.lpszMenuName = "m3_Viewer";                  
     wndClass.lpszClassName = "m3_Viewer";
     wndClass.hIconSm = LoadIcon(NULL, IDI_EXCLAMATION);
     if(!RegisterClassEx(&wndClass)) return;
		hWindow = CreateWindowEx(NULL,"m3_Viewer","m3_Viewer",  WS_OVERLAPPED  | 
                             WS_CAPTION        | 
                             WS_SYSMENU        | 
                             WS_VISIBLE, 0, 0,m3_Window::wndWidth, m3_Window::wndHeight,NULL,NULL,GetModuleHandle(NULL), NULL);                                     
     DWORD dw = GetLastError(); 
	 if(!hWindow) return;
     ShowWindow(hWindow, SW_SHOW);   
     UpdateWindow(hWindow);   */
}

