//#define STRICT
//#define WIN32_LEAN_AND_MEAN

#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <FCNTL.H>
#include <io.h>

#include <Cg/Cg.h>
#include <Cg/cgGL.h>

#include "m3_Viewer.h"
#include "m3_DDSLoader.h"
#include "m3_FileFormat.h"
#include "m3_Window.h"
#include "m3_Mesh.h"

//HDC	  g_hDC  = NULL;
//HGLRC g_hRC  = NULL;

GLuint	base;

CGprofile   cg_VertexProfile;
CGprofile   cg_PixelProfile;
CGcontext   cg_Context;
CGprogram   cg_VertexProgram;
CGprogram   cg_PixelProgram;

CGparameter cg_Texture_01;
CGparameter cg_Texture_02;

CGparameter cg_mWorldViewProjection;
CGparameter cg_mWorldViewInverse;

CGparameter cg_vCamera;
CGparameter cg_vLight;

std::vector<m3_Mesh*> meshList;

Uint32 my_callbackfunc(Uint32 interval, void *param);
void* my_callback_param;

Uint32 my_callbackfunc(Uint32 interval, void *param){
 return interval;
}

//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, 
//				   LPSTR lpCmdLine, int nCmdShow);
void init(void);
void render(void);
void shutDown(void);

int __stdcall WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	FreeConsole();
	AllocConsole();
	

	//SetConsoleTitle(winTitle);

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


if ( SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) < 0 ){ 
   printf("Unable to init SDL: %s\n", SDL_GetError()); 
   exit(1); 
 } 

 printf("Unabl"); 

 atexit(SDL_Quit); 

 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
 SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
 SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
 SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5); 

 if ( SDL_SetVideoMode(640,480,32,SDL_OPENGL) == NULL ){ 
   printf("Unable to set 640x480 video: %s\n", SDL_GetError()); 
   exit(1); 
 }


SDL_TimerID my_timer_id = SDL_AddTimer(1000, my_callbackfunc, my_callback_param);

   init();

   while(true)
   {
	  m3_Input::Update();
	  render();
   }
   shutDown();
}

GLvoid BuildFont(GLvoid)								
{
	/*HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-18,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(g_hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(g_hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(g_hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);	*/								// Delete The Font
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

void InitShader()
{
    if(cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
        cg_VertexProfile = CG_PROFILE_ARBVP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
        cg_VertexProfile = CG_PROFILE_VP40;
    else
    {
        MessageBox( NULL,"Failed to initialize vertex shader! Hardware doesn't "
            "support any of the required vertex shading extensions!",
            "ERROR",MB_OK|MB_ICONEXCLAMATION );
        return;
    }

	
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
        cg_PixelProfile = CG_PROFILE_ARBFP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
        cg_PixelProfile = CG_PROFILE_FP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
        cg_PixelProfile = CG_PROFILE_FP20;
    else
    {
        MessageBox( NULL,"Failed to initialize pixel shader! Hardware doesn't "
			        "support any of the required pixel shading extensions!",
			        "ERROR",MB_OK|MB_ICONEXCLAMATION );
		return;
    }


	cg_Context = cgCreateContext();

	//
	// Create the vertex and pixel shader...
	//
	
	cg_VertexProgram = cgCreateProgramFromFile( cg_Context,
										          CG_SOURCE,
										         "Content\\shaders\\vertex_shader.cg",
										         cg_VertexProfile,
										         NULL, 
										         NULL );

	cg_PixelProgram = cgCreateProgramFromFile( cg_Context,
										         CG_SOURCE,
										         "Content\\shaders\\pixel_shader.cg",
										         cg_PixelProfile,
										         NULL, 
										         NULL );

	cgGLLoadProgram( cg_VertexProgram );
	cgGLLoadProgram( cg_PixelProgram );

	cg_Texture_01   = cgGetNamedParameter(cg_PixelProgram, "colorTexture");
	cg_Texture_02   = cgGetNamedParameter(cg_PixelProgram, "normalTexture");

	cg_mWorldViewProjection    = cgGetNamedParameter( cg_PixelProgram, "mWorldViewProjection" );
	cg_mWorldViewInverse       = cgGetNamedParameter( cg_PixelProgram, "mWorldViewInverse" );
	cg_vCamera		           = cgGetNamedParameter( cg_PixelProgram, "vCamera" );
	cg_vLight                  = cgGetNamedParameter( cg_PixelProgram, "vLight");

	cgGLBindProgram( cg_VertexProgram );
	cgGLBindProgram( cg_PixelProgram );
}

void init( void )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
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

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	/////////////////////////////////////////////////////////////////////////////

	WIN32_FIND_DATA FindFileData; 
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
	BuildFont();

	InitShader();
}

void shutDown(void)	
{
	/*if( g_hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( g_hRC );
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC( m3_Window::hWindow, g_hDC );
		g_hDC = NULL;
	}*/
}


void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );

	static GLfloat lightAngle = 0.0f;
	lightAngle += 0.01f;
	GLfloat LightPosition[] = { cos(lightAngle)*16.0f*(m3_Input::mWheel + 1.0f), 0.0f, sin(lightAngle)*16.0f*(m3_Input::mWheel + 1.0f), 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	

	if(m3_Input::meshIndex >=  meshList.size())
		m3_Input::meshIndex = 0;

	if(m3_Input::saveToObj)
	{
		m3_Input::saveToObj = false;
		meshList[m3_Input::meshIndex]->Convert();
	}

	if(m3_Input::meshIndex >=0 && m3_Input::meshIndex < meshList.size())
	{
		//if(m3_Input::enableLight)
		//	glEnable(GL_LIGHTING);
		//else
		//	glDisable(GL_LIGHTING);

		cgGLSetTextureParameter( cg_Texture_01, meshList[m3_Input::meshIndex]->textureColorId );
		cgGLSetTextureParameter( cg_Texture_02, meshList[m3_Input::meshIndex]->textureNormalId );

		cgGLEnableProfile( cg_VertexProfile );
		cgGLEnableProfile( cg_PixelProfile );

		cgGLEnableTextureParameter(cg_Texture_01);
		cgGLEnableTextureParameter(cg_Texture_02);
		
		meshList[m3_Input::meshIndex]->Update();

		// This matrix will be used to transform the vertices from model-space to clip-space
		cgGLSetStateMatrixParameter( cg_mWorldViewProjection,
									CG_GL_MODELVIEW_PROJECTION_MATRIX,
									CG_GL_MATRIX_IDENTITY );

		// This matrix will be used to transform the normals from model-space to view-space
		cgGLSetStateMatrixParameter( cg_mWorldViewInverse,
									 CG_GL_MODELVIEW_MATRIX,
									 CG_GL_MATRIX_INVERSE_TRANSPOSE );

		float fEyePosition[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float fLightVector[] = { 5.0f, 5.0f, 5.0f, 0.0f };

		// Normalize light vector
		float fLength = sqrtf( fLightVector[0]*fLightVector[0] +
							   fLightVector[1]*fLightVector[1] +
							   fLightVector[2]*fLightVector[2] );
		fLightVector[0] /= fLength;
		fLightVector[1] /= fLength;
		fLightVector[2] /= fLength;

		cgGLSetParameter4fv( cg_vCamera, fEyePosition );
		cgGLSetParameter4fv( cg_vLight, fLightVector );

		meshList[m3_Input::meshIndex]->Render();

		cgGLDisableTextureParameter( cg_Texture_01 );
		cgGLDisableTextureParameter( cg_Texture_02 );

		cgGLDisableProfile( cg_VertexProfile );
		cgGLDisableProfile( cg_PixelProfile );

		if(m3_Input::enableNormal)
			meshList[m3_Input::meshIndex]->RenderNormals();

		glLoadIdentity();	
		glTranslatef(0.0f,0.0f,-1.0f);					
		glColor3f(1.0f,1.0f,1.0f);
 		glRasterPos2f(-0.5f,0.35f);
		glPrint(meshList[m3_Input::meshIndex]->meshName.c_str());	

		glRasterPos2f(-0.5f,-0.25f);
		glPrint("Press 'Tab' to switch mesh.");	
		glRasterPos2f(-0.5f,-0.28f);
		glPrint("Press '1' to turn on/off light.");
		glRasterPos2f(-0.5f,-0.31f);
		glPrint("Press '2' to turn on/off normal.");
		glRasterPos2f(-0.5f,-0.34f);
		glPrint("Press 'Space' to save mesh as .obj file.");
	}

	glFlush();
    SDL_GL_SwapBuffers();
	//SwapBuffers( g_hDC );
}
