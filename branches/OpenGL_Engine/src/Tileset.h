#ifndef _TILESET_H_
#define _TILESET_H_

#include "Dummy.h"

class Tileset : public Dummy
{
	private :
		float **_heightmap;
		float _clipPlaneValue;
		std::string _mapName;
	public :
		Tileset();
		inline void SetClipPlane(float value) { _clipPlaneValue = value; };
		virtual void Load(std::string value) { };
		void Load(std::string value, LevelIndex _index);
		virtual void Update();
		virtual void Render();
		void UpdateData(UpdateDataFlag _flag);
};

#endif