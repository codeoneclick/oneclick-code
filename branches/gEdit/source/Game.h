#ifndef _GAME_H_
#define _GAME_H_
#include "Core/CDeviceD3D.h"
#include "EnviromentController.h"

class Game
{
private :
	MSG	_sysMessage;
	static Enviroment::EnviromentController *_enviromentController;
public :
	Game();
	bool Create();
	virtual void Update(DWORD time);
	virtual void Render();
	bool gameRun;
	__forceinline static Enviroment::EnviromentController *GetEnviromentControllerInstance() { return _enviromentController; }
};

#endif