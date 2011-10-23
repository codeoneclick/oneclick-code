#ifndef _GUICONTROLLER_H_
#define _GUICONTROLLER_H_

#include <map>
#include <vector>
#include "GuiMenuDummy.h"

class GuiController
{
private :
	std::string _currentMenu;
	std::string _currentCommand;
	std::map<std::string,GuiMenuDummy*> _menusContainer;
public :
	GuiController();
	void AddMenu(std::string _menuName, GuiMenuDummy *_menu);
	__forceinline void SetCurrentMenu(std::string value) { _currentMenu = value; }
	__forceinline std::string GetCommand() { std::string command = _currentCommand; _currentCommand = "none"; return command; }

	void Update();
	void Render();
	void CheckCollision();
	void Resize();
	void ShowControl(std::string _name, SlideState _state);
	void HideControl(std::string _name);
	void HideAllControl();
};

#endif