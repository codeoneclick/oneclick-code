#ifndef _WATER_H_
#define _WATER_H_

#include "Dummy.h"

class Water : public Dummy
{
private :
	unsigned int _width;
	unsigned int _height;
	std::string  _mapName;
	void _CalculateTBN(unsigned int nVerteces,unsigned int nIndeces);
public :
	Water();
	virtual void Load(std::string value) { };
	void Load(std::string value, LevelIndex _index);
	virtual void Update();
	virtual void Render();
	void UpdateData(UpdateDataFlag _flag);
};

#endif