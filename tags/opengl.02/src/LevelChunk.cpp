#include "LevelChunk.h"

LevelChunk::LevelChunk()
{
	_heightmap = NULL;
	_grass = NULL;
	_water = NULL;

	_index.indexX = 0;
	_index.indexY = 0;
}

void LevelChunk::Load(VertexBufferPtrExt *_heightmapVertexData,std::string &name,LevelIndex _indexValue)
{
	_index = _indexValue;
	
	_heightmap = new Heightmap();
	_heightmap->Load(name,_heightmapVertexData,_indexValue);

	_water = new Water();
	_water->Load(name,_indexValue);

	_grass = new Grass();
	_grass->Load(name,_indexValue);
}

void LevelChunk::Update(RenderTextureType _renderType)
{
	switch(_renderType)
	{
	    case RENDER_SIMPLE_TEXTURE:
			_heightmap->Update();
			_grass->Update();
			_water->Update();
		break;
		case RENDER_REFLECTION_TEXTURE:
			_heightmap->Update();
			_grass->Update();
		break;
		case RENDER_REFRACTION_TEXTURE:
			_heightmap->Update();
		break;
	}
}

void LevelChunk::Render(RenderTextureType _renderType)
{
	switch(_renderType)
	{
	    case RENDER_SIMPLE_TEXTURE:
			_heightmap->SetClipPlane(0.0f);
			_heightmap->Render();
			_grass->Render();
			_water->Render();
		break;
		case RENDER_REFLECTION_TEXTURE:
			_heightmap->SetClipPlane(11.0f);
			_heightmap->Render();
			_grass->Render();
		break;
		case RENDER_REFRACTION_TEXTURE:
			_heightmap->SetClipPlane(-11.0f);
			_heightmap->Render();
		break;
	}
}