#ifndef _INPUT_H_
#define _INPUT_H_
#include <windows.h>

namespace core
{

class Input
{
private :

public :
	static LRESULT	CALLBACK InputProcess(HWND hWindow, UINT	msg, WPARAM	paramW, LPARAM paramL);
	static bool	keys[256];
	static bool mouseL;
	static bool mouseR;
	static POINT currentMousePosition;
	static POINT oldMousePosition;
};
};

#endif