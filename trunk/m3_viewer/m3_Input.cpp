#include "m3_Input.h"

int		 m3_Input::mWheel		     = 0;
POINT    m3_Input::mLastPosition     = POINT();
POINT    m3_Input::mCurrentPosition  = POINT();
POINT    m3_Input::mDeltaPosition    = POINT();
bool	 m3_Input::mRightClick   = false;
bool	 m3_Input::mRightDown	 = false;
bool	 m3_Input::mLeftClick	 = false;
bool	 m3_Input::mLeftDown	 = false;

bool	 m3_Input::enableLight	 = false;
bool	 m3_Input::enableNormal	 = false;
bool	 m3_Input::saveToObj	 = false;
unsigned int m3_Input::meshIndex = 0;
SDL_Event    m3_Input::event     = SDL_Event(); 

void m3_Input::Update()
{
	while ( SDL_PollEvent(&event) )
	{ 
		switch(event.type)
		{
			case SDL_QUIT:
				exit(0);
			break;

			// Key down event.
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						exit(0);
					break;

					case SDLK_TAB:
						meshIndex++;
					break;

					case SDLK_SPACE:
						saveToObj = true;
					break;
				} 
			break;

			// Mouse move event.
			case SDL_MOUSEMOTION:
				mCurrentPosition.x = event.motion.x;
				mCurrentPosition.y = event.motion.y;
				if( mLeftDown )
				{
					mDeltaPosition.x -= (mCurrentPosition.x - mLastPosition.x);
					mDeltaPosition.y -= (mCurrentPosition.y - mLastPosition.y);
				}
				mLastPosition.x = mCurrentPosition.x;
				mLastPosition.y = mCurrentPosition.y;
			break;

			case SDL_MOUSEBUTTONDOWN:
				mLeftDown  = true;
				mLeftClick = true;
				mLastPosition.x = mCurrentPosition.x = event.button.x;
				mLastPosition.y = mCurrentPosition.y = event.button.y;
			break;

			case SDL_MOUSEBUTTONUP:
				switch(event.button.button)
				{
					case SDL_BUTTON_WHEELUP:
						mWheel -= 1;
                        break;

					case SDL_BUTTON_WHEELDOWN:
						mWheel += 1;
						break;
				}
				mLeftDown  = false;
			break;	
		}
	} 
}

