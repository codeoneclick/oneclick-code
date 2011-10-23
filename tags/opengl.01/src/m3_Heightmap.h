#pragma once
#ifndef _M3_HEIGHTMAP_H_
#define _M3_HEIGHTMAP_H_

#include "m3_Entity.h"

class m3_Heightmap : public m3_Entity
{
	private :
		unsigned int _width;
		unsigned int _height;
		float **_heightmap;
	public :
		m3_Heightmap();
		virtual void Load(std::string value);
		virtual void Update();
		virtual void Render();
		float GetHeight(float _positionX,float _positionZ);
};

#endif