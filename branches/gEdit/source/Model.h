#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <math.h>
#include "Dummy.h"
#include "Matrix4x4.h"

namespace Enviroment
{
class CModel : public CDummy
{
	public :
		CModel();
		virtual void Load(std::string value);
		virtual void Update();
		virtual void Render();
};
};

#endif