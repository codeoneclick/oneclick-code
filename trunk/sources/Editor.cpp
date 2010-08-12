#include "Editor.h"
#include "Game.h"
#include "Math.h"

using namespace edit;

unsigned int Editor::_currentTileType = 0;
math::vector::Vector3d  Editor::_mouse3dPosition = math::vector::Vector3d(0.0f,0.0f,0.0f);
type::VertexBuffer  *Editor::_landscapeVertexBufferPtr = NULL;
TileType Editor::_tileType[16][16];
eTyleType Editor::_tileMerge[16][16];
char Editor::levelMap[256][256];
tileLey Editor::tile_map[256][256];


void Editor::InitTileType()
{
	for(int i = 0; i < 256; ++i)
		for(int j = 0; j < 256; ++j)
		{
			levelMap[i][j] = LEVEL_01;
			tile_map[i][j].tileType = T_C_02;
			tile_map[i][j].leyerType = LEVEL_01;
		}


	unsigned int tileCount = 16;
	unsigned int tileSetTypeIndex = 0;
	for( unsigned int i = 0; i < tileCount; ++i)
	{
		float texCoordOffsetU = 1.0f / tileCount * i;
		float texCoordOffsetD = 1.0f / tileCount * ( i + 1 );

		for(unsigned int j = 0; j < tileCount; ++j)
		{
			float texOffsetLeft = 1.0f / tileCount * j;
			float texOffsetRight = 1.0f / tileCount * (j + 1);
			_tileType[tileSetTypeIndex][j].vTexCoord[0] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetU);
			_tileType[tileSetTypeIndex][j].vTexCoord[1] = math::vector::Vector2d(texOffsetRight,texCoordOffsetU);
			_tileType[tileSetTypeIndex][j].vTexCoord[2] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetD);
			_tileType[tileSetTypeIndex][j].vTexCoord[3] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetD);
			_tileType[tileSetTypeIndex][j].vTexCoord[4] = math::vector::Vector2d(texOffsetRight,texCoordOffsetU);
			_tileType[tileSetTypeIndex][j].vTexCoord[5] = math::vector::Vector2d(texOffsetRight,texCoordOffsetD);
		}

		tileSetTypeIndex++;
		unsigned int tileElementIndex = 0;
		for(int j = (16 - 1); j >= 0; j--)
		{
			float texOffsetLeft = 1.0f / tileCount * j;
			float texOffsetRight = 1.0f / tileCount * (j + 1);

			if( j == T_L  || j == T_R )
			{
				float texCoordTemp = texOffsetRight;
				texOffsetRight = texOffsetLeft;
				texOffsetLeft = texCoordTemp;
			}

			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[0] = math::vector::Vector2d(texOffsetRight,texCoordOffsetU);
			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[1] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetU);
			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[2] = math::vector::Vector2d(texOffsetRight,texCoordOffsetD);
			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[3] = math::vector::Vector2d(texOffsetRight,texCoordOffsetD);
			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[4] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetU);
			_tileType[tileSetTypeIndex][tileElementIndex].vTexCoord[5] = math::vector::Vector2d(texOffsetLeft,texCoordOffsetD);
			tileElementIndex++;
		}
		tileSetTypeIndex++;
	}
}

void Editor::_SetTile(int startPointIndex, type::VertexData * _vPtr, eTyleType tileType)
{
	/*tileType = _tileMerge[tileType][_vPtr[startPointIndex].vExtValue];//_CheckTile(startPointIndex,_vPtr,tileType);
	for(int i = 0; i < 6; ++i)
	{
		_vPtr[startPointIndex + i].vTexCoord = _tileType[tileType].vTexCoord[i];
		_vPtr[startPointIndex + i].vExtValue = tileType;
	}*/
}

eTyleType Editor::_CheckTile(int startPointIndex, type::VertexData * _vPtr, eTyleType tileType)
{
	return tileType;
}

/*
0,1 - C
2 - LD
3 - RD
4 - LU
5 - RU
6 - L
7 - R
8 - D
9 - U
*/

void Editor::_EditTile()
{
	/*int indexX = _mouse3dPosition.x/4.0f;
	int indexZ = _mouse3dPosition.z/4.0f;

	extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB,_landscapeVertexBufferPtr->vertexBufferAddr);
	type::VertexData *_vertexData = (type::VertexData*)extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
	int arrayIndex = indexX * 6 * 255 + indexZ * 6;
	
	_SetTile(arrayIndex,_vertexData, T_C_02);

	_SetTile(arrayIndex - 6,_vertexData, T_D);                           
	_SetTile(arrayIndex + 6,_vertexData, T_U);						    

	_SetTile(((indexX - 1) * 6 * 255 + indexZ * 6),_vertexData, T_L);    
	_SetTile(((indexX + 1) * 6 * 255 + indexZ * 6),_vertexData, T_R);     

	_SetTile(((indexX - 1) * 6 * 255 + (indexZ - 1) * 6),_vertexData, T_LD);
	_SetTile(((indexX + 1) * 6 * 255 + (indexZ + 1) * 6),_vertexData, T_RU);

	_SetTile(((indexX - 1) * 6 * 255 + (indexZ + 1) * 6),_vertexData, T_LU);
	_SetTile(((indexX + 1) * 6 * 255 + (indexZ - 1) * 6),_vertexData, T_RD);
	
	extension::VBExtension::glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);*/
}

void Editor::Update(DWORD time)
{
	/*if(core::Input::mouseL)
	{
		_Get3DMousePosition(core::Input::currentMousePosition.x,core::Input::currentMousePosition.y);
		if(_landscapeVertexBufferPtr == NULL)
		{
		//	_landscapeVertexBufferPtr = Game::GetEnviromentControllerInstance()->GetLandscapeInstance()->GetVertexBufferAddr();
		}
		//_EditTile();
		_Tiling(_mouse3dPosition.x/4.0f,_mouse3dPosition.z/4.0f,LEVEL_03);
		
		extension::VBExtension::glBindBufferARB( GL_ARRAY_BUFFER_ARB,_landscapeVertexBufferPtr->vertexBufferAddr);
		type::VertexData *_vertexData = (type::VertexData*)extension::VBExtension::glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);
		for(int i = 0; i < 255; ++i)
			for(int j = 0; j < 255; ++j)
			{
				int index = i * 6 * 255 + j * 6;
				for(int k = 0; k < 6; ++k)
				{
					_vertexData[index + k].vTexCoord = _tileType[tile_map[i][j].leyerType][tile_map[i][j].tileType].vTexCoord[k];
				}
			}
		extension::VBExtension::glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
	}*/
}

void Editor::_Get3DMousePosition(int x, int y)
{
	GLint viewport[4];
	GLdouble mdView[16];
	GLdouble mdProjection[16];
	GLfloat  windowX, windowY, windowZ;
	GLdouble positionX, positionY, positionZ;

	for(unsigned int i = 0; i < 16; ++i)
	{
		mdView[i] = Game::GetEnviromentControllerInstance()->GetCameraInstance()->mView.m[i];
		mdProjection[i] = Game::GetEnviromentControllerInstance()->GetCameraInstance()->mProjection.m[i];
	}

	glGetIntegerv( GL_VIEWPORT, viewport );

	windowX = (float)x;
	windowY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(windowY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &windowZ );

	gluUnProject( windowX, windowY, windowZ, mdView,  mdProjection, viewport, &positionX, &positionY, &positionZ);
	_mouse3dPosition.x = positionX;
	_mouse3dPosition.y = positionY;
	_mouse3dPosition.z = positionZ;
}

void Editor::SetTileset(int x, int y,char brushLevel)
{
	char tile_00 = levelMap[x][y-1];
	char tile_01 = levelMap[x+1][y-1];
	char tile_02 = levelMap[x+1][y];
	char tile_03 = levelMap[x+1][y+1];
	char tile_04 = levelMap[x][y+1];
	char tile_05 = levelMap[x-1][y+1];
	char tile_06 = levelMap[x-1][y];
	char tile_07 = levelMap[x-1][y-1];

	if(tile_00!=brushLevel&&tile_01!=brushLevel&&tile_02!=brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_RD);
	if(tile_02!=brushLevel&&tile_03!=brushLevel&&tile_04!=brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_RU);
	if(tile_04!=brushLevel&&tile_05!=brushLevel&&tile_06!=brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_LU);
	if(tile_06!=brushLevel&&tile_07!=brushLevel&&tile_00!=brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_LD);
	//------------------------------------2
	if(tile_00!=brushLevel&&tile_01!=brushLevel&&tile_02==brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_D);
	if(tile_02==brushLevel&&tile_03!=brushLevel&&tile_04!=brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_U);
	if(tile_04!=brushLevel&&tile_05!=brushLevel&&tile_06==brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_U);
	if(tile_06==brushLevel&&tile_07!=brushLevel&&tile_00!=brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_D);
	//------------------------------------3
	if(tile_00==brushLevel&&tile_01!=brushLevel&&tile_02!=brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_R);
	if(tile_02!=brushLevel&&tile_03!=brushLevel&&tile_04==brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_R);
	if(tile_04==brushLevel&&tile_05!=brushLevel&&tile_06!=brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_L);
	if(tile_06!=brushLevel&&tile_07!=brushLevel&&tile_00==brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_L);
	//------------------------------------4
	if(tile_00!=brushLevel&&tile_01==brushLevel&&tile_02!=brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_DIAG_01);
	if(tile_02!=brushLevel&&tile_03==brushLevel&&tile_04!=brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_DIAG_02);
	if(tile_04!=brushLevel&&tile_05==brushLevel&&tile_06!=brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_DIAG_01);
	if(tile_06!=brushLevel&&tile_07==brushLevel&&tile_00!=brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_DIAG_02);
	//------------------------------------5
	if(tile_00!=brushLevel&&tile_01==brushLevel&&tile_02==brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_LD_EXT);
	if(tile_02!=brushLevel&&tile_03==brushLevel&&tile_04==brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_RD_EXT);
	if(tile_04!=brushLevel&&tile_05==brushLevel&&tile_06==brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_RU_EXT);
	if(tile_06!=brushLevel&&tile_07==brushLevel&&tile_00==brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_LU_EXT);
	//------------------------------------6
	if(tile_00==brushLevel&&tile_01==brushLevel&&tile_02!=brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_RU_EXT);
	if(tile_02==brushLevel&&tile_03==brushLevel&&tile_04!=brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_LU_EXT);
	if(tile_04==brushLevel&&tile_05==brushLevel&&tile_06!=brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_LD_EXT);
	if(tile_06==brushLevel&&tile_07==brushLevel&&tile_00!=brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_RD_EXT);
	//------------------------------------7
	if(tile_00==brushLevel&&tile_01!=brushLevel&&tile_02==brushLevel)if(tile_00<brushLevel)SetTile(x,y-1,brushLevel,T_RD_EXT);
	if(tile_02==brushLevel&&tile_03!=brushLevel&&tile_04==brushLevel)if(tile_02<brushLevel)SetTile(x,y,brushLevel,T_RU_EXT);
	if(tile_04==brushLevel&&tile_05!=brushLevel&&tile_06==brushLevel)if(tile_04<brushLevel)SetTile(x-1,y,brushLevel,T_LU_EXT);
	if(tile_06==brushLevel&&tile_07!=brushLevel&&tile_00==brushLevel)if(tile_06<brushLevel)SetTile(x-1,y-1,brushLevel,T_LD_EXT);
	//------------------------------------

	if(tile_00==brushLevel&&tile_01==brushLevel&&tile_02==brushLevel)SetTile(x,y-1,brushLevel,T_C_02);
	if(tile_02==brushLevel&&tile_03==brushLevel&&tile_04==brushLevel)SetTile(x,y,brushLevel,T_C_02);
	if(tile_04==brushLevel&&tile_05==brushLevel&&tile_06==brushLevel)SetTile(x-1,y,brushLevel,T_C_02);
	if(tile_06==brushLevel&&tile_07==brushLevel&&tile_00==brushLevel)SetTile(x-1,y-1,brushLevel,T_C_02);
}

