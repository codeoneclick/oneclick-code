#ifndef _RENDERSCREENPLANE_H_
#define _RENDERSCREENPLANE_H_

#include "Dummy.h"

class RenderScreenPlane : public Dummy
{
private :
	void _UpdateVB();
public :
	RenderScreenPlane();
	virtual void Load(std::string value) {};
	virtual void Update();
	virtual void Render();
};

#endif