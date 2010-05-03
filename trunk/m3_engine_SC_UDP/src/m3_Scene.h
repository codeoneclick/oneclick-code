#pragma once
#ifndef _M3_SCENE_H_
#define _M3_SCENE_H_

#include <windows.h>
#include <string>
#include <vector>
#include "m3_BattleMachine.h"
#include "m3_Heightmap.h"
#include "m3_UDPServer.h"
#include "m3_UDPClient.h"

class m3_Scene
{
private :
	m3_BattleMachine *_player;
	std::vector<m3_BattleMachine*> _enemys;
	m3_Heightmap *_map;
	Vector3d _vMousePosition3D;
	m3_UDPServer *_serverPtr;
	m3_UDPClient *_clientPtr;
	float _UpdateUnitRotationOnHeightmap(Vector3d vPosition);
public :
	void Load();
	void Update();
	void Render();
	m3_Scene();
};

#endif