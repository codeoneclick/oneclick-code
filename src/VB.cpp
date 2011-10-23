#include "VB.h"

#include <windows.h>

PFNGLGENBUFFERSARBPROC				VB::_glGenBuffersARB = NULL;					
PFNGLBINDBUFFERARBPROC				VB::_glBindBufferARB = NULL;					
PFNGLBUFFERDATAARBPROC				VB::_glBufferDataARB = NULL;					
PFNGLDELETEBUFFERSARBPROC			VB::_glDeleteBuffersARB = NULL;
PFNGLMAPBUFFERARBPROC				VB:: _glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC				VB::_glUnmapBufferARB = NULL;
PFNGLCLIENTACTIVETEXTUREPROC        VB:: _glClientActiveTextureCoordARB = NULL;
PFNGLVERTEXATTRIBPOINTERPROC        VB:: _glVertexAttribPointer = NULL;
PFNGLGETATTRIBLOCATIONPROC          VB:: _glGetAttribLocation = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC    VB:: _glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC    VB:: _glDisableVertexAttribArray = NULL;

PFNGLGENBUFFERSARBPROC  VB::glCreateVB	
{
	if(_glGenBuffersARB == NULL)
		_glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	return _glGenBuffersARB;
}
PFNGLBINDBUFFERARBPROC     VB::glBindVB
{
	if(_glBindBufferARB == NULL)
		_glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	return _glBindBufferARB;
}
PFNGLBUFFERDATAARBPROC     VB::glWriteDataVB
{
	if(_glBufferDataARB == NULL)
		_glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	return _glBufferDataARB;
}
PFNGLDELETEBUFFERSARBPROC  VB::glDeleteVB
{
	if(_glDeleteBuffersARB == NULL)
		_glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
	return _glDeleteBuffersARB;
}

PFNGLMAPBUFFERARBPROC  VB::glLockVB
{
	if(_glMapBufferARB == NULL)
		_glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
	return _glMapBufferARB;
}

PFNGLUNMAPBUFFERARBPROC    VB::glUnlockVB
{
	if(_glUnmapBufferARB == NULL)
		_glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
	return _glUnmapBufferARB;
}

PFNGLCLIENTACTIVETEXTUREPROC VB::glBindDataVB
{
	if(_glClientActiveTextureCoordARB == NULL)
		_glClientActiveTextureCoordARB = (PFNGLCLIENTACTIVETEXTUREPROC)wglGetProcAddress("glClientActiveTexture");
	return _glClientActiveTextureCoordARB;
}

PFNGLVERTEXATTRIBPOINTERPROC VB::glBindDataVB_2
{
	if(_glVertexAttribPointer == NULL)
		_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	return _glVertexAttribPointer;
}

PFNGLGETATTRIBLOCATIONPROC VB::glGetDataLocation
{
	if(_glGetAttribLocation == NULL)
		_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	return _glGetAttribLocation;
}

PFNGLENABLEVERTEXATTRIBARRAYPROC VB::glEnableVertexAttrib
{
	if(_glEnableVertexAttribArray == NULL)
		_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	return _glEnableVertexAttribArray;
}

PFNGLDISABLEVERTEXATTRIBARRAYPROC VB::glDisableVertexAttrib
{
	if(_glDisableVertexAttribArray == NULL)
		_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	return _glDisableVertexAttribArray;
}