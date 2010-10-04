#include "Window.h"
#include "Input.h"
using namespace Core;

unsigned int CWindow::m_Width  = 640;
unsigned int CWindow::m_Height = 480; 
bool CWindow::m_Fullscreen = false;

HDC CWindow::m_handleDC;			
HWND CWindow::m_handleWindow;		
HINSTANCE CWindow::m_handleInstance;	

CWindow::CWindow()
{
}

void CWindow::_CreateWindow(unsigned int _width, unsigned int _height, unsigned int _bpp)
{
	m_Width = _width;
	m_Height = _height;


	unsigned int pixelFormat;			
	WNDCLASS	windowClass;					
	DWORD		windowExtStyle;				
	DWORD		windowStyle;			
	RECT		windowRectangle;				
	windowRectangle.left = 0;			
	windowRectangle.right = m_Width;		
	windowRectangle.top = 0;			
	windowRectangle.bottom = m_Height;			

	m_handleInstance = GetModuleHandle(NULL);				
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	windowClass.lpfnWndProc		= (WNDPROC) core::Input::InputProcess;		
	windowClass.cbClsExtra		= 0;									
	windowClass.cbWndExtra		= 0;								
	windowClass.hInstance		= m_handleInstance;						
	windowClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	windowClass.hbrBackground	= NULL;									
	windowClass.lpszMenuName	= NULL;							
	windowClass.lpszClassName	= "Engine";						

	if (!RegisterClass(&windowClass))									
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;											
	}
	

	windowExtStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		
	windowStyle = WS_OVERLAPPEDWINDOW;							


	AdjustWindowRectEx(&windowRectangle, windowStyle, false , windowExtStyle);

	DWORD dw = GetLastError(); 
	if (!(m_handleWindow = CreateWindowEx(windowExtStyle,							
								"Engine",						
								"Engine",								
								windowStyle |							
								WS_CLIPSIBLINGS |					
								WS_CLIPCHILDREN,					
								0, 0,								
								windowRectangle.right - windowRectangle.left,	
								windowRectangle.bottom - windowRectangle.top,	
								NULL,								
								NULL,								
								m_handleInstance,							
								NULL)))							
	{
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);		
		return;								
	}

	static PIXELFORMATDESCRIPTOR pfd =				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		_bpp,									
		0, 0, 0, 0, 0, 0,						
		0,											
		0,											
		0,											
		0, 0, 0, 0,									
		16,											 
		0,										
		0,										
		PFD_MAIN_PLANE,							
		0,											
		0, 0, 0										
	};
	
	if (!(m_handleDC=GetDC(m_handleWindow)))							
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
	}

	if (!(pixelFormat = ChoosePixelFormat(m_handleDC,&pfd)))
	{							
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;							
	}

	if(!SetPixelFormat(m_handleDC,pixelFormat,&pfd))		
	{				
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;							
	}				
}

void CWindow::SetText(std::string text)
{
	SetWindowText(m_handleWindow,text.c_str());
}
