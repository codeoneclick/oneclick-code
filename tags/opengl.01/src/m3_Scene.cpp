#include "m3_Scene.h"

m3_Scene::m3_Scene()
{
	_player = NULL;
	_map    = NULL;
	_vMousePosition3D = Vector3d(0.0f,0.0f,0.0f);
	_server_ptr = new server_udp();
	_client_ptr = new client_udp();
}

void m3_Scene::Load()
{
	_player = new m3_BattleMachine();
	_player->Load("Content\\models\\tank.3ds","tank.3ds");
	_player->vScale = Vector3d(0.05f,0.05f,0.05f);

	_map = new m3_Heightmap();
	_map->Load("Content\\maps\\map.raw");

	for(uint32 i = 0; i < 4; ++i)
	{
		_enemys.push_back(new m3_BattleMachine());
		(* --_enemys.end())->Load("Content\\models\\tank.3ds","tank.3ds");
		(* --_enemys.end())->vScale = Vector3d(0.05f,0.05f,0.05f);
		float fRandPositionX = m3_Util::GetRandomFromRange(16, 192);
		float fRandPositionZ = m3_Util::GetRandomFromRange(64, 256);
		float fPositonY = _map->GetHeight(fRandPositionX,fRandPositionZ);
		(* --_enemys.end())->vPosition = Vector3d(fRandPositionX,fPositonY,fRandPositionZ);
		(* --_enemys.end())->isAi = true;
	}

	_server_ptr->init();
	_client_ptr->init();
}

void m3_Scene::Update()
{
	if(m3_Input::ePressStartServer && !_server_ptr->is_enable())
	{
		_server_ptr->enable();
	}

	if(m3_Input::ePressStartClient && !_client_ptr->is_enable())
	{
		_client_ptr->enable();
	}

	//if(_serverPtr->IsAtWork())
	//	_serverPtr->Update();
	static DWORD last_time = 0;
	DWORD current_time = GetTickCount();

	if(_client_ptr->is_enable() && (current_time - last_time) > 1 )
	{
		last_time = current_time;
		//message_unit_aspect message;
		message_ext message;
		message.header.message_type = 1024;
		message.header.message_size = 12;
		message.data = NULL;
		//memcpy(&_player->vPosition,message.data,sizeof(Vector3d));
		message.data = (char*)&_player->vPosition;
		Vector3d *temp = (Vector3d*)message.data;
		//message.vPosition = _player->vPosition;
		_client_ptr->send_message(&message);
//	_clientPtr->Update();
	}

	_map->Update();

	m3_Core::GetCamera()->vLookAt.y = _map->GetHeight(m3_Core::GetCamera()->vLookAt.x,m3_Core::GetCamera()->vLookAt.z);
	_player->vPosition = m3_Core::GetCamera()->vLookAt;
	_player->vRotation.y = m3_Core::GetCamera()->vRotation.y - 1.57f;
	_player->vRotation.z = _UpdateUnitRotationOnHeightmap(_player->vPosition);
	_player->fTurretRotation = m3_Util::GetRotationFromDirection(_player->vPosition,_vMousePosition3D);

	std::vector<m3_BattleMachine*>::iterator _enemysIterator = _enemys.begin();
	while(_enemysIterator != _enemys.end())
	{
		(*_enemysIterator)->aiBlock->SetMainPosition((*_enemysIterator)->vPosition);
		(*_enemysIterator)->aiBlock->SetTargetPosition(_player->vPosition);
		(*_enemysIterator)->aiBlock->UpdateAI();
		Vector3d vNewPosition = (*_enemysIterator)->aiBlock->GetMainPosition();
		(*_enemysIterator)->vRotation.y = m3_Util::GetRotationFromDirection((*_enemysIterator)->vPosition,(*_enemysIterator)->aiBlock->GetMovePosition());
		(*_enemysIterator)->vPosition = Vector3d(vNewPosition.x,_map->GetHeight(vNewPosition.x,vNewPosition.z),vNewPosition.z);
		
		(*_enemysIterator)->vRotation.z = _UpdateUnitRotationOnHeightmap((*_enemysIterator)->vPosition);
		(*_enemysIterator)->fTurretRotation = m3_Util::GetRotationFromDirection((*_enemysIterator)->vPosition,_player->vPosition);
		++_enemysIterator;
	}
}

float m3_Scene::_UpdateUnitRotationOnHeightmap(Vector3d vPosition)
{
	Vector3d vPoint_01 = vPosition;
	Vector3d vPoint_02 = Vector3d(vPosition.x, vPosition.y + 16.0f, vPosition.z);
	Vector3d vPoint_03 = Vector3d(vPosition.x + 1.0f,_map->GetHeight(vPosition.x + 1.0f,vPosition.z),vPosition.z);

	float fAngle_01 = m3_Util::GetRotationFromNormal(vPoint_01, vPoint_02, vPoint_03);

	return -acos(fAngle_01) + 1.57f;
}

void m3_Scene::Render()
{
	_map->Render();
	_player->Draw();

	std::vector<m3_BattleMachine*>::iterator _enemysIterator = _enemys.begin();
	while(_enemysIterator != _enemys.end())
	{
		(*_enemysIterator)->Draw();
		++_enemysIterator;
	}
	_vMousePosition3D = m3_Util::GetMousePositionIn3D(m3_Input::mCurrentPosition.x,m3_Input::mCurrentPosition.y);
}