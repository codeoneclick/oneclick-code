#include "CDeviceD3D.h"
#include "CGlobal.h"

using namespace Core;

CDeviceD3D::CDeviceD3D()
{
   D3DDISPLAYMODE D3DMode;
   D3DPRESENT_PARAMETERS D3DParams;
	
   m_handle = Direct3DCreate9(D3D_SDK_VERSION);

   if(m_handle == NULL)
   {
      return;
   }

   if(FAILED(m_handle->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DMode)))
   {
      return;
   }

   ZeroMemory(&D3DParams, sizeof(D3DParams));

   D3DParams.Windowed = TRUE;  
   D3DParams.BackBufferWidth  = CGlobal::GetWidth();
   D3DParams.BackBufferHeight = CGlobal::GetHeight();

   D3DParams.BackBufferFormat           = D3DMode.Format;
   D3DParams.BackBufferCount            = 3;
   D3DParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
   D3DParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
   D3DParams.EnableAutoDepthStencil     = TRUE;
   D3DParams.AutoDepthStencilFormat     = D3DFMT_D24X8;

   if(FAILED(m_handle->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, CGlobal::GetHWND(),
                               D3DCREATE_HARDWARE_VERTEXPROCESSING  | D3DCREATE_MULTITHREADED ,
                               &D3DParams, &m_device)))
   {
      return;
   }	
	m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); 
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    m_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
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

void CDeviceD3D::SetViewport(int _x, int _y, unsigned int _width, unsigned int _height)
{
    D3DVIEWPORT9 viewport;
    viewport.X = _x;
    viewport.Y = _y;
    viewport.Width  = _width;
    viewport.Height = _height;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;
    m_device->SetViewport(&viewport);
}