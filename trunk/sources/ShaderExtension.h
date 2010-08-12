#ifndef _SHADEREXTENSION_H_
#define _SHADEREXTENSION_H_	
#include "Windows.h"
#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "glext.h"

namespace extension
{

class ShaderExtension
{
public :
	static PFNGLCREATEPROGRAMOBJECTARBPROC  glCreateProgramObjectARB;
	static PFNGLDELETEOBJECTARBPROC         glDeleteObjectARB;
	static PFNGLUSEPROGRAMOBJECTARBPROC     glUseProgramObjectARB;
	static PFNGLCREATESHADEROBJECTARBPROC   glCreateShaderObjectARB;
	static PFNGLSHADERSOURCEARBPROC         glShaderSourceARB;
	static PFNGLCOMPILESHADERARBPROC        glCompileShaderARB;
	static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
	static PFNGLATTACHOBJECTARBPROC         glAttachObjectARB;
	static PFNGLGETINFOLOGARBPROC           glGetInfoLogARB;
	static PFNGLLINKPROGRAMARBPROC          glLinkProgramARB;
	static PFNGLGETUNIFORMLOCATIONARBPROC   glGetUniformLocationARB;
	static PFNGLUNIFORM4FARBPROC            glUniform4fARB;
	static PFNGLUNIFORM1IARBPROC            glUniform1iARB;
};

};

#endif