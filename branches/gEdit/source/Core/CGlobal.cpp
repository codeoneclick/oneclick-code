#include "CGlobal.h"
#include "CDeviceD3D.h"
#include "CRenderD3D.h"

using namespace Core;

HWND CGlobal::m_HWND = NULL;
unsigned int CGlobal::m_Width = 800;
unsigned int CGlobal::m_Height = 600;

CGlobal::RENDER_DEVICE CGlobal::m_RenderDeviceType = CGlobal::RENDER_DEVICE::D3D;

IDevice *CGlobal::m_Device = NULL;

IDevice *CGlobal::GetDevice()
{	
	if(m_Device == NULL)
	{
		switch(m_RenderDeviceType)
		{
		case RENDER_DEVICE::D3D :
			m_Device = new CDeviceD3D();
			break;
		case RENDER_DEVICE::OGL :

			break;
		}
	}
	return m_Device;
}

IRender *CGlobal::m_Render = NULL;

IRender *CGlobal::GetRender()
{	
	if(m_Render == NULL)
	{
		switch(m_RenderDeviceType)
		{
		case RENDER_DEVICE::D3D :
			m_Render = new CRenderD3D();
			break;
		case RENDER_DEVICE::OGL :

			break;
		}
	}
	return m_Render;
}
