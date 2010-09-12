#include "FB.h"

#include "windows.h"

PFNGLGENFRAMEBUFFERSEXTPROC                     FB::_glGenFramebuffersEXT = NULL;                     
PFNGLDELETEFRAMEBUFFERSEXTPROC                  FB::_glDeleteFramebuffersEXT = NULL;                   
PFNGLBINDFRAMEBUFFEREXTPROC                     FB::_glBindFramebufferEXT = NULL;                      
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC                FB::_glFramebufferTexture2DEXT = NULL;                 
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC             FB::_glFramebufferRenderbufferEXT = NULL;              

PFNGLGENRENDERBUFFERSEXTPROC                    FB::_glGenRenderbuffersEXT = NULL;                     
PFNGLDELETERENDERBUFFERSEXTPROC                 FB::_glDeleteRenderbuffersEXT = NULL;                 
PFNGLBINDRENDERBUFFEREXTPROC                    FB::_glBindRenderbufferEXT = NULL;                    
PFNGLRENDERBUFFERSTORAGEEXTPROC                 FB::_glRenderbufferStorageEXT = NULL;  

PFNGLGENFRAMEBUFFERSEXTPROC FB::glCreateFB	
{
	if(_glGenFramebuffersEXT == NULL)
		_glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC) wglGetProcAddress("glGenFramebuffersEXT");
	return _glGenFramebuffersEXT;
}
PFNGLDELETEFRAMEBUFFERSEXTPROC FB::glDeleteFB
{
	if(_glDeleteFramebuffersEXT == NULL)
		_glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
	return _glDeleteFramebuffersEXT;
}
PFNGLBINDFRAMEBUFFEREXTPROC  FB::glBindFB
{
	if(_glBindFramebufferEXT == NULL)
		_glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) wglGetProcAddress("glBindFramebufferEXT");
	return _glBindFramebufferEXT;
}
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC  FB::glSetTextureFB
{
	if(_glFramebufferTexture2DEXT == NULL)
		_glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
	return _glFramebufferTexture2DEXT;
}

PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC  FB::glSetRenderBufferFB
{
	if(_glFramebufferRenderbufferEXT == NULL)
		_glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
	return _glFramebufferRenderbufferEXT;
}


PFNGLGENRENDERBUFFERSEXTPROC  FB::glCreateRB
{
	if(_glGenRenderbuffersEXT == NULL)
		_glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) wglGetProcAddress("glGenRenderbuffersEXT");
	return _glGenRenderbuffersEXT;
}

PFNGLDELETERENDERBUFFERSEXTPROC FB::glDeleteRB
{
	if(_glDeleteRenderbuffersEXT == NULL)
		_glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
	return _glDeleteRenderbuffersEXT;
}

PFNGLBINDRENDERBUFFEREXTPROC  FB::glBindRB
{
	if(_glBindRenderbufferEXT == NULL)
		_glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) wglGetProcAddress("glBindRenderbufferEXT");
	return _glBindRenderbufferEXT;
}

PFNGLRENDERBUFFERSTORAGEEXTPROC FB::glAllocRB
{
	if(_glRenderbufferStorageEXT == NULL)
		_glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)wglGetProcAddress("glRenderbufferStorageEXT");
	return _glRenderbufferStorageEXT;
}

