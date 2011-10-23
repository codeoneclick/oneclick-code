#ifndef _LEVELCHUNK_H_
#define _LEVELCHUNK_H_

#include "Heightmap.h"
#include "Grass.h"
#include "Water.h"
#include "RenderController.h"

class LevelChunk
{
private :
	Heightmap *_heightmap;
	Grass     *_grass;
	Water     *_water;
	LevelIndex _index;
public :
	LevelChunk();
	void Load(VertexBufferPtrExt *_heightmapVertexData,std::string &name, LevelIndex _indexValue);
	void Update(RenderTextureType _renderType);
	void Render(RenderTextureType _renderType);
};

#endif