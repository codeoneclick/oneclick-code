#include "Input.h"

using namespace core;

bool  Input::keys[256];
bool  Input::mouseL = false;
bool  Input::mouseR = false;
POINT Input::currentMousePosition = POINT();
POINT Input::oldMousePosition     = POINT();

LRESULT CALLBACK Input::InputProcess(HWND hWindow, UINT	message, WPARAM	paramW, LPARAM paramL)	
{
	GetCursorPos(&currentMousePosition);
	switch (message)									
	{
		case WM_ACTIVATE:						
		{
			if (!HIWORD(paramW))					
			{
							
			}
			else
			{	

			}
			return 0;								
		}

		case WM_SYSCOMMAND:						
		{
			switch (paramW)						
			{
				case SC_SCREENSAVE:				
				case SC_MONITORPOWER:				
				return 0;							
			}
			break;									
		}

		case WM_CLOSE:								
		{
			PostQuitMessage(0);						
			return 0;							
		}

		case WM_KEYDOWN:							
		{
			keys[paramW] = true;					
			return 0;								
		}

		case WM_KEYUP:								
		{
			keys[paramW] = false;					
			return 0;								
		}

		case WM_SIZE:								
		{
			return 0;								
		}
		
		case WM_RBUTTONDOWN :
		{
			GetCursorPos(&oldMousePosition);
			mouseR = true;
			return 0;		
		}
		case WM_RBUTTONUP :
		{
			mouseR = false;
			return 0;	
		}

		case WM_LBUTTONDOWN :
		{
			GetCursorPos(&oldMousePosition);
			mouseL = true;
			return 0;		
		}
		case WM_LBUTTONUP :
		{
			mouseL = false;
			return 0;	
		}
		                  
	}
	return DefWindowProc(hWindow, message, paramW, paramL);
}