#include "Game.h"
#include "RenderController.h"
#include "VBExtension.h"
#include "FBExtension.h"

Enviroment::EnviromentController* Game::_enviromentController = NULL;

Game::Game()
{

}

bool Game::Create()
{
	_CreateWindowContext();
	_CreateGLContext();
	Extension::VBExtension::VBExtension();
	Extension::FBExtension::FBExtension();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Video::CRenderController::Render2Texture(Video::CRenderController::ERenderTexture::SCREEN_TEXTURE);
	Video::CRenderController::Render2Texture(Video::CRenderController::ERenderTexture::REFLECTION_TEXTURE);
	Video::CRenderController::Render2Texture(Video::CRenderController::ERenderTexture::REFRACTION_TEXTURE);
	Video::CRenderController::Render();
	glFlush();
	SwapBuffers(hDC);
	
	static DWORD framesPerSecond = 0;       
    static DWORD lastTime = 0;   
	DWORD fps = 0;
        
    DWORD currentTime = GetTickCount();
    ++framesPerSecond;

    if(currentTime - lastTime > 1000 )
    {
        lastTime = currentTime;
        fps = (float)framesPerSecond;
        framesPerSecond = 0;
		char fps_text[64];
		sprintf_s(fps_text,"FPS : %i",fps);
		SetWindowCaption(fps_text);
    }
}