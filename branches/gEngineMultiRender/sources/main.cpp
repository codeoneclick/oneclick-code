#include <windows.h>		
#include <gl\gl.h>		
#include <gl\glu.h>

#include "Game.h"

int main()
{
	Game* gameInstance = new Game();
	gameInstance->Create();

	while(gameInstance->gameRun)
	{
		gameInstance->Update(0);
		gameInstance->Render();
	}
	return 0;						
}
