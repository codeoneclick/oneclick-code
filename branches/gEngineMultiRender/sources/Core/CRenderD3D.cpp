#include "CRenderD3D.h"
#include "CGlobal.h"
#include "CTextureD3D.h"

using namespace Core;

CRenderD3D::CRenderD3D()
{

}

CRenderD3D::~CRenderD3D()
{

}

void CRenderD3D::BeginRender()
{
	IDevice::Ref()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,0x00000000, 1.0f, 0); 
	IDevice::Ref()->BeginScene();
}

void CRenderD3D::EndRender()
{
	IDevice::Ref()->EndScene(); 
    IDevice::Ref()->Present(NULL, NULL, NULL, NULL);
}

void CRenderD3D::Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count)
{
	if(_vertex_count == 0) return;
	IDevice::Ref()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertex_count, 0, _primitive_count);
}

void CRenderD3D::BeginRenderTarget(Core::ITexture *_texture)
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

void CRenderD3D::EndRenderTarget()
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