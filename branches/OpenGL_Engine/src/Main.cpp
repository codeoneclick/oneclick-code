#include "Game.h"

Game* _game;

int CALLBACK WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	_game = new Game();
	
	Game::InitWindowContext();
	Game::InitGLContext();
	Game::InitConsoleContext();
	
	_game->Load();
	_game->Start();
}