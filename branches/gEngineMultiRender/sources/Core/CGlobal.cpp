#include "CGlobal.h"
#include "CDeviceD3D.h"

using namespace Core;

IDevice *CGlobal::m_Device = NULL;

IDevice *CGlobal::GetDevice()
{	
	if(m_Device == NULL)
	{
		m_Device = new CDeviceD3D();
	}
	return m_Device;
}
