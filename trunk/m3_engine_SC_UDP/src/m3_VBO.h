#pragma once
#ifndef _M3_VBO_H_
#define _M3_VBO_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

class m3_VBO
{
private :
	static PFNGLGENBUFFERSARBPROC     _glGenBuffersARB;					
	static PFNGLBINDBUFFERARBPROC     _glBindBufferARB;					
	static PFNGLBUFFERDATAARBPROC     _glBufferDataARB;					
	static PFNGLDELETEBUFFERSARBPROC  _glDeleteBuffersARB;
	static PFNGLMAPBUFFERARBPROC      _glMapBufferARB;
    static PFNGLUNMAPBUFFERARBPROC    _glUnmapBufferARB;
	static PFNGLVERTEXATTRIBPOINTERARBPROC      _glVertexAttribPointerARB;
	static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  _glEnableVertexAttribArrayARB;
	static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC _glDisableVertexAttribArrayARB;
public :
	static PFNGLGENBUFFERSARBPROC     glGenBufferVBO();					
	static PFNGLBINDBUFFERARBPROC     glBindBufferVBO();					
	static PFNGLBUFFERDATAARBPROC     glBufferDataVBO();					
	static PFNGLDELETEBUFFERSARBPROC  glDeleteBufferVBO(); 
	static PFNGLMAPBUFFERARBPROC      glMapBufferVBO();
	static PFNGLUNMAPBUFFERARBPROC    glUnmapBufferVBO();
	static PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointer();
	static PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttrib();
	static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttrib();
};

#endif