#include "m3_VBO.h"

PFNGLGENBUFFERSARBPROC     m3_VBO::_glGenBuffersARB = NULL;					
PFNGLBINDBUFFERARBPROC     m3_VBO::_glBindBufferARB = NULL;					
PFNGLBUFFERDATAARBPROC     m3_VBO::_glBufferDataARB = NULL;					
PFNGLDELETEBUFFERSARBPROC  m3_VBO::_glDeleteBuffersARB = NULL;
PFNGLMAPBUFFERARBPROC      m3_VBO:: _glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC    m3_VBO::_glUnmapBufferARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC      m3_VBO::_glVertexAttribPointerARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC  m3_VBO::_glEnableVertexAttribArrayARB = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC m3_VBO::_glDisableVertexAttribArrayARB = NULL;

PFNGLGENBUFFERSARBPROC     m3_VBO::glGenBufferVBO()	
{
	if(_glGenBuffersARB == NULL)
		_glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	return _glGenBuffersARB;
}
PFNGLBINDBUFFERARBPROC     m3_VBO::glBindBufferVBO()
{
	if(_glBindBufferARB == NULL)
		_glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	return _glBindBufferARB;
}
PFNGLBUFFERDATAARBPROC     m3_VBO::glBufferDataVBO()	
{
	if(_glBufferDataARB == NULL)
		_glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	return _glBufferDataARB;
}
PFNGLDELETEBUFFERSARBPROC  m3_VBO::glDeleteBufferVBO()
{
	if(_glDeleteBuffersARB == NULL)
		_glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
	return _glDeleteBuffersARB;
}

PFNGLMAPBUFFERARBPROC      m3_VBO::glMapBufferVBO()
{
	if(_glMapBufferARB == NULL)
		_glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
	return _glMapBufferARB;
}

PFNGLUNMAPBUFFERARBPROC    m3_VBO::glUnmapBufferVBO()
{
	if(_glUnmapBufferARB == NULL)
		_glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
	return _glUnmapBufferARB;
}

PFNGLVERTEXATTRIBPOINTERARBPROC      m3_VBO::glVertexAttribPointer()
{
	if(_glVertexAttribPointerARB == NULL)
		_glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)wglGetProcAddress("glVertexAttribPointerARB");
	return _glVertexAttribPointerARB;
}

PFNGLENABLEVERTEXATTRIBARRAYARBPROC  m3_VBO::glEnableVertexAttrib()
{
	if(_glEnableVertexAttribArrayARB == NULL)
		_glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glEnableVertexAttribArrayARB");
	return _glEnableVertexAttribArrayARB;
}

PFNGLDISABLEVERTEXATTRIBARRAYARBPROC m3_VBO::glDisableVertexAttrib()
{
	if(_glDisableVertexAttribArrayARB == NULL)
		_glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glDisableVertexAttribArrayARB");
	return _glDisableVertexAttribArrayARB;
}

	
