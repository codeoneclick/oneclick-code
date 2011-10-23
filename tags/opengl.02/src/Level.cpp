#include "Level.h"

void Level::Load(std::string &name)
{
	for(unsigned int i = 0; i < MAP_SIZE/CHUNK_SIZE; ++i)
		for(unsigned int j = 0; j < MAP_SIZE/CHUNK_SIZE; ++j)
		{
			LevelIndex _index;
			_index.indexX = i;
			_index.indexY = j;

			LevelChunk *_levelChunk = new LevelChunk();

			_levelChunk->_index = _index;

			_levelChunk->_heightmap = new Heightmap();
			_levelChunk->_heightmap->Load(name,_index);
			
			_levelChunk->_water     = new Water();
			_levelChunk->_water->Load(name,_index);

			_levelChunk->_grass     = new Grass();
			_levelChunk->_grass->Load(name,_index);
				
			_levelContainer.push_back(_levelChunk);
		}
	LevelIndex _index;
	_index.indexX = 0;
	_index.indexY = 0;
	_mapTileSet = new Tileset();
	_mapTileSet->Load(name,_index);
}

void Level::Update(RenderTextureType _type)
{
	_mapTileSet->Update();

	std::vector<LevelChunk*>::iterator _beginIterator = _levelContainer.begin();
	std::vector<LevelChunk*>::iterator _endIterator   = _levelContainer.end();

	while(_beginIterator != _endIterator)
	{
		if(!Core::GetCamera()->IsBoundingSphereInFrustum((*_beginIterator)->_index.indexX * CHUNK_SIZE + CHUNK_SIZE/2,(*_beginIterator)->_index.indexY * CHUNK_SIZE + CHUNK_SIZE/2,CHUNK_SIZE))
		{	
			++_beginIterator;
			continue;
		}

		switch(_type)
		{
			case RENDER_SIMPLE_TEXTURE:
				(*_beginIterator)->_heightmap->Update();
				(*_beginIterator)->_water->Update();
				(*_beginIterator)->_grass->Update();
			break;
			case RENDER_REFLECTION_TEXTURE:
				(*_beginIterator)->_heightmap->Update();
				(*_beginIterator)->_grass->Update();
			break;
			case RENDER_REFRACTION_TEXTURE:
				(*_beginIterator)->_heightmap->Update();
			break;
		}
		++_beginIterator;
	}
}

void Level::Render(RenderTextureType _type)
{
	std::vector<LevelChunk*>::iterator _beginIterator = _levelContainer.begin();
	std::vector<LevelChunk*>::iterator _endIterator   = _levelContainer.end();
	
	_mapTileSet->EnableShader("multitex","multitex");
	_mapTileSet->EnableVB();
	_mapTileSet->EnableIB();	
	switch(_type)
	{
		case RENDER_SIMPLE_TEXTURE:
			_mapTileSet->SetClipPlane(0.0f);
			_mapTileSet->Render();
		break;
		case RENDER_REFLECTION_TEXTURE:
			_mapTileSet->SetClipPlane(WATER_LEVEL);
			_mapTileSet->Render();
		break;
		case RENDER_REFRACTION_TEXTURE:
			_mapTileSet->SetClipPlane(-WATER_LEVEL);
			_mapTileSet->Render();
		break;
	}
	_mapTileSet->DisableShader();

/////////////////////////////////////////////////////////////////////////////////

	if(_beginIterator != _endIterator)
	{
		(*_beginIterator)->_heightmap->EnableShader("multitex","multitex");
		(*_beginIterator)->_heightmap->EnableVB();
	}

	while(_beginIterator != _endIterator)
	{
		if(!Core::GetCamera()->IsBoundingSphereInFrustum((*_beginIterator)->_index.indexX * CHUNK_SIZE + CHUNK_SIZE/2,(*_beginIterator)->_index.indexY * CHUNK_SIZE + CHUNK_SIZE/2,CHUNK_SIZE))
		{	
			++_beginIterator;
			continue;
		}

		switch(_type)
		{
			case RENDER_SIMPLE_TEXTURE:
				(*_beginIterator)->_heightmap->EnableIB();
				(*_beginIterator)->_heightmap->SetClipPlane(0.0f);
				(*_beginIterator)->_heightmap->Render();
			break;
			case RENDER_REFLECTION_TEXTURE:
				(*_beginIterator)->_heightmap->EnableIB();
				(*_beginIterator)->_heightmap->SetClipPlane(WATER_LEVEL);
				(*_beginIterator)->_heightmap->Render();
			break;
			case RENDER_REFRACTION_TEXTURE:
				(*_beginIterator)->_heightmap->EnableIB();
				(*_beginIterator)->_heightmap->SetClipPlane(-WATER_LEVEL);
				(*_beginIterator)->_heightmap->Render();
			break;
		}
		++_beginIterator;
	}

/////////////////////////////////////////////////////////////////////////////////

	_beginIterator = _levelContainer.begin();

	if(_beginIterator != _endIterator)
	{
		(*_beginIterator)->_heightmap->DisableShader();
		(*_beginIterator)->_water->EnableShader("water","water");
		(*_beginIterator)->_water->EnableVB();
	}

	while(_beginIterator != _endIterator)
	{
		if(!Core::GetCamera()->IsBoundingSphereInFrustum((*_beginIterator)->_index.indexX * CHUNK_SIZE + CHUNK_SIZE/2,(*_beginIterator)->_index.indexY * CHUNK_SIZE + CHUNK_SIZE/2,CHUNK_SIZE))
		{	
			++_beginIterator;
			continue;
		}

		switch(_type)
		{
			case RENDER_SIMPLE_TEXTURE:
				(*_beginIterator)->_water->EnableIB();
				(*_beginIterator)->_water->Render();
			break;
		}
		++_beginIterator;
	}

/////////////////////////////////////////////////////////////////////////////////

	_beginIterator = _levelContainer.begin();

	if(_beginIterator != _endIterator)
	{
		(*_beginIterator)->_water->DisableShader();
		(*_beginIterator)->_grass->EnableShader("grass","grass");
		(*_beginIterator)->_grass->EnableVB();
	}

	while(_beginIterator != _endIterator)
	{
		if(!Core::GetCamera()->IsBoundingSphereInFrustum((*_beginIterator)->_index.indexX * CHUNK_SIZE + CHUNK_SIZE/2,(*_beginIterator)->_index.indexY * CHUNK_SIZE + CHUNK_SIZE/2,CHUNK_SIZE))
		{	
			++_beginIterator;
			continue;
		}

		switch(_type)
		{
			case RENDER_SIMPLE_TEXTURE:
				(*_beginIterator)->_grass->EnableIB();
				(*_beginIterator)->_grass->Render();
			break;
			case RENDER_REFLECTION_TEXTURE:
				(*_beginIterator)->_grass->EnableIB();
				(*_beginIterator)->_grass->Render();
			break;
		}
		++_beginIterator;
	}

	_beginIterator = _levelContainer.begin();

	if(_beginIterator != _endIterator)
	{
		(*_beginIterator)->_grass->DisableShader();
	}
}