#include <windows.h>

class gInput
{
	// VARIBLES
	
private :
	// FUNCTION
private :
    // VARIBLES
public :
	static int		 mWheel;
	static bool	     mRightClick;
	static bool      mRightDown;
	static bool      mLeftClick;
	static bool      mLeftDown;
	// FUNCTION
public :
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};
