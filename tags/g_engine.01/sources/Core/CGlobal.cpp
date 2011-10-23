#include "CGlobal.h"
#include "CDeviceD3D.h"

using namespace Core;

CGlobal::RENDER_DEVICE CGlobal::m_RenderDevice = CGlobal::D3D;

IDevice *CGlobal::m_Device = NULL;

IDevice *CGlobal::GetDevice()
{	
	if(m_Device == NULL)
	{
		switch(m_RenderDevice)
		{
		case D3D :
			m_Device = new CDeviceD3D();
			break;
		case OGL :

			break;
		}
	}
	return m_Device;
}