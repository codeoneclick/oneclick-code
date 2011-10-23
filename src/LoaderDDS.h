#ifndef _LOADERDDS_H_
#define _LOADERDDS_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ddraw.h> 
#include "glext.h"
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

class LoaderDDS
{
	// VARIBLES
private :
	// FUNCTION
private :
    // VARIBLES
public :
	// FUNCTION
public :
	static unsigned int Load(DDS_IMAGE_DATA* value);
	static DDS_IMAGE_DATA* LoadImageData(std::string value);
	static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
};

#endif

