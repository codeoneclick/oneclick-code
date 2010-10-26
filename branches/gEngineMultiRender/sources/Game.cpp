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
	_CreateWindow(640,480,32);
	Core::CGlobal::GetDevice();
	Video::CRenderController::Load();
	_enviromentController = new Enviroment::EnviromentController();
	_enviromentController->Create();
	gameRun = true;
	return true;
}

void Game::Update(DWORD time)
{
	if(PeekMessage(&_sysMessage,NULL,0,0,PM_REMOVE))
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
	}
	else
	{
		if (core::Input::keys[VK_ESCAPE])				
		{
			gameRun = false;						
		}
	}
}

void Game::Render()
{

	Core::CRender::BeginRender();
	Video::CRenderController::Render2Texture(Video::CRenderController::SCREEN_TEXTURE);
	Core::CRender::EndRender();

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
		SetText(fps_text);
    }
}