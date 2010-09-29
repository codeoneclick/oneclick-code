#include "Window.h"
#include "Input.h"
using namespace core;

unsigned int Window::Width  = 640;
unsigned int Window::Height = 480; 

LPDIRECT3DDEVICE9  Window::m_D3DDevice = NULL;
bool  Window::m_D3DRender = false;

Window::Window()
{
	_currentWidth  = 640;
	_currentHeight = 480;
	_oldWidth  = 640;
	_oldHeight = 480;

	_bitsPerPixel = 16;

	_fullscreen = false;

	_m_D3D = NULL;
}

bool Window::_CreateWindowContext(std::string _value)
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

	hInstance = GetModuleHandle(NULL);				
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	windowClass.lpfnWndProc		= (WNDPROC) Input::InputProcess;		
	windowClass.cbClsExtra		= 0;									
	windowClass.cbWndExtra		= 0;								
	windowClass.hInstance		= hInstance;						
	windowClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	windowClass.hbrBackground	= NULL;									
	windowClass.lpszMenuName	= NULL;							
	windowClass.lpszClassName	= _value.c_str();						

	if (!RegisterClass(&windowClass))									
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											
	}
	
	if (_fullscreen)												
	{
		DEVMODE dmScreenSettings;							
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth	= _currentWidth;	
		dmScreenSettings.dmPelsHeight	= _currentHeight;
		dmScreenSettings.dmBitsPerPel	= _bitsPerPixel;	
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

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
								_value.c_str(),						
								_value.c_str(),								
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


	D3DDISPLAYMODE D3DMode;
	D3DPRESENT_PARAMETERS D3DParams;
	
	if(_m_D3D != NULL)
	{
		 _m_D3D->Release();
		 _m_D3D = NULL;
	}
	if(m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

   _m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

   if(_m_D3D == NULL)
   {
      MessageBox(NULL, "DirectX 9.0 не инициализирован...","Ошибка!", MB_OK);
      return false;
   }

   if(FAILED(_m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DMode)))
   {
      MessageBox(NULL, "Невозможно получить настройки экрана...", "Ошибка!", MB_OK);
      return false;
   }

   ZeroMemory(&D3DParams, sizeof(D3DParams));

   D3DParams.Windowed = TRUE;  
   D3DParams.BackBufferWidth  = Width;
   D3DParams.BackBufferHeight = Height;

   D3DParams.BackBufferFormat           = D3DMode.Format;
   D3DParams.BackBufferCount            = 3;
   D3DParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
   D3DParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
   D3DParams.EnableAutoDepthStencil     = TRUE;
   D3DParams.AutoDepthStencilFormat     = D3DFMT_D24X8;

	if(FAILED(_m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                               D3DCREATE_HARDWARE_VERTEXPROCESSING  | D3DCREATE_MULTITHREADED ,
                               &D3DParams, &m_D3DDevice)))
   {
      MessageBox(NULL, "Невозможно создать устройство DirectX 9.0","Ошибка!", MB_OK);
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
	glShadeModel( GL_SMOOTH );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );	
	glEnable( GL_CULL_FACE );
	glViewport( 0,0,_currentWidth ,_currentHeight );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearDepth( 1.0f );

	m_D3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); 
	m_D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    m_D3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    m_D3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    m_D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
    m_D3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
    m_D3DDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)128);
	m_D3DDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
    m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	D3DVIEWPORT9 viewport;
    viewport.X = 0;
    viewport.Y = 0;
    viewport.Width  = Width;
    viewport.Height = Height;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;
    m_D3DDevice->SetViewport(&viewport);

    return true;
}