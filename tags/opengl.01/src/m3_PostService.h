#pragma once
#ifndef _M3_POSTSERVICE_H_
#define _M3_POSTSERVICE_H_

#include <windows.h>
#include <stdlib.h>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include <ddraw.h> 

#include "m3_GUIController.h"

class m3_PostService
{
	private:
		static m3_GUIController* _GUIController;
		static GLuint _postTextureId;
		static unsigned int _textureWidth;
		static unsigned int _textureHeight;
		static SDL_Surface *old_surface;
		static SDL_Surface *current_surface;
		static GLuint _EmptyTexture();
	public:
		static void EnableRenderToTexture();
		static void DisableRenderToTexture();
		static void Render();
		static void Update();
		static void Load();
};
#endif