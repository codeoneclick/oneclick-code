#include "gInput.h"

int		 gInput::mWheel		 = 0;
bool	 gInput::mRightClick = false;
bool	 gInput::mRightDown	 = false;
bool	 gInput::mLeftClick	 = false;
bool	 gInput::mLeftDown	 = false;


LRESULT CALLBACK gInput::wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
    {
		case WM_MOUSEWHEEL:
			mWheel = GET_WHEEL_DELTA_WPARAM(wParam);
		break;

		case WM_KEYUP:
            switch(wParam)
            { 
		       case VK_ESCAPE:
					PostQuitMessage(0);
			   break;
            }
            break;
		case WM_KEYDOWN:
            switch(wParam)
            { 
            }
            break;
		case WM_LBUTTONDOWN:
			mLeftDown  = true;
			mLeftClick = true;
            break;

        case WM_LBUTTONUP:
			mLeftDown  = false;
            break;

		case WM_RBUTTONDOWN:
			mRightDown  = true;
			mRightClick = true;
			break;

		 case WM_RBUTTONUP:
			mRightDown  = false;
            break;

		case WM_ACTIVATE:
		    break;

		case WM_SIZE:
			break;

         case WM_CLOSE:
         case WM_DESTROY:
            PostQuitMessage(0);
            break;

            default:
               break;
       }
	return DefWindowProc( hwnd, message, wParam, lParam );
}

