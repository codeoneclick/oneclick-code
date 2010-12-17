#include "CDeviceD3D.h"
#include "..\Window.h"

using namespace Core;

CDeviceD3D::CDeviceD3D()
{
   D3DDISPLAYMODE D3DMode;
   D3DPRESENT_PARAMETERS D3DParams;
	
   m_handle = Direct3DCreate9(D3D_SDK_VERSION);

   if(m_handle == NULL)
   {
      MessageBox(NULL, "DirectX 9.0 не инициализирован...","Ошибка!", MB_OK);
      return;
   }

   if(FAILED(m_handle->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DMode)))
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

   if(FAILED(m_handle->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, CWindow::GetHWND(),
                               D3DCREATE_HARDWARE_VERTEXPROCESSING  | D3DCREATE_MULTITHREADED ,
                               &D3DParams, &m_device)))
   {
      MessageBox(NULL, "Невозможно создать устройство DirectX 9.0","Ошибка!", MB_OK);
      return;
   }

	ShowWindow(CWindow::GetHWND(),SW_SHOW);			

	m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); 
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    m_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	m_device->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    //m_device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    //m_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    //m_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
    //m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
    //m_device->SetRenderState(D3DRS_ALPHAREF, (DWORD)128);
	//m_device->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
    m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	

}

Core::ITexture* CDeviceD3D::CreateTexture()
{
	CTextureD3D *out_texture = new CTextureD3D();
	return out_texture;
}

Core::IShader* CDeviceD3D::CreateShader()
{
	CShaderD3D *out_shader = new CShaderD3D();
	return out_shader;
}

Core::IVertexBuffer* CDeviceD3D::CreateVertexBuffer()
{
	CVertexBufferD3D *out_vertex_buffer = new CVertexBufferD3D();
	return out_vertex_buffer;
}

Core::IIndexBuffer* CDeviceD3D::CreateIndexBuffer()
{
	CIndexBufferD3D *out_index_buffer = new CIndexBufferD3D();
	return out_index_buffer;
}