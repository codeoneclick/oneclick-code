#include "EnviromentController.h"
#include "Resource.h"
#include "RenderController.h"

using namespace Enviroment;

EnviromentController::EnviromentController()
{
	_camera = NULL;
}

void EnviromentController::Create()
{
	_camera = new Camera();
	m_Island = new CSoaringIsland();
	m_Island->Load("Content\\maps\\Kbsd_Heightmap_Example.raw");
	_mesh = new CModel();
	//_mesh->Load("Content\\models\\tank.3ds");
	_mesh->m_vRotation.x = -1.57f;
	_mesh->m_vScale = math::Vector3d(0.1f,0.1f,0.1f);

	//_ocean = new COcean();
	//_ocean->Load("none");
	CResource::Enable();
	//_ocean->vPosition.y = -128.0f;
	CDummy *a = new CDummy();
}

void EnviromentController::Update(DWORD time)
{
	//if(time == 0)
    _camera->Update();
	m_Island->Update();
	//_ocean->Update();
	//_mesh->Update();
	CResource::WorkInMainTread();
}

void EnviromentController::Render()
{
	m_Island->Render();
	//_mesh->Render();
}