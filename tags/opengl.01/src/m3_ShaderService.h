#pragma once
#ifndef _M3_SHADERSERVICE_H_
#define _M3_SHADERSERVICE_H_

#include <windows.h>
#include <Cg/Cg.h>
#include <Cg/cgGL.h>
#include "glext.h"
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>

struct m3_Shader
{
	GLhandleARB shaderProgram;
	GLhandleARB _vertexShader;
	GLhandleARB _fragmentShader;
};

struct m3_ShaderBasicParams
{
	GLuint Texture;
};

struct m3_CgShader
{
	CGcontext   cg_Context;
	CGprofile   cg_VertexProfile;
	CGprofile   cg_PixelProfile;
	CGprogram   cg_VertexProgram;
	CGprogram   cg_PixelProgram;
};

struct m3_CgShaderBasicParams
{
	CGparameter cg_Texture[8];
	CGparameter cg_mWorldViewProjection;
	CGparameter cg_mWorldViewInverse;
	CGparameter cg_vCamera;
	CGparameter cg_vLight;
	CGparameter cg_fTimer;

	m3_CgShaderBasicParams()
	{
		for(unsigned int i = 0; i < 8; ++i)
			cg_Texture[i] = NULL;
		cg_mWorldViewProjection = NULL;
		cg_mWorldViewInverse = NULL;
		cg_vCamera = NULL;
		cg_vLight = NULL;
		cg_fTimer = NULL;
	}
};

class m3_ShaderService
{
	private :
		std::map<std::string,m3_CgShader*> _shaderContainer;
		std::vector<std::string> _requestShader;
		
		HANDLE _thread;
		CRITICAL_SECTION shaderRequestCriticalSection;

		void _insertShader(std::string key);
		unsigned char* _ReadShaderFile(const char *fileName);
	public :
		void _shaderLoadThread();
		m3_CgShader* GetShader(std::string value);
		m3_ShaderService();	

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

#endif