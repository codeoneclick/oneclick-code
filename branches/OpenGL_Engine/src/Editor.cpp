#include "Editor.h"
#include "MapService.h"
#include "Utility.h"
#include "Input.h"

float				   Editor::_editDeltaHeight = 5.0f;
EDIT_TYPE			   Editor::_editType = EDIT_NONE;
EDIT_HEIGHTMAP_TYPE    Editor::_editHeightmapType = EDIT_HEIGHTMAP_SIMPLE;

void Editor::Update()
{
	if( Input::mLeftDown )
	{  
		switch(_editType)
		{
			case EDIT_HEIGHTMAP :
				_EditHeightmap();
			break;
		}
	}
}


void Editor::_EditHeightmap()
{
	_vMousePosition3D = Core::GetCamera()->vLookAt;
	float radius = 10.0f;

	static unsigned int _editInterval = 0;
	_editInterval++;
	if(_editInterval < 25)
		return;

	_editInterval = 0;
	
	float **_heightmap = Resource::MapContainer()->_heightmap;
    float height = 0.0f;
	int minIndX = (int)floor(_vMousePosition3D.x - radius);
	int minIndZ = (int)floor(_vMousePosition3D.z - radius);
	int maxIndX = (int)floor(_vMousePosition3D.x + radius);
	int maxIndZ = (int)floor(_vMousePosition3D.z + radius);

    for (int x = minIndX; x < maxIndX; x++)
            for (int z = minIndZ; z < maxIndZ; z++) 
			{
                if((x < 0) || (z < 0)) 
					continue;
				float distance = Length(Vector3d(x - _vMousePosition3D.x,0.0f,z - _vMousePosition3D.z));
                if (distance > radius)
                    continue;
                float riseCoeff = distance / radius;
                riseCoeff = 1.0f - riseCoeff*riseCoeff;
                float deltaHeight = _editDeltaHeight * riseCoeff;

                float Height =  _heightmap[x][z] + deltaHeight;
                Height = floor(Height + 0.5f);
				Resource::MapContainer()->_heightmap[x][z] = Height;
             }
	if(_editHeightmapType == EDIT_HEIGHTMAP_SMOOTH)
	{
		int vertNumber = 0;
		float middleHeight = 0;
		int CashCount = 0;
		for (int x = minIndX; x < maxIndX; x++)
                for (int z = minIndZ; z < maxIndZ; z++) {
                        if((x <= 0) || (z <= 0)) continue;
                        float leng = Length(Vector3d(x - _vMousePosition3D.x, 0.0f, z - _vMousePosition3D.z));
                        float coeff = radius - leng;
                        height = _heightmap[x][z];
                        middleHeight = 0;
                        if (coeff > 0) {
                                middleHeight = height;
                                middleHeight += _heightmap[x-1][z];
                                middleHeight += _heightmap[x+1][z];
                                middleHeight += _heightmap[x-1][z-1];
                                middleHeight += _heightmap[x][z-1];
                                middleHeight += _heightmap[x+1][z-1];
                                middleHeight += _heightmap[x-1][z+1];
                                middleHeight += _heightmap[x][z+1];
                                middleHeight += _heightmap[x+1][z+1];
                                height = middleHeight / 9.0f;
                                height = floor(height + 0.5f);
                        }
                        Resource::MapContainer()->_heightmap[x][z] = height;
                }
	}
	VertexData *_vertexDataPtr = NULL;
	unsigned int _vertexBufferIndex = 0;

	VB::glBindVB( GL_ARRAY_BUFFER_ARB,  Resource::MapContainer()->_heightmapVB->vertexBufferId );	
	_vertexDataPtr = (VertexData*) VB::glLockVB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	for(unsigned int i = 0; i < MAP_SIZE; ++i )
				for(unsigned int j = 0; j < MAP_SIZE; ++j )
				{
					_vertexDataPtr[_vertexBufferIndex].vPosition.y = _heightmap[i][j] * HEIGHTMAP_LEVEL + 1.0f;
					++_vertexBufferIndex;
				}
	VB::glUnlockVB(GL_ARRAY_BUFFER_ARB);
	VB::glBindVB( GL_ARRAY_BUFFER_ARB, 0 );	
}