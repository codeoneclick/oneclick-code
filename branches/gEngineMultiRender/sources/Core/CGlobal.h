#ifndef _CGLOBAL_H_
#define _CGLOBAL_H_

#include "IDevice.h"

namespace Core
{
	class CGlobal
	{
	private :
		static IDevice *m_Device;
	public :
		static IDevice *GetDevice();	
	};
};

#endif
