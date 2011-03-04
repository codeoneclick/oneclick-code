#include "CDeviceD3D.h"
#include "Window.h"
#include "../Game/Game.h"

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

CDeviceD3D::~CDeviceD3D()
{

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

void CDeviceD3D::BeginRender()
{
	m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,0x00000000, 1.0f, 0); 
	m_device->BeginScene();
}

void CDeviceD3D::EndRender()
{
	m_device->EndScene(); 
    m_device->Present(NULL, NULL, NULL, NULL);
}

void CDeviceD3D::Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count)
{
	if(_vertex_count == 0) return;
	m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertex_count, 0, _primitive_count);
}

void CDeviceD3D::BeginRenderTarget(Core::ITexture *_texture)
{
	IDevice::Ref()->GetViewport(&m_OldViewport);
    IDevice::Ref()->GetRenderTarget(0, &m_OldRenderSurface);
    IDevice::Ref()->GetDepthStencilSurface(&m_OldStencilSurface);	

	((CTextureD3D*)_texture)->m_addr->GetSurfaceLevel(0,&m_CurrentStencilSurface);

	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width  = _texture->m_Width;
	viewport.Height = _texture->m_Height;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

    IDevice::Ref()->SetViewport(&viewport);
	IDevice::Ref()->SetRenderTarget(0,m_CurrentStencilSurface);
	IDevice::Ref()->SetDepthStencilSurface(((CTextureD3D*)_texture)->m_addr_surf);
    IDevice::Ref()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,0x00000000, 1.0f, 0); 
	IDevice::Ref()->BeginScene();
}

void CDeviceD3D::EndRenderTarget()
{
	IDevice::Ref()->EndScene();
 
    IDevice::Ref()->SetDepthStencilSurface(m_OldStencilSurface);

	if(m_OldStencilSurface!=NULL)
	{
		m_OldStencilSurface->Release();
		m_OldStencilSurface=NULL;
	}

	if(m_CurrentStencilSurface != NULL)
	{
		m_CurrentStencilSurface->Release();
		m_CurrentStencilSurface = NULL;
	}
  
	IDevice::Ref()->SetRenderTarget(0,m_OldRenderSurface);
	if(m_OldRenderSurface != NULL)
	{
		m_OldRenderSurface->Release();
		m_OldRenderSurface = NULL;
	}

	IDevice::Ref()->SetViewport(&m_OldViewport);
}

void CDeviceD3D::EnableClipPlane(unsigned int _index, math::Vector3d _point_01, math::Vector3d _point_02, math::Vector3d _point_03)
{
	D3DXPLANE clipPlane;
	D3DXPlaneFromPoints(&clipPlane,&D3DXVECTOR3(_point_01.x,_point_01.y,_point_01.z),&D3DXVECTOR3(_point_02.x,_point_02.y,_point_02.z),&D3DXVECTOR3(_point_03.x,_point_03.y,_point_03.z));
	Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0 + _index);
	D3DXVECTOR4 clipVector = D3DXVECTOR4(clipPlane.a,clipPlane.b,clipPlane.c,clipPlane.d);
	math::Matrix4x4 mClipPlane = Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView * Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection;
	D3DXMATRIX clipMatrix;
	memcpy(clipMatrix.m,mClipPlane.m,16 * sizeof(float));
	D3DXMatrixTranspose(&clipMatrix,&clipMatrix);
	D3DXMatrixInverse(&clipMatrix,NULL,&clipMatrix);
	D3DXVec4Transform(&clipVector,&clipVector,&clipMatrix);

	clipPlane.a = clipVector.x;
	clipPlane.b = clipVector.y;
	clipPlane.c = clipVector.z;
	clipPlane.d = clipVector.w;

	Ref()->SetClipPlane(_index, clipPlane);
}
void CDeviceD3D::DisableClipPlane(unsigned int _index)
{
	Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
}

void CDeviceD3D::SetCullFace(ECULLFACE _value)
{
	switch(_value)
	{
		case IDevice::CULL_NONE :
			m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		case IDevice::CULL_CW :
			m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		case IDevice::CULL_CCW :
			m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
	}
}