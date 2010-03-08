#pragma once
#ifndef _M3_INPUT_H_
#define _M3_INPUT_H_

#include <windows.h>

class m3_Input
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

	static POINT     mLastPosition;
	static POINT     mCurrentPosition;
	static POINT     mDeltaPosition;

	static unsigned int meshIndex;
	static bool			enableLight;
	static bool			enableNormal;
	static bool			saveToObj;
	// FUNCTION
public :
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif