#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "StructDef.h"

enum EDIT_TYPE { EDIT_NONE = 0, EDIT_HEIGHTMAP };
enum EDIT_HEIGHTMAP_TYPE { EDIT_HEIGHTMAP_SIMPLE = 0, EDIT_HEIGHTMAP_SMOOTH };

class Editor
{
private :
	Vector3d _vMousePosition3D;
	void _EditHeightmap();
public :
	void Update();
	static float _editDeltaHeight;
	static EDIT_TYPE _editType;
	static EDIT_HEIGHTMAP_TYPE _editHeightmapType;

};

#endif