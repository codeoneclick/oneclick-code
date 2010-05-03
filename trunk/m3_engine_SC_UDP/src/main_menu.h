#pragma once
#ifndef _M3_MAIN_MENU_H_
#define _M3_MAIN_MENU_H_

#include "m3_Core.h"

class main_menu
{
private :
	std::vector<m3_GUIEntity*> _elementsContainer;
public :
	
	main_menu();
	void Load(std::string name);
	void OnEvent();
};

#endif