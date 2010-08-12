#include "VBExtension.h"

using namespace Extension;

PFNGLGENBUFFERSARBPROC			  VBExtension::glGenBuffersARB = NULL;	
PFNGLDELETEBUFFERSARBPROC		  VBExtension::glDeleteBuffersARB = NULL; 
PFNGLBINDBUFFERARBPROC			  VBExtension::glBindBufferARB = NULL;					
PFNGLBUFFERDATAARBPROC			  VBExtension::glBufferDataARB = NULL;					
PFNGLMAPBUFFERARBPROC			  VBExtension::glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC           VBExtension::glUnmapBufferARB = NULL;
PFNGLCLIENTACTIVETEXTUREPROC	  VBExtension::glClientActiveTextureCoordARB = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      VBExtension::glVertexAttribPointer = NULL;
PFNGLGETATTRIBLOCATIONPROC        VBExtension::glGetAttribLocation = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  VBExtension::glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC VBExtension::glDisableVertexAttribArray = NULL;

bool VBExtension::extensionSingleFlag = false;

VBExtension::VBExtension()
{
	if(extensionSingleFlag) return;
	VBExtension::glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");	
	VBExtension::glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB"); 
	VBExtension::glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");					
	VBExtension::glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");					
	VBExtension::glMapBufferARB = (PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB");
	VBExtension::glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB");
	VBExtension::glClientActiveTextureCoordARB = (PFNGLCLIENTACTIVETEXTUREPROC)wglGetProcAddress("glClientActiveTexture");
	VBExtension::glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	VBExtension::glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
    VBExtension::glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	VBExtension::glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	extensionSingleFlag = true;
}