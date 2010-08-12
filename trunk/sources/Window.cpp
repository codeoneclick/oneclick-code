#include "Window.h"
#include "Input.h"
using namespace core;

unsigned int Window::Width  = 1024;
unsigned int Window::Height = 768; 

Window::Window()
{
	_currentWidth  = 1024;
	_currentHeight = 768;
	_oldWidth  = 1024;
	_oldHeight = 768;

	_bitsPerPixel = 16;

	_fullscreen = false;
}

bool Window::_CreateWindowContext()
{
	GLuint		pixelFormat;			
	WNDCLASS	windowClass;					
	DWORD		windowExtStyle;				
	DWORD		windowStyle;			
	RECT		windowRectangle;				
	windowRectangle.left = 0;			
	windowRectangle.right = _currentWidth;		
	windowRectangle.top = 0;			
	windowRectangle.bottom = _currentHeight;			

	hInstance			= GetModuleHandle(NULL);				
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	windowClass.lpfnWndProc		= (WNDPROC) Input::InputProcess;		
	windowClass.cbClsExtra		= 0;									
	windowClass.cbWndExtra		= 0;								
	windowClass.hInstance		= hInstance;						
	windowClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	windowClass.hbrBackground	= NULL;									
	windowClass.lpszMenuName	= NULL;							
	windowClass.lpszClassName	= "gEngine";						

	if (!RegisterClass(&windowClass))									
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											
	}
	
	if (_fullscreen)												
	{
		DEVMODE dmScreenSettings;							
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth	= _currentWidth;	
		dmScreenSettings.dmPelsHeight	= _currentHeight;
		dmScreenSettings.dmBitsPerPel	= _bitsPerPixel;	
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION);
			return false;					
		}
	}

	if (_fullscreen)												
	{
		windowExtStyle = WS_EX_APPWINDOW;								
		windowStyle = WS_POPUP;										
		ShowCursor(false);										
	}
	else
	{
		windowExtStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		
		windowStyle = WS_OVERLAPPEDWINDOW;							
	}

	AdjustWindowRectEx(&windowRectangle, windowStyle, false , windowExtStyle);

	DWORD dw = GetLastError(); 
	if (!(hWnd=CreateWindowEx(windowExtStyle,							
								"gEngine",						
								"gEngine",								
								windowStyle |							
								WS_CLIPSIBLINGS |					
								WS_CLIPCHILDREN,					
								0, 0,								
								windowRectangle.right - windowRectangle.left,	
								windowRectangle.bottom - windowRectangle.top,	
								NULL,								
								NULL,								
								hInstance,							
								NULL)))							
	{
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);		
		return false;								
	}

	static PIXELFORMATDESCRIPTOR pfd =				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		_bitsPerPixel,									
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
	
	if (!(hDC=GetDC(hWnd)))							
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								
	}

	if (!(pixelFormat = ChoosePixelFormat(hDC,&pfd)))
	{							
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;							
	}

	if(!SetPixelFormat(hDC,pixelFormat,&pfd))		
	{				
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;							
	}

	if (!(hRC=wglCreateContext(hDC)))				
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{				
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								
	}

	ShowWindow(hWnd,SW_SHOW);						
	return true;			
}

void Window::SetWindowCaption(std::string text)
{
	SetWindowText(hWnd,text.c_str());
}

bool Window::_CreateGLContext()
{
	glShadeModel(GL_SMOOTH);
	glEnable( GL_DEPTH_TEST );
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_CULL_FACE);
	glViewport(0,0,_currentWidth ,_currentHeight);
	glMatrixMode (GL_PROJECTION);										
	glLoadIdentity ();													
	glMatrixMode (GL_MODELVIEW);										
	glLoadIdentity ();				
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClearDepth (1.0f);
	return true;
}