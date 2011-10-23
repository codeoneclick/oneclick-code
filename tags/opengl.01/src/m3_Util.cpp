#include "m3_Util.h"
#pragma comment(lib, "winmm.lib")

Vector3d m3_Util::GetMousePositionIn3D(int x, int y)
{
	GLint viewport[4];
	GLdouble mdView[16];
	GLdouble mdProjection[16];
	GLfloat  windowX, windowY, windowZ;
	GLdouble positionX, positionY, positionZ;

	for(uint32 i = 0; i < 16; ++i)
	{
		mdView[i]  = m3_Core::GetCamera()->mView.m[i];
		mdProjection[i] = m3_Core::GetCamera()->mProjection.m[i];
	}

	glGetIntegerv( GL_VIEWPORT, viewport );

	windowX = (float)x;
	windowY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(windowY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &windowZ );

	gluUnProject( windowX, windowY, windowZ, mdView,  mdProjection, viewport, &positionX, &positionY, &positionZ);

	return Vector3d(positionX, positionY, positionZ);
}

float m3_Util::GetRotationFromDirection(Vector3d vPosition_01, Vector3d vPosition_02)
{
	float angleX = (vPosition_02.x - vPosition_01.x) / sqrt(pow(vPosition_02.x - vPosition_01.x, 2) + pow(vPosition_02.z - vPosition_01.z, 2));
	float angleZ = 90.0f * (vPosition_02.z - vPosition_01.z) / sqrt(pow(vPosition_02.x - vPosition_01.x, 2) + pow(vPosition_02.z - vPosition_01.z, 2));
	float angleY = 0.0f;
	if (angleX >= 0) 
		angleY = angleZ;
	if (angleX < 0) 
		angleY = 90.0f + (90.0f - angleZ);
	return  -(float) angleY *  0.0174532925f;
}

float m3_Util::GetRotationFromNormal(Vector3d vPosition_01, Vector3d vPosition_02,Vector3d vPosition_03)
{
	float fVectorLength_01 = sqrt(pow(vPosition_02.x - vPosition_01.x,2) + pow(vPosition_02.y - vPosition_01.y,2) + pow(vPosition_02.z - vPosition_01.z,2));
	float fVectorLength_02 = sqrt(pow(vPosition_03.x - vPosition_01.x,2) + pow(vPosition_03.y - vPosition_01.y,2) + pow(vPosition_03.z - vPosition_01.z,2));
	float fScalar = (vPosition_02.x - vPosition_01.x)*(vPosition_03.x - vPosition_01.x) + (vPosition_02.y - vPosition_01.y)*(vPosition_03.y - vPosition_01.y) + (vPosition_02.z - vPosition_01.z)*(vPosition_03.z - vPosition_01.z);
	return fScalar / (fVectorLength_01 * fVectorLength_02);
}

float m3_Util::GetRandomFromRange(float min, float max)
{
	Sleep(1);
	srand((unsigned)GetTickCount());
	float range = (max - min) + 1.0f;
	for(unsigned int i = 0; i < 64; ++i)
	{
		srand((unsigned)timeGetTime());
		rand();
	}
	return min + float(range*rand()/(RAND_MAX + 1.0f)); 
}