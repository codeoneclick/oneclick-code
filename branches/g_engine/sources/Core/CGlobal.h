#ifndef _CGLOBAL_H_
#define _CGLOBAL_H_

#include "IDevice.h"

namespace Core
{
	class CGlobal
	{
	public :
		enum RENDER_DEVICE { D3D = 0, OGL };
	private :
		static IDevice *m_Device;
	public :
		static IDevice *GetDevice();
		static RENDER_DEVICE m_RenderDevice;
	};
};

#endif
