#ifndef _VBExtension_H_
#define _VBExtension_H_

#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

namespace Extension
{
class VBExtension
{
private :
	static bool extensionSingleFlag;
public :
	static PFNGLGENBUFFERSARBPROC			 glGenBuffersARB;	
	static PFNGLDELETEBUFFERSARBPROC		 glDeleteBuffersARB; 
	static PFNGLBINDBUFFERARBPROC			 glBindBufferARB;					
	static PFNGLBUFFERDATAARBPROC			 glBufferDataARB;					
	static PFNGLMAPBUFFERARBPROC			 glMapBufferARB;
	static PFNGLUNMAPBUFFERARBPROC           glUnmapBufferARB;
	static PFNGLCLIENTACTIVETEXTUREPROC		 glClientActiveTextureCoordARB;
	static PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
	static PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation;
	static PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
	static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
public :
	VBExtension();
};
};
#endif