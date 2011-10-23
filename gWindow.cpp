#include "gWindow.h"

int				gWindow::wndHeight	= 600;
int				gWindow::wndWidth	= 800;
HWND			gWindow::hWindow	= NULL;
bool			gWindow::fullScreen = false;
WNDCLASSEX      gWindow::wndClass   = WNDCLASSEX();

void gWindow::Load()
{
	 wndClass.cbSize = sizeof(WNDCLASSEX);           
	 wndClass.style = CS_OWNDC | CS_DBLCLKS;      
	 wndClass.lpfnWndProc = gInput::wndProc;                
	 wndClass.cbClsExtra = 0;                        
     wndClass.cbWndExtra = 0;                       
     wndClass.hInstance = GetModuleHandle(NULL);                 
     wndClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
     wndClass.hCursor = LoadCursor(NULL, IDC_HAND); 
     wndClass.hbrBackground = NULL;                  
     wndClass.lpszMenuName = "gEngine";                  
     wndClass.lpszClassName = "gEngine";
     wndClass.hIconSm = LoadIcon(NULL, IDI_EXCLAMATION);
     if(!RegisterClassEx(&wndClass)) return;
     hWindow = CreateWindowEx(NULL,"gEngine","gEngine", WS_POPUPWINDOW, 0, 0,gWindow::wndWidth, gWindow::wndHeight,NULL,NULL,GetModuleHandle(NULL), NULL);                                     
     DWORD dw = GetLastError(); 
	 if(!hWindow) return;
     ShowWindow(hWindow, SW_SHOW);   
     UpdateWindow(hWindow);                         
}

