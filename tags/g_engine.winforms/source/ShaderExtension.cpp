#include "ShaderExtension.h"

using namespace extension;

PFNGLCREATEPROGRAMOBJECTARBPROC  ShaderExtension::glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
PFNGLDELETEOBJECTARBPROC         ShaderExtension::glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
PFNGLUSEPROGRAMOBJECTARBPROC     ShaderExtension::glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)wglGetProcAddress("glUseProgramObjectARB");
PFNGLCREATESHADEROBJECTARBPROC   ShaderExtension::glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
PFNGLSHADERSOURCEARBPROC         ShaderExtension::glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
PFNGLCOMPILESHADERARBPROC        ShaderExtension::glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
PFNGLGETOBJECTPARAMETERIVARBPROC ShaderExtension::glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
PFNGLATTACHOBJECTARBPROC         ShaderExtension::glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB");
PFNGLGETINFOLOGARBPROC           ShaderExtension::glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
PFNGLLINKPROGRAMARBPROC          ShaderExtension::glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
PFNGLGETUNIFORMLOCATIONARBPROC   ShaderExtension::glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)wglGetProcAddress("glGetUniformLocationARB");
PFNGLUNIFORM4FARBPROC            ShaderExtension::glUniform4fARB = (PFNGLUNIFORM4FARBPROC)wglGetProcAddress("glUniform4fARB");
PFNGLUNIFORM1IARBPROC            ShaderExtension::glUniform1iARB = (PFNGLUNIFORM1IARBPROC)wglGetProcAddress("glUniform1iARB");
