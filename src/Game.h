#ifndef _GAME_H_
#define _GAME_H_

#include "Window.h"
#include "Console.h"
#include "Scene.h"
#include "RenderController.h"
#include "MainMenu.h"

class Game : public Window , public Console
{
private :
	static Scene *_scene;
	MainMenu* _mainMenu;
private :

public :	
	
public :
	void Load();
	void Start();
	virtual void Update(unsigned long deltaTime);
	virtual void Render();
	inline static Scene *GetSceneInstance() { return _scene; }
};

#endif
