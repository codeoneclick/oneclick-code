#include "Utility.h"
#pragma comment(lib, "winmm.lib")

Vector3d Utility::GetMousePositionIn3D(int x, int y)
{
	GLint viewport[4];
	GLdouble mdView[16];
	GLdouble mdProjection[16];
	GLfloat  windowX, windowY, windowZ;
	GLdouble positionX, positionY, positionZ;

	for(unsigned int i = 0; i < 16; ++i)
	{
		mdView[i]  = Core::GetCamera()->mView.m[i];
		mdProjection[i] = Core::GetCamera()->mProjection.m[i];
	}

	glGetIntegerv( GL_VIEWPORT, viewport );

	windowX = (float)x;
	windowY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(windowY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &windowZ );

	gluUnProject( windowX, windowY, windowZ, mdView,  mdProjection, viewport, &positionX, &positionY, &positionZ);

	return Vector3d(positionX, positionY, positionZ);
}

float Utility::GetRotationFromDirection(Vector3d vPosition_01, Vector3d vPosition_02)
{
	float fVectorLength = sqrt(pow(vPosition_02.x - vPosition_01.x, 2) + pow(vPosition_02.z - vPosition_01.z, 2));
	float angleX = PI*(vPosition_02.x - vPosition_01.x) / fVectorLength;
	float angleZ = PI*(vPosition_02.z - vPosition_01.z) / fVectorLength;
	float angleY = 0.0f;
	if (angleX > 0) 
		angleY = angleZ/2.0f;
	if (angleX < 0) 
		angleY = -angleZ/2.0f - PI;
	return  -angleY;
}

float Utility::GetRotationFromNormal(Vector3d vPosition_01, Vector3d vPosition_02,Vector3d vPosition_03)
{
	float fVectorLength_01 = sqrt(pow(vPosition_02.x - vPosition_01.x,2) + pow(vPosition_02.y - vPosition_01.y,2) + pow(vPosition_02.z - vPosition_01.z,2));
	float fVectorLength_02 = sqrt(pow(vPosition_03.x - vPosition_01.x,2) + pow(vPosition_03.y - vPosition_01.y,2) + pow(vPosition_03.z - vPosition_01.z,2));
	float fScalar = (vPosition_02.x - vPosition_01.x)*(vPosition_03.x - vPosition_01.x) + (vPosition_02.y - vPosition_01.y)*(vPosition_03.y - vPosition_01.y) + (vPosition_02.z - vPosition_01.z)*(vPosition_03.z - vPosition_01.z);
	return fScalar / (fVectorLength_01 * fVectorLength_02);
}

float Utility::GetRandomFromRange(float min, float max)
{
	float range = (max - min) + 1.0f;
	return min + float(range*rand()/(RAND_MAX + 1.0f)); 
}

float Utility::GetHeightFromMapLayer_01(float x, float z)
{
    int roundPositionX = (int) x;
    int roundPositionZ = (int) z;

    float remainPositionX = x - roundPositionX;
    float remainPositionZ = z - roundPositionZ;

    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (MAP_SIZE - 1)) || (roundPositionZ > (MAP_SIZE - 1)))
       return 0.0f;
        
	float height_11 = Resource::MapContainer()->_heightmap[roundPositionX][roundPositionZ]*HEIGHTMAP_LEVEL;
    float height_12 = Resource::MapContainer()->_heightmap[roundPositionX][roundPositionZ +1]*HEIGHTMAP_LEVEL;
    float height_21 = Resource::MapContainer()->_heightmap[roundPositionX + 1][roundPositionZ]*HEIGHTMAP_LEVEL;
    float height_22 = Resource::MapContainer()->_heightmap[roundPositionX + 1][roundPositionZ + 1]*HEIGHTMAP_LEVEL;
    float mainHeight;

    if( remainPositionX > remainPositionZ )
        {
                mainHeight = height_11 + (height_22 - height_21)*remainPositionZ + (height_21 - height_11)*remainPositionX;
        }
        else
        {
                mainHeight = height_11 + (height_22 - height_12)*remainPositionX + (height_12 - height_11)*remainPositionZ;
        }

        float height = (1 - remainPositionX) * ((1 - remainPositionZ) * height_11 + remainPositionZ * height_12) + remainPositionX * ((1 - remainPositionZ) * height_21 + remainPositionZ * height_22);
        return height;
}

Vector3d Utility::GetRotationOnHeightMap(Vector3d vPosition)
{
	Vector3d vPoint_01 = vPosition;
	Vector3d vPoint_02 = Vector3d(vPosition.x, vPosition.y + 16.0f, vPosition.z);
	Vector3d vPoint_03 = Vector3d(vPosition.x + 1.0f, GetHeightFromMapLayer_01(vPosition.x + 1.0f,vPosition.z),vPosition.z);
	Vector3d vPoint_04 = Vector3d(vPosition.x, GetHeightFromMapLayer_01(vPosition.x,vPosition.z + 1.0f),vPosition.z + 1.0f);

	float fAngle_01 = GetRotationFromNormal(vPoint_01, vPoint_02, vPoint_03);
	float fAngle_02 = GetRotationFromNormal(vPoint_01, vPoint_02, vPoint_04);

	return Vector3d(-acos(fAngle_02) + HALF_PI,0.0f,-acos(fAngle_01) + HALF_PI);
}