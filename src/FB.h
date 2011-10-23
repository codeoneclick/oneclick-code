#ifndef _FB_H_
#define _FB_H_

#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

#define glCreateFB           glCreateFB()
#define glDeleteFB           glDeleteFB()
#define glBindFB             glBindFB()
#define glSetTextureFB       glSetTextureFB()
#define glSetRenderBufferFB  glSetRenderBufferFB()

#define glCreateRB           glCreateRB()
#define glDeleteRB           glDeleteRB()
#define glBindRB             glBindRB()
#define glAllocRB            glAllocRB()

class FB
{
private :
	static PFNGLGENFRAMEBUFFERSEXTPROC                     _glGenFramebuffersEXT;                     
	static PFNGLDELETEFRAMEBUFFERSEXTPROC                  _glDeleteFramebuffersEXT;                   
	static PFNGLBINDFRAMEBUFFEREXTPROC                     _glBindFramebufferEXT;                      
	static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC                _glFramebufferTexture2DEXT;                 
	static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC             _glFramebufferRenderbufferEXT;              

	static PFNGLGENRENDERBUFFERSEXTPROC                    _glGenRenderbuffersEXT;                     
	static PFNGLDELETERENDERBUFFERSEXTPROC                 _glDeleteRenderbuffersEXT;                 
	static PFNGLBINDRENDERBUFFEREXTPROC                    _glBindRenderbufferEXT;                    
	static PFNGLRENDERBUFFERSTORAGEEXTPROC                 _glRenderbufferStorageEXT;                  

public :
	static PFNGLGENFRAMEBUFFERSEXTPROC			           glCreateFB;	
	static PFNGLDELETEFRAMEBUFFERSEXTPROC		           glDeleteFB; 
	static PFNGLBINDFRAMEBUFFEREXTPROC			           glBindFB;					
	static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC			       glSetTextureFB;					
	static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC			   glSetRenderBufferFB;

	static PFNGLGENRENDERBUFFERSEXTPROC                    glCreateRB;
	static PFNGLDELETERENDERBUFFERSEXTPROC		           glDeleteRB;
	static PFNGLBINDRENDERBUFFEREXTPROC                    glBindRB;
	static PFNGLRENDERBUFFERSTORAGEEXTPROC		           glAllocRB;
};

#endif