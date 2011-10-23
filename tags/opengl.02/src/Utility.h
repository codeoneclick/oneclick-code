#ifndef _UTILITY_H_
#define _UTILITY_H_

#define PI 3.14f
#define HALF_PI 1.57f
#define TO_PI_VALUE 0.0174532925f

#include "Core.h"

class Utility
{
  public :
	static Vector3d GetMousePositionIn3D(int x, int y);
	static float GetRotationFromDirection(Vector3d vPosition_01, Vector3d vPosition_02);
	static float GetRotationFromNormal(Vector3d vPosition_01, Vector3d vPosition_02,Vector3d vPosition_03);
	static float GetRandomFromRange(float min, float max);  
	static float GetHeightFromMapLayer_01(float x, float z);
	static float GetHeightFromMapLayer_02(float x, float z);
	static Vector3d  GetRotationOnHeightMap(Vector3d vPosition);
};

#endif