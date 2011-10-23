#ifndef _CGLOBAL_H_
#define _CGLOBAL_H_

#include "IDevice.h"
#include "CBaseSecond.h"
#include <map>

typedef void(CBase::*PTR_EVENT_FUN)();

namespace Core
{
	class CGlobal
	{
	public :
		enum RENDER_DEVICE { D3D = 0, OGL };
	private :
		static std::map<std::string, PTR_EVENT_FUN> m_callbacks;
		static IDevice *m_Device;
	public :
		static IDevice *GetDevice();
		static RENDER_DEVICE m_RenderDevice;

		static void addEventListener();
	};
};

#endif
