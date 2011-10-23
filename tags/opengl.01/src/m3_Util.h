#pragma once
#ifndef _M3_UTIL_H_
#define _M3_UTIL_H_

#include "m3_Core.h"

class m3_Util
{
  public :
	static Vector3d GetMousePositionIn3D(int x, int y);
	static float GetRotationFromDirection(Vector3d vPosition_01, Vector3d vPosition_02);
	static float GetRotationFromNormal(Vector3d vPosition_01, Vector3d vPosition_02,Vector3d vPosition_03);
	static float GetRandomFromRange(float min, float max);  
};

#endif