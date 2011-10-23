#pragma once
#ifndef _M3_WINDOW_H_
#define _M3_WINDOW_H_

#include <windows.h>
#include "m3_Input.h"

class m3_Window
{
	// VARIBLES
	
private :
	// FUNCTION
private :
    // VARIBLES
public :
	static int				wndWidth;
	static int				wndHeight;
	static WNDCLASSEX       wndClass;
	static HWND			    hWindow;  
	static bool             fullScreen;
	// FUNCTION
public :
	static void Load();
};

#endif