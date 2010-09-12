#include "m3_PostService.h"

GLuint m3_PostService::_postTextureId = 0;

unsigned int m3_PostService::_textureHeight = 512;
unsigned int m3_PostService::_textureWidth  = 512;

SDL_Surface *m3_PostService::old_surface = NULL;
SDL_Surface *m3_PostService::current_surface = NULL;

GLuint m3_PostService::_EmptyTexture()
{
	GLuint textureId;		
	unsigned int* textureData;		

	textureData = (unsigned int*)new GLuint[((_textureWidth * _textureHeight)* 4 * sizeof(unsigned int))];
	ZeroMemory(textureData,((_textureWidth * _textureHeight)* 4 * sizeof(unsigned int)));	

	glGenTextures(1, &textureId);					
	glBindTexture(GL_TEXTURE_2D, textureId);		
	glTexImage2D(GL_TEXTURE_2D, 0, 4, _textureWidth, _textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);					

	delete [] textureData;											
	return textureId;			
}

void m3_PostService::EnableRenderToTexture()
{
	if(_postTextureId == 0)
		_postTextureId = _EmptyTexture();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,_textureWidth,_textureHeight);

	/*current_surface = SDL_CreateRGBSurface(0, _textureWidth, _textureHeight, 32, 
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_BlitSurface(old_surface, 0, current_surface, 0);
	glBindTexture(GL_TEXTURE_2D, _postTextureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, _textureWidth, _textureHeight, 0, GL_BGRA, 
			GL_UNSIGNED_BYTE, current_surface->pixels );*/
}

void m3_PostService::DisableRenderToTexture()
{
	//SDL_FreeSurface(current_surface);
	//SDL_FreeSurface(old_surface);
	glBindTexture(GL_TEXTURE_2D,_postTextureId);			
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, _textureWidth, _textureHeight, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);						
}

void m3_PostService::Render()
{															
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();							
	glOrtho( 0, WINDOW_WIDTH , WINDOW_HEIGHT , 0, -1, 1 );				
	glMatrixMode(GL_MODELVIEW);						
	glPushMatrix();								
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	m3_Core::GetGUI()->Render();

	/*glBindTexture(GL_TEXTURE_2D,_postTextureId);	
					
	glBegin(GL_QUADS);	
		glTexCoord2f(0,1);			
		glVertex2f(0,0);							

		glTexCoord2f(0,0);						
		glVertex2f(0,WINDOW_HEIGHT);						

		glTexCoord2f(1,0);						
		glVertex2f(WINDOW_WIDTH,WINDOW_HEIGHT);								

		glTexCoord2f(1,1);						
		glVertex2f(WINDOW_WIDTH,0);								
	glEnd();	*/

	glMatrixMode( GL_PROJECTION );							
	glPopMatrix();								
	glMatrixMode( GL_MODELVIEW );							
	glPopMatrix();						
}

m3_GUIController* m3_PostService::_GUIController = NULL;

void m3_PostService::Load()
{
	_GUIController = new m3_GUIController();
	_GUIController->Load();
}

void m3_PostService::Update()
{
	_GUIController->Update();
	m3_Core::GetGUI()->Update();
	m3_Core::GetGUI()->CheckCollision();
}

