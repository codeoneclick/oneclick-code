#include "Input.h"

int		 Input::mWheel		      = -7;
float    Input::mUpPosition       = -0.5f;
POINT    Input::mLastPosition     = POINT();
POINT    Input::mCurrentPosition  = POINT();
POINT    Input::mDeltaPosition    = POINT();
bool	 Input::mRightClick   = false;
bool	 Input::mRightDown	 = false;
bool	 Input::mLeftClick	 = false;
bool	 Input::mLeftDown	 = false;

bool	 Input::enableLight	 = false;
bool	 Input::enableNormal	 = false;
bool	 Input::saveToObj	 = false;
int		 Input::meshIndex = 0;
SDL_Event    Input::event     = SDL_Event(); 

bool     Input::ePressForward  = false;
bool     Input::ePressBackward = false;
bool     Input::ePressLeft     = false;
bool     Input::ePressRight    = false;
bool     Input::ePressRotateLeft  = false;
bool     Input::ePressRotateRight = false;

bool	 Input::exitEvent    	 = false;

bool     Input::playerMove        = false;
bool     Input::fire              = false;

int      Input::sequenceIndex     = 0;

void Input::Update()
{
	while ( SDL_PollEvent(&event) )
	{ 
		switch(event.type)
		{
			case SDL_QUIT:
				exit(0);
			break;

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

					case SDLK_w :
						ePressForward = true;
						playerMove = true;
					break;

					case SDLK_s :
						ePressBackward = true;
					break;

					case SDLK_a :
						ePressLeft = true;
					break;

					case SDLK_d :
						ePressRight = true;
					break;

					case SDLK_q :
						ePressRotateLeft = true;
					break;
					
					case SDLK_e :
						ePressRotateRight = true;
					break;

					case SDLK_f :
						fire = true;
					break;

					case SDLK_F1 :
						Window::SwitchResolution(320,240);
					break;

					case SDLK_F2 :
						Window::SwitchResolution(640,480);
					break;

					case SDLK_F3 :
						Window::SwitchResolution(800,600);	
					break;

					case SDLK_F4 :
						Window::SwitchResolution(1024,768);	
					break;

					case SDLK_1 :
						sequenceIndex++;
					break;
				} 
			break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_w :
						ePressForward = false;
						playerMove = false;
					break;

					case SDLK_s :
						ePressBackward = false;
					break;

					case SDLK_a :
						ePressLeft = false;
					break;

					case SDLK_d :
						ePressRight = false;					
					break;

					case SDLK_q :
						ePressRotateLeft = false;
					break;
					
					case SDLK_e :
						ePressRotateRight = false;
					break;

					case SDLK_f :
						fire = false;
					break;
				}
			break;

			case SDL_MOUSEMOTION:
				mCurrentPosition.x = event.motion.x;
				mCurrentPosition.y = event.motion.y;
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
						if(mWheel > -15) 
							mWheel -= 1;
                        break;

					case SDL_BUTTON_WHEELDOWN:
						if(mWheel < -1)
							mWheel += 1;
						break;
				}
				mLeftClick = false;
				mLeftDown  = false;
			break;	
		}
	} 
}

