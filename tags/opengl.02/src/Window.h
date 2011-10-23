#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Input.h"

class Window
{
	// VARIBLES
private :
	// FUNCTION
private :
    // VARIBLES
public :
	static int				currentWidth;
	static int				currentHeight;
	static int				lastWidth;
	static int				lastHeight;
	static bool             isFullscreen;
	static SDL_Surface*     windowSurface;
	// FUNCTION
public :
	static bool InitWindowContext();
	static void InitGLContext();
	virtual void Update(unsigned long deltaTime) = 0;
	virtual void Render() = 0;
	static void  SwitchResolution(int _width, int _height);
};

#endif