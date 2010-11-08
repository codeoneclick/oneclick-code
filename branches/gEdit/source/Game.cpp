#include "Game.h"
#include "Render.h"
#include "RenderController.h"
#include "Core/CGlobal.h"

Enviroment::EnviromentController* Game::_enviromentController = NULL;

Game::Game()
{

}

bool Game::Create()
{
	Core::CGlobal::GetDevice();
	_enviromentController = new Enviroment::EnviromentController();
	_enviromentController->Create();
	Video::CRenderController::Init();
	gameRun = true;
	return true;
}

void Game::Update(DWORD time)
{
	/*if(PeekMessage(&_sysMessage,NULL,0,0,PM_REMOVE))
	{
		if (_sysMessage.message == WM_QUIT)				
		{
			gameRun = false;	
		}
		else									
		{
			TranslateMessage(&_sysMessage);				
			DispatchMessage(&_sysMessage);				
		}
	}*/
}

void Game::Render()
{

	Core::CGlobal::GetRender()->BeginRender();
	Video::CRenderController::Render();
	Core::CGlobal::GetRender()->EndRender();

	static DWORD framesPerSecond = 0;       
    static DWORD lastTime = 0;   
	DWORD fps = 0;
        
    DWORD currentTime = GetTickCount();
    ++framesPerSecond;

    if(currentTime - lastTime > 1000 )
    {
        lastTime = currentTime;
        fps = framesPerSecond;
        framesPerSecond = 0;
		char fps_text[64];
		sprintf_s(fps_text,"FPS : %i",fps);
    }
}