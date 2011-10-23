#include "Scene.h"

Scene::Scene()
{
	_player = NULL;
	_level    = NULL;
}

void Scene::Load()
{
	_player = new Mesh();
	_player->Load("Content\\models\\Tank.3ds","Tank.3ds");
	_player->vScale = Vector3d(0.03f,0.03f,0.03f);

	std::string name = "Content\\maps\\map.raw";
	_level = new Level();
	_level->Load(name);

	_editor = new Editor();
}

void Scene::Update(RenderTextureType _type)
{
	switch(_type)
	{
	    case RENDER_SIMPLE_TEXTURE:
			_level->Update(_type);
			Core::GetCamera()->vLookAt.y = Utility::GetHeightFromMapLayer_01(Core::GetCamera()->vLookAt.x,Core::GetCamera()->vLookAt.z);
			_player->vPosition = Core::GetCamera()->vLookAt;
			Core::GetCamera()->vPosition.y = Utility::GetHeightFromMapLayer_01(Core::GetCamera()->vPosition.x,Core::GetCamera()->vPosition.z) + 8.0f;
			_player->vRotation.y = Core::GetCamera()->vRotation.y - HALF_PI;
			_player->vRotation.z = Utility::GetRotationOnHeightMap(_player->vPosition).z;
			_player->vRotation.x = -Utility::GetRotationOnHeightMap(_player->vPosition).x;
		break;
		case RENDER_REFLECTION_TEXTURE:
			_level->Update(_type);
		break;
		case RENDER_REFRACTION_TEXTURE:
			_level->Update(_type);
		break;
	}

	_editor->Update();
}

void Scene::Render(RenderTextureType _type)
{
	switch(_type)
	{
	    case RENDER_SIMPLE_TEXTURE:
			_level->Render(_type);
			//_grass->Render();
			_player->Update();
			_player->RenderChunk("_basis");

			_player->Update();
			_player->RenderChunk("_track_01");
			_player->Update();
			_player->RenderChunk("_track_02");

			_player->Update();
			_player->RenderChunk("_turret");
		break;
		case RENDER_REFLECTION_TEXTURE:
			_level->Render(_type);
			//_grass->Render();
		break;
		case RENDER_REFRACTION_TEXTURE:
			_level->Render(_type);
		break;
	}
}