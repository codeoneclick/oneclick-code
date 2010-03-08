#pragma once
#ifndef _M3_DDSLOADER_H_
#define _M3_DDSLOADER_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <ddraw.h> 
#include "glext.h"
//
#include <stdlib.h>
#include <fstream>




struct DDS_IMAGE_DATA
{
    GLsizei  width;
    GLsizei  height;
    GLint    components;
    GLenum   format;
    int      numMipMaps;
    GLubyte *pixels;
};

class m3_DDSLoader
{
	// VARIBLES
private :
	// FUNCTION
private :
	static DDS_IMAGE_DATA *_LoadImageData(const char* fileName);
    // VARIBLES
public :
	// FUNCTION
public :
	static void Load( const char* fileName,GLuint *textureId);
};

#endif

