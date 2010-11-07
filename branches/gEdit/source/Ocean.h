#ifndef _OCEAN_H_
#define _OCEAN_H_

#include <string>
#include <math.h>
#include "Dummy.h"
#include "Matrix4x4.h"

namespace Enviroment
{
class COcean : public CDummy
{
	private :
		unsigned int   _width;
		unsigned int   _height;
	public :
		COcean();
		virtual void Load(std::string value);
		virtual void Update();
		virtual void Render();
};
};

#endif