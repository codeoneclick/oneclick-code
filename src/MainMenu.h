#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "GuiMenuDummy.h"

class MainMenu : public GuiMenuDummy
{
private :

public :
	MainMenu();
	virtual void Load(std::string name);
	virtual void OnEvent();
};

#endif
