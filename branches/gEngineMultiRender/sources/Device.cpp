#include "Device.h"
#include "VBExtension.h"
#include "FBExtension.h"

using namespace Core;

LPDIRECT3DDEVICE9 CDevice::m_D3DDevice = NULL;
CDevice::DEVICETYPE CDevice::m_DeviceType = CDevice::D3D;

CDevice::CDevice()
{
	m_handleD3D = NULL;
	m_D3DDevice = NULL;
}

void CDevice::_CreateDevice(unsigned int _width, unsigned int _height, unsigned int _bpp, Core::CDevice::DEVICETYPE _device_type)
{
	_CreateWindow(_width,_height,_bpp);

	switch(_device_type)
	{
	case D3D :
		CreateD3DContext();
		break;
	case OGL :
		CreateOGLContext();
		break;
	}
	m_DeviceType = _device_type;
}

void CDevice::CreateD3DContext()
{
	D3DDISPLAYMODE D3DMode;
	D3DPRESENT_PARAMETERS D3DParams;
	
	if(m_handleD3D != NULL)
	{
		 m_handleD3D->Release();
		 m_handleD3D = NULL;
	}
	if(m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

   m_handleD3D = Direct3DCreate9(D3D_SDK_VERSION);

   if(m_handleD3D == NULL)
   {
      MessageBox(NULL, "DirectX 9.0 не инициализирован...","Ошибка!", MB_OK);
      return;
   }

   if(FAILED(m_handleD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DMode)))
   {
      MessageBox(NULL, "Невозможно получить настройки экрана...", "Ошибка!", MB_OK);
      return;
   }

   ZeroMemory(&D3DParams, sizeof(D3DParams));

   D3DParams.Windowed = TRUE;  
   D3DParams.BackBufferWidth  = CWindow::m_Width;
   D3DParams.BackBufferHeight = CWindow::m_Height;

   D3DParams.BackBufferFormat           = D3DMode.Format;
   D3DParams.BackBufferCount            = 3;
   D3DParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
   D3DParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
   D3DParams.EnableAutoDepthStencil     = TRUE;
   D3DParams.AutoDepthStencilFormat     = D3DFMT_D24X8;

	if(FAILED(m_handleD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_handleWindow,
                               D3DCREATE_HARDWARE_VERTEXPROCESSING  | D3DCREATE_MULTITHREADED ,
                               &D3DParams, &m_D3DDevice)))
   {
      MessageBox(NULL, "Невозможно создать устройство DirectX 9.0","Ошибка!", MB_OK);
      return;
   }

	ShowWindow(m_handleWindow,SW_SHOW);			

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
}

void CDevice::CreateOGLContext()
{
	if (!(m_handleGLRC = wglCreateContext(m_handleDC)))				
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
	}

	if(!wglMakeCurrent(m_handleDC,m_handleGLRC))					
	{				
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return;								
	}

	ShowWindow(m_handleWindow,SW_SHOW);

	Extension::VBExtension::VBExtension();
	Extension::FBExtension::FBExtension();

	glShadeModel( GL_SMOOTH );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );	
	glEnable( GL_CULL_FACE );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearDepth( 1.0f );
}


	