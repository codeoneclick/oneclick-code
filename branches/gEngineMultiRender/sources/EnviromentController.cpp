#include "EnviromentController.h"
#include "Resource.h"

using namespace Enviroment;

EnviromentController::EnviromentController()
{
	_camera = NULL;
}

void EnviromentController::Create()
{
	_camera = new Camera();
	_landscape = new Landscape();
	_landscape->Load("Content\\maps\\map.raw");
	_mesh = new CModel();
	_mesh->Load("Content\\models\\tank.3ds");
	_mesh->vRotation.x = -1.57f;
	_mesh->vScale = math::Vector3d(0.1f,0.1f,0.1f);

	_ocean = new COcean();
	_ocean->Load("none");
	Resource::Enable();
	//_ocean->vPosition.y = -128.0f;
}

void EnviromentController::Update(DWORD time)
{
	//if(time == 0)
    _camera->Update();
	_landscape->Update();
	//_ocean->Update();
	//_mesh->Update();
	Resource::GetMeshControllerInstance()->Update();
	Resource::WorkInMainTread();
}

void EnviromentController::Render(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case Video::CRenderController::ERenderTexture::SCREEN_TEXTURE :
		{
			//_mesh->Render();
			//_ocean->Render();
			_landscape->Render();
		}
		break;
		case Video::CRenderController::ERenderTexture::REFLECTION_TEXTURE :
		{
			_landscape->Render();
		}
		break;
		case Video::CRenderController::ERenderTexture::REFRACTION_TEXTURE :
		{
			_landscape->Render();
		}
		break;
	}
}
