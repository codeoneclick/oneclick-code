#include "CGlobal.h"
#include "CDeviceD3D.h"
#include "CRenderD3D.h"

using namespace Core;

CGlobal::RENDER_DEVICE CGlobal::m_RenderDevice = CGlobal::RENDER_DEVICE::D3D;

IDevice *CGlobal::m_Device = NULL;

IDevice *CGlobal::GetDevice()
{	
	if(m_Device == NULL)
	{
		switch(m_RenderDevice)
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
		switch(m_RenderDevice)
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