void Editor::SetTile(int x,int y,char brushLevel, eTyleType tileType)
{
	tile_map[x][y].tileType = tileType;
	tile_map[x][y].leyerType = brushLevel;
}

void Editor::_Tiling(int x, int y, TILE_TEXTURE_LEVEL brushLevel)
{
	levelMap[x][y] = brushLevel;
	SetTileset(x,y,brushLevel);
	int mapWidth = 256;
	int mapHeight = 256;
	for(int indexLevel_01 = 1; indexLevel_01 < LEVEL_MAX; indexLevel_01++)
	{
		x--;
		y--;
		for(int indexLevel_02 = 0; indexLevel_02 < indexLevel_01 * 2; indexLevel_02++)
		{
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
			{
				char currentLevel = levelMap[x][y];
				if(currentLevel > brushLevel)
				{
					int incLevel = indexLevel_01 + brushLevel;
					if(currentLevel > incLevel && incLevel < LEVEL_MAX)
						levelMap[x][y] = incLevel;
				}
				if(currentLevel < brushLevel)
				{
					int decLevel = brushLevel - indexLevel_01;
					if(currentLevel < decLevel && decLevel >-1 )
						levelMap[x][y] = decLevel;
				}
				SetTileset(x,y,currentLevel);		
			}x++;
		}
		for(int indexLevel_02 = 0; indexLevel_02 < indexLevel_01*2; indexLevel_02++)
		{
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
			{
				char currentLevel = levelMap[x][y];
				if(currentLevel > brushLevel)
				{
					int incLevel = indexLevel_01 + brushLevel;
					if( currentLevel > incLevel && incLevel < LEVEL_MAX)
						levelMap[x][y] = incLevel;
				}
				if(currentLevel < brushLevel)
				{
					int decLevel = brushLevel - indexLevel_01;
					if( currentLevel < decLevel && decLevel > -1)
						levelMap[x][y] = decLevel;
				}
				SetTileset(x,y,currentLevel);
			}y++;
		}
		for(int indexLevel_02 = 0; indexLevel_02 < indexLevel_01*2; indexLevel_02++)
		{
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
			{
				char currentLevel = levelMap[x][y];
				if(currentLevel > brushLevel)
				{
					int incLevel = indexLevel_01 + brushLevel;
					if( currentLevel > incLevel && incLevel < LEVEL_MAX)
						levelMap[x][y] = incLevel;
				}
				if(currentLevel < brushLevel)
				{
					int decLevel = brushLevel - indexLevel_01;
					if( currentLevel < decLevel && decLevel > -1)
						levelMap[x][y] = decLevel;
				}
				SetTileset(x,y,currentLevel);

			}x--;
		}
				for(int indexLevel_02 = 0; indexLevel_02 < indexLevel_01*2; indexLevel_02++)
		{
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
			{
				char currentLevel = levelMap[x][y];
				if(currentLevel > brushLevel)
				{
					int incLevel = indexLevel_01 + brushLevel;
					if( currentLevel > incLevel && incLevel < LEVEL_MAX)
						levelMap[x][y] = incLevel;
				}
				if(currentLevel < brushLevel)
				{
					int decLevel = brushLevel - indexLevel_01;
					if( currentLevel < decLevel && decLevel > -1)
						levelMap[x][y] = decLevel;
				}
				SetTileset(x,y,currentLevel);
			}y--;
		}
	}
}