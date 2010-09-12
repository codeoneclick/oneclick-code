#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Heightmap.h"
#include "Water.h"
#include "Grass.h"
#include "Tileset.h"
#include "RenderController.h"

struct LevelChunk
{
	Heightmap *_heightmap;
	Water     *_water;
	Grass     *_grass;
	LevelIndex _index;
};

class Level 
{
	private:
		Tileset *_mapTileSet;
		std::vector<LevelChunk*> _levelContainer;
	public:
		void Load(std::string &name);
		void Update(RenderTextureType _type);
		void Render(RenderTextureType _type);
};

#endif