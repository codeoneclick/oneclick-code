#include "Window.h"

#include "Core.h"

int				Window::currentHeight	= 240;
int				Window::currentWidth 	= 320;
int				Window::lastHeight	    = 240;
int				Window::lastWidth 	    = 320;
bool			Window::isFullscreen    = false;
SDL_Surface*    Window::windowSurface   = NULL;

bool Window::InitWindowContext()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
	{ 
		printf("Unable to init SDL: %s \n", SDL_GetError()); 
		return false;
	} 

    atexit(SDL_Quit);

	putenv(strdup("SDL_VIDEO_CENTERED = 1")); 
	
	unsigned int initParams = SDL_OPENGL | SDL_HWSURFACE;
	if(isFullscreen)
		initParams |= SDL_FULLSCREEN;

	if( (windowSurface = SDL_SetVideoMode(Window::currentWidth,Window::currentHeight,32,initParams)) == NULL)
	{ 
	    printf("Unable to set %ix%i video: %s \n",Window::currentWidth,Window::currentHeight, SDL_GetError()); 
        return false; 
    }

    SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
    SDL_WM_SetIcon(icon, NULL);

    SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 );
    SDL_WM_SetCaption("OneClick", NULL);
	return true;
}

void Window::InitGLContext()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);	
	glEnable( GL_DEPTH_TEST );
	glDepthFunc(GL_LEQUAL);		
	glEnable(GL_CULL_FACE);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glHint ( GL_POLYGON_SMOOTH_HINT,         GL_NICEST );
	glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
}

void Window::SwitchResolution(int _width, int _height)
{
	putenv("SDL_VIDEO_WINDOW_POS");
	putenv("SDL_VIDEO_CENTERED=1");
	Window::lastWidth = Window::currentWidth;
	Window::lastHeight = Window::currentHeight;
	Window::currentWidth = _width;
	Window::currentHeight = _height;
	SDL_SetVideoMode(Window::currentWidth,Window::currentHeight,32,SDL_OPENGL);
	glViewport(0,0,Window::currentWidth ,Window::currentHeight);	
	Core::GetGuiController()->Resize();
}

