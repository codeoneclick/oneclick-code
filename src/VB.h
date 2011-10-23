#ifndef _VB_H_
#define _VB_H_

#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

#define glCreateVB     glCreateVB()
#define glDeleteVB     glDeleteVB()
#define glBindVB       glBindVB()
#define glWriteDataVB  glWriteDataVB()
#define glLockVB       glLockVB()
#define glUnlockVB     glUnlockVB()
#define glBindDataVB   glBindDataVB()
#define glBindDataVB_2   glBindDataVB_2()
#define glGetDataLocation   glGetDataLocation()
#define glEnableVertexAttrib   glEnableVertexAttrib()
#define glDisableVertexAttrib   glDisableVertexAttrib()


class VB
{
private :
	static PFNGLGENBUFFERSARBPROC           _glGenBuffersARB;					
	static PFNGLBINDBUFFERARBPROC           _glBindBufferARB;					
	static PFNGLBUFFERDATAARBPROC           _glBufferDataARB;					
	static PFNGLDELETEBUFFERSARBPROC        _glDeleteBuffersARB;
	static PFNGLMAPBUFFERARBPROC            _glMapBufferARB;
    static PFNGLUNMAPBUFFERARBPROC          _glUnmapBufferARB;
	static PFNGLCLIENTACTIVETEXTUREPROC     _glClientActiveTextureCoordARB;
	static PFNGLVERTEXATTRIBPOINTERPROC     _glVertexAttribPointer; 
	static PFNGLGETATTRIBLOCATIONPROC		_glGetAttribLocation;
	static PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray;
	static PFNGLDISABLEVERTEXATTRIBARRAYPROC _glDisableVertexAttribArray;
public :
	static PFNGLGENBUFFERSARBPROC			glCreateVB;	
	static PFNGLDELETEBUFFERSARBPROC		glDeleteVB; 
	static PFNGLBINDBUFFERARBPROC			glBindVB;					
	static PFNGLBUFFERDATAARBPROC			glWriteDataVB;					
	static PFNGLMAPBUFFERARBPROC			glLockVB;
	static PFNGLUNMAPBUFFERARBPROC          glUnlockVB;
	static PFNGLCLIENTACTIVETEXTUREPROC		glBindDataVB;
	static PFNGLVERTEXATTRIBPOINTERPROC     glBindDataVB_2;
	static PFNGLGETATTRIBLOCATIONPROC       glGetDataLocation;
	static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttrib;
	static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttrib;
};

#endif