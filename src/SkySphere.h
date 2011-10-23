#ifndef _SKYSPHERE_H_
#define _SKYSPHERE_H_

#include "m3_Entity.h"

class SkySphere : public m3_Entity
{
private :
	std::string _meshFileName;
public :
	SkySphere();
	virtual void Load(std::string value);
	virtual void Update();
	virtual void Render();
};

#endif