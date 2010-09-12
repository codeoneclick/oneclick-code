#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>
#include <SDL.h>
#include "Vector3d.h"
#include "window.h"

class Input
{
	// VARIBLES
private :
	static SDL_Event event; 
	// FUNCTION
private :
    // VARIBLES
public :
	static int		 mWheel;
	static float     mUpPosition;
	static bool	     mRightClick;
	static bool      mRightDown;
	static bool      mLeftClick;
	static bool      mLeftDown;

	static POINT     mLastPosition;
	static POINT     mCurrentPosition;
	static POINT     mDeltaPosition;

	static int			meshIndex;
	static bool			enableLight;
	static bool			enableNormal;
	static bool			saveToObj;

	static bool         ePressForward;
	static bool         ePressBackward;
	static bool         ePressLeft;
	static bool			ePressRight;
	static bool         ePressRotateLeft;
	static bool         ePressRotateRight;

	static bool			exitEvent;

	static int          sequenceIndex;

	static bool         playerMove;
	static bool         fire;
	// FUNCTION
public :
	static void Update();
};

#endif