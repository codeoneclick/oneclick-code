#ifndef _CGLOBAL_H_
#define _CGLOBAL_H_

#include "IDevice.h"
#include "IRender.h"

namespace Core
{
	class CGlobal
	{
	public :
		enum RENDER_DEVICE { D3D = 0, OGL };
	private :
		static IDevice *m_Device;
		static IRender *m_Render;
	public :
		static IDevice *GetDevice();
		static IRender *GetRender();
		static RENDER_DEVICE m_RenderDevice;
	};
};

#endif
