#ifndef _G_WINDOW_H_
#define _G_WINDOW_H_

#include "gInput.h"
class gWindow
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