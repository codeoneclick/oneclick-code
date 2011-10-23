#ifndef _SCENE_H_
#define _SCENE_H_

#include <windows.h>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Utility.h"
#include "Heightmap.h"
#include "Water.h"
#include "Grass.h"
#include "RenderController.h"
#include "Level.h"
#include "Editor.h"

class Scene
{
private :
	Mesh *_player;
	Level *_level;
	Editor *_editor;
public :
	void Load();
	void Update(RenderTextureType _type);
	void Render(RenderTextureType _type);
	inline Heightmap *GetHeightmapInstance() { return NULL; }
	inline Water *GetWaterInstance() { return NULL; }
	inline Grass *GetGrassInstance() { return NULL; }
	Scene();
};

#endif