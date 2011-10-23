#include "Game.h"

Scene *Game::_scene = NULL;

void Game::Load()
{
	_scene = new Scene();
	_scene->Load();
	_mainMenu = new MainMenu();
	_mainMenu->Load("mainMenu");
	RenderController::Load();
}

void Game::Start()
{
   while(!Input::exitEvent)
   {
	  Input::Update();
	  Update(0);
	  Render();
   }
}

void Game::Update(unsigned long deltaTime)
{
	Core::GetCamera()->Update();
	Core::GetGuiController()->Update();
	Core::GetGuiController()->CheckCollision();
}

void Game::Render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderController::RenderToTexture(RENDER_SIMPLE_TEXTURE);
	RenderController::RenderToTexture(RENDER_REFLECTION_TEXTURE);
	RenderController::RenderToTexture(RENDER_REFRACTION_TEXTURE);
	RenderController::Render(RENDER_POST);
	glFlush();
    SDL_GL_SwapBuffers();

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
		printf("FPS : %i \n",fps);
    }
}