#include "CRenderD3D.h"
#include "CGlobal.h"

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
}

void CRenderD3D::Spitout()
{
	IDevice::Ref()->Present(NULL, NULL, NULL, NULL);
}

void CRenderD3D::SpitoutTo(HWND _handle)
{
	IDevice::Ref()->Present(NULL, NULL, _handle, NULL);
}

void CRenderD3D::Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count)
{
	if(_vertex_count == 0) return;
	IDevice::Ref()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertex_count, 0, _primitive_count);
}