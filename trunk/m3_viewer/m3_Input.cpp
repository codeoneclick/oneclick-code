#include "m3_Input.h"

int		 m3_Input::mWheel		 = 0;
POINT    m3_Input::mLastPosition = POINT();
POINT    m3_Input::mCurrentPosition  = POINT();
POINT    m3_Input::mDeltaPosition  = POINT();
bool	 m3_Input::mRightClick = false;
bool	 m3_Input::mRightDown	 = false;
bool	 m3_Input::mLeftClick	 = false;
bool	 m3_Input::mLeftDown	 = false;

bool	 m3_Input::enableLight	 = false;
bool	 m3_Input::enableNormal	 = false;
bool	 m3_Input::saveToObj	 = false;
unsigned int m3_Input::meshIndex = 0;


LRESULT CALLBACK m3_Input::wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
    {
		case WM_MOUSEWHEEL:
			mWheel -= GET_WHEEL_DELTA_WPARAM(wParam)/120;
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
				case VK_TAB:
					meshIndex++;
					break;
				case 0x31:
					enableLight = !enableLight;
					break;
				case 0x32:
					enableNormal = !enableNormal;
				case VK_SPACE:
					saveToObj = true;
					break;
            }
            break;
		case WM_LBUTTONDOWN:
			mLeftDown  = true;
			mLeftClick = true;
			mLastPosition.x = mCurrentPosition.x = LOWORD (lParam);
			mLastPosition.y = mCurrentPosition.y = HIWORD (lParam);
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

		case WM_MOUSEMOVE:
		{
			mCurrentPosition.x = LOWORD (lParam);
			mCurrentPosition.y = HIWORD (lParam);

			if( mLeftDown )
			{
				mDeltaPosition.x -= (mCurrentPosition.x - mLastPosition.x);
				mDeltaPosition.y -= (mCurrentPosition.y - mLastPosition.y);
			}

			mLastPosition.x = mCurrentPosition.x;
			mLastPosition.y = mCurrentPosition.y;
		}
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

