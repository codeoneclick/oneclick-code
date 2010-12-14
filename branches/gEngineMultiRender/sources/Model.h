#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <vector>
#include <math.h>
#include "Dummy.h"
#include "Matrix4x4.h"
#include "Resource.h"

namespace Enviroment
{
class CModel : public CDummy
{
	public :
		CModel();
		~CModel();
		virtual void Load(std::vector<SResource> _resource);
		virtual void Update();
		virtual void Render();
};
};

#endif