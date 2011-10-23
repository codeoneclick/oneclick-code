#ifndef _FBEXTENSION_H_
#define _FBEXTENSION_H_

#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

namespace Extension
{
class FBExtension
{
private :
	static bool extensionSingleFlag;
public :
	static PFNGLGENFRAMEBUFFERSEXTPROC           glGenFramebuffersEXT;                     
	static PFNGLDELETEFRAMEBUFFERSEXTPROC        glDeleteFramebuffersEXT;                   
	static PFNGLBINDFRAMEBUFFEREXTPROC           glBindFramebufferEXT;                      
	static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC      glFramebufferTexture2DEXT;                 
	static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC   glFramebufferRenderbufferEXT;              
	static PFNGLGENRENDERBUFFERSEXTPROC          glGenRenderbuffersEXT;                     
	static PFNGLDELETERENDERBUFFERSEXTPROC       glDeleteRenderbuffersEXT;                 
	static PFNGLBINDRENDERBUFFEREXTPROC          glBindRenderbufferEXT;                    
	static PFNGLRENDERBUFFERSTORAGEEXTPROC       glRenderbufferStorageEXT;  
public :
	FBExtension();
};
};
#endif