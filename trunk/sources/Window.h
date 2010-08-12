#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>		
#include <gl\gl.h>		
#include <gl\glu.h>
#include <string>
namespace core
{
class Window
{
private :
	unsigned int _currentWidth;
	unsigned int _currentHeight;
	unsigned int _oldWidth;
	unsigned int _oldHeight;
	unsigned int _bitsPerPixel; 
	bool         _fullscreen;
protected :
	bool _CreateWindowContext();
	bool _CreateGLContext();

	virtual void Render() = 0;
	virtual void Update(DWORD time) = 0;

	HDC			hDC;		
	HGLRC		hRC;		
	HWND		hWnd;		
	HINSTANCE	hInstance;		
public  :
	Window();
	void  SetResolution(unsigned int width, unsigned int height, unsigned int bitPerPixel);
	void  SetFullscreen(bool value);
	float GetResizeDelta();
	void  SetWindowCaption(std::string text);

	static unsigned int Width;
	static unsigned int Height;

	
};

};

#endif