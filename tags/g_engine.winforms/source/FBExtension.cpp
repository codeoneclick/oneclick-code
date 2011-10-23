#include "FBExtension.h"


#include "VBExtension.h"

using namespace Extension;

PFNGLGENFRAMEBUFFERSEXTPROC           FBExtension::glGenFramebuffersEXT = NULL;	
PFNGLDELETEFRAMEBUFFERSEXTPROC        FBExtension::glDeleteFramebuffersEXT= NULL; 
PFNGLBINDFRAMEBUFFEREXTPROC           FBExtension::glBindFramebufferEXT = NULL;					
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC      FBExtension::glFramebufferTexture2DEXT = NULL;					
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC   FBExtension::glFramebufferRenderbufferEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC          FBExtension::glGenRenderbuffersEXT = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC       FBExtension::glDeleteRenderbuffersEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC          FBExtension::glBindRenderbufferEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC       FBExtension::glRenderbufferStorageEXT = NULL;

bool FBExtension::extensionSingleFlag = false;

FBExtension::FBExtension()
{
	if(extensionSingleFlag) return;
	FBExtension::glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC) wglGetProcAddress("glGenFramebuffersEXT");	
	FBExtension::glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC) wglGetProcAddress("glDeleteFramebuffersEXT"); 
	FBExtension::glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) wglGetProcAddress("glBindFramebufferEXT");					
	FBExtension::glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) wglGetProcAddress("glFramebufferTexture2DEXT");					
	FBExtension::glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
	FBExtension::glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) wglGetProcAddress("glGenRenderbuffersEXT");
	FBExtension::glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
	FBExtension::glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) wglGetProcAddress("glBindRenderbufferEXT");
	FBExtension::glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)wglGetProcAddress("glRenderbufferStorageEXT");
	extensionSingleFlag = true;
}