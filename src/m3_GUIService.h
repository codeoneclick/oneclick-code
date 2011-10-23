#pragma once
#ifndef _M3_GUISERVICE_H_
#define _M3_GUISERVICE_H_

#include <map>
#include <vector>
#include "m3_GUIEntity.h"
#include "m3_Input.h"

class m3_GUIService
{
private :
	std::string _currentMenu;
	std::string _currentCommand;
	std::map<std::string,std::vector<m3_GUIEntity*>> _GUIMenusContainer;
public :
	void AddMenu(std::string _menuName, std::vector<m3_GUIEntity*> _GUIElementsContainer);
	__forceinline void SetCurrentMenu(std::string value) { _currentMenu = value; }
	__forceinline std::string GetCommand() { std::string command = _currentCommand; _currentCommand = "none"; return command; }

	m3_GUIService();
	void Update();
	void Render();
	void CheckCollision();
};

#endif