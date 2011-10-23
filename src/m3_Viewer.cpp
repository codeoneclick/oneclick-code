//#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <FCNTL.H>
#include <io.h>

#include <Cg/Cg.h>
#include <Cg/cgGL.h>

#include "m3_Core.h"
#include "m3_Viewer.h"
#include "m3_DDSLoader.h"
#include "m3_FileFormat.h"
#include "m3_Window.h"
#include "m3_Mesh.h"
#include "m3_Heightmap.h"
#include "m3_PostService.h"
#include "m3_Resource.h"
#include "Matrix4x4.h"
#include "m3_3DSLoader.h"
#include "m3_Scene.h"

//m3_Heightmap *map;

//std::vector<m3_Mesh*> meshList;

m3_Scene *_scene;


Uint32 my_callbackfunc(Uint32 interval, void *param);
void* my_callback_param;

Uint32 my_callbackfunc(Uint32 interval, void *param){
 return interval;
}

void init(void);
void render(void);
void shutDown(void);

int __stdcall WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	FreeConsole();
	AllocConsole();

	int hConHandle;
	long lStdHandle;
	FILE *fp;

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );

 // FT_Init_FreeType( &library ); 
if ( SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) < 0 ){ 
   printf("Unable to init SDL: %s\n", SDL_GetError()); 
   exit(1); 
 } 

 //printf("Unabl"); 

 atexit(SDL_Quit); 
 putenv(strdup("SDL_VIDEO_CENTERED=1")); 
 if ( SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32,SDL_OPENGL | !SDL_FULLSCREEN) == NULL )
 { 
   printf("Unable to set 640x480 video: %s\n", SDL_GetError()); 
   exit(1); 
 }

 SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
 SDL_WM_SetIcon(icon, NULL);

 SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0 );
 SDL_WM_SetCaption("m3_viewer", NULL);
 SDL_TimerID my_timer_id = SDL_AddTimer(1000, my_callbackfunc, my_callback_param);

   init();

   while(!m3_Input::exitEvent)
   {
	  m3_Input::Update();
	  render();
   }
   shutDown();
}

void init( void )
{
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glShadeModel(GL_SMOOTH);

	GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f,  1.0f };
	GLfloat LightAmbient[]  = { 0.7f, 0.7f, 0.7f,  1.0f };
	GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f,  1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	
	glEnable(GL_LIGHT1);	

	glDisable(GL_LIGHTING);

	glLoadIdentity();
	glMatrixMode( GL_PROJECTION );
	Matrix4x4 mProjection = MatrixProjection(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,1000.0f);
	glLoadMatrixf(mProjection.m);

	/////////////////////////////////////////////////////////////////////////////

	/*WIN32_FIND_DATA FindFileData; 
	HANDLE hFind = INVALID_HANDLE_VALUE; 
	char *DirSpec = "Content\\models\\*.m3";
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		meshList.push_back(new m3_Mesh());
		std::string fileName = "Content\\models\\";
		fileName += FindFileData.cFileName;
		meshList[meshList.size() - 1]->Load(fileName.c_str(),FindFileData.cFileName);
		while(FindNextFile(hFind, &FindFileData) != 0)
		{
			fileName = "Content\\models\\";
			fileName += FindFileData.cFileName;
			meshList.push_back(new m3_Mesh());
			meshList[meshList.size() - 1]->Load(fileName.c_str(),FindFileData.cFileName);
		}
	}

	meshList.push_back(new m3_Mesh());
	meshList[meshList.size() - 1]->Load("Content\\models\\Panter.3ds","Panter.3ds");

	map = new m3_Heightmap();
	map->Load("Content\\maps\\map.raw");*/

	m3_DDSLoader::glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)wglGetProcAddress("glCompressedTexImage2DARB");

	_scene = new m3_Scene();
	_scene->Load();

	m3_PostService::Load();
	m3_Core::GetGUI()->SetCurrentMenu("main_menu");

}

void shutDown(void)	
{

}

void render( void )
{
	m3_PostService::Update();
	m3_Core::GetCamera()->Update();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	_scene->Update();
	_scene->Render();
	
	m3_PostService::Render();

	glFlush();
    SDL_GL_SwapBuffers();
}
