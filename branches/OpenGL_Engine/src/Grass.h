#ifndef _GRASS_H_
#define _GRASS_H_

#include "Dummy.h"

class Grass : public Dummy
{
public :
	Grass();
	virtual void Load(std::string value) {};
	void Load(std::string value, LevelIndex _index);
	virtual void Update();
	virtual void Render();
	void UpdateData(UpdateDataFlag _flag);
};

#endif