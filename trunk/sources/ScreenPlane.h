#ifndef _SCREENPLANE_H_
#define _SCREENPLANE_H_

#include "Dummy.h"

namespace Video
{

class CScreenPlane
{
public :
	CScreenPlane();
	virtual void Update();
	virtual void Render();
};
};
#endif