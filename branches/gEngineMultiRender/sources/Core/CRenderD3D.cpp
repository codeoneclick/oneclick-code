#include "CRenderD3D.h"
#include "CGlobal.h"
#include "CTextureD3D.h"
#include "../Game.h"

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

void CRenderD3D::EnableClipPlane(unsigned int _index, math::Vector3d _point_01, math::Vector3d _point_02, math::Vector3d _point_03)
{
	D3DXPLANE clipPlane;
	D3DXPlaneFromPoints(&clipPlane,&D3DXVECTOR3(_point_01.x,_point_01.y,_point_01.z),&D3DXVECTOR3(_point_02.x,_point_02.y,_point_02.z),&D3DXVECTOR3(_point_03.x,_point_03.y,_point_03.z));
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0 + _index);
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

	Core::CGlobal::GetDevice()->Ref()->SetClipPlane(_index, clipPlane);
}
void CRenderD3D::DisableClipPlane(unsigned int _index)
{
	Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
}

void CRenderD3D::SetCullFace(ECULLFACE _value)
{
	switch(_value)
	{
		case IRender::CULL_NONE :
			IDevice::Ref()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		case IRender::CULL_CW :
			IDevice::Ref()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		case IRender::CULL_CCW :
			IDevice::Ref()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
	}
}