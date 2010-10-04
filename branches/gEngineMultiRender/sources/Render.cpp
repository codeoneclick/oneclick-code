#include "Render.h"

using namespace Core;

CRender::CRender()
{

}

CRender::~CRender()
{

}

void CRender::BeginRender()
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		CDevice::GetD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,0x00000000, 1.0f, 0); 
		CDevice::GetD3DDevice()->BeginScene();
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void CRender::EndRender()
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
	    CDevice::GetD3DDevice()->EndScene(); 
        CDevice::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
	}
	else
	{
	    glFlush();
		SwapBuffers(CWindow::GetHDC());
	}
}

void CRender::SetViewport(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height)
{
	if(CDevice::GetDeviceType() == CDevice::D3D)
	{
		D3DVIEWPORT9 viewport;
		viewport.X = _x;
		viewport.Y = _y;
		viewport.Width  = _width;
		viewport.Height = _height;
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CDevice::GetD3DDevice()->SetViewport(&viewport);
	}
	else
	{
		glViewport( _x,_y,_width ,_height );
	}
}

void CRender::Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count)
{
	if(CDevice::GetDeviceType() == CDevice::D3D)
	{
		if(_vertex_count == 0) return;
		CDevice::GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertex_count, 0, _primitive_count);
	}
	else
	{
		if(_index_count == 0) return;
		glDrawElements( GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, NULL);
	}	
}


