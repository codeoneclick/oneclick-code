#pragma once
#ifndef _M3_GUICONTROLLER_H_
#define _M3_GUICONTROLLER_H_

#include "m3_Core.h"
#include "main_menu.h"

class m3_GUIController
{
private :
	main_menu *_main_menu;
	
public :
	void Load();
	void Update();
};

#endif