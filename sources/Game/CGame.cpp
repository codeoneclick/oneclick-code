#include "CGame.h"
#include "Controller/RenderController.h"
#include "../Core/CGlobal.h"

CGame::CGame()
{
	_CreateWindow(800,600,32);
	Core::CGlobal::GetDevice();
	Video::CRenderController::Init();
	m_enviromentController = new Enviroment::EnviromentController();
	m_enviromentController->Load();
	m_isGameRun = true;
}

void CGame::update()
{
	if(PeekMessage(&m_systemMessage,NULL,0,0,PM_REMOVE))
	{
		if (m_systemMessage.message == WM_QUIT)				
		{
			m_isGameRun = false;	
		}
		else									
		{
			TranslateMessage(&m_systemMessage);				
			DispatchMessage(&m_systemMessage);				
		}
	}
	else
	{
		if (core::Input::keys[VK_ESCAPE])				
		{
			m_isGameRun = false;						
		}
	}
}

void CGame::render()
{
	Video::CRenderController::Render2Texture(Video::CRenderController::REFLECTION_TEXTURE);
	Video::CRenderController::Render2Texture(Video::CRenderController::REFRACTION_TEXTURE);
	Video::CRenderController::Render(Video::CRenderController::SCREEN_TEXTURE);

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