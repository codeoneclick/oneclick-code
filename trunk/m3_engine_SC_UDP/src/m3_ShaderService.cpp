#include "m3_ShaderService.h"
#include <sys/stat.h>

PFNGLCREATEPROGRAMOBJECTARBPROC  m3_ShaderService::glCreateProgramObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC         m3_ShaderService::glDeleteObjectARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC     m3_ShaderService::glUseProgramObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC   m3_ShaderService::glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC         m3_ShaderService::glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC        m3_ShaderService::glCompileShaderARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC m3_ShaderService::glGetObjectParameterivARB = NULL;
PFNGLATTACHOBJECTARBPROC         m3_ShaderService::glAttachObjectARB = NULL;
PFNGLGETINFOLOGARBPROC           m3_ShaderService::glGetInfoLogARB = NULL;
PFNGLLINKPROGRAMARBPROC          m3_ShaderService::glLinkProgramARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC   m3_ShaderService::glGetUniformLocationARB = NULL;
PFNGLUNIFORM4FARBPROC            m3_ShaderService::glUniform4fARB = NULL;
PFNGLUNIFORM1IARBPROC            m3_ShaderService::glUniform1iARB = NULL;

m3_ShaderService::m3_ShaderService()
{
	glCreateProgramObjectARB  = (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
    glDeleteObjectARB         = (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
    glUseProgramObjectARB     = (PFNGLUSEPROGRAMOBJECTARBPROC)wglGetProcAddress("glUseProgramObjectARB");
    glCreateShaderObjectARB   = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
    glShaderSourceARB         = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
    glCompileShaderARB        = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
    glAttachObjectARB         = (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB");
    glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
    glLinkProgramARB          = (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
    glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)wglGetProcAddress("glGetUniformLocationARB");
    glUniform4fARB            = (PFNGLUNIFORM4FARBPROC)wglGetProcAddress("glUniform4fARB");
	glUniform1iARB            = (PFNGLUNIFORM1IARBPROC)wglGetProcAddress("glUniform1iARB");
}

unsigned char *m3_ShaderService::_ReadShaderFile( const char *fileName )
{
    FILE *file = fopen( fileName, "r" );

    if( file == NULL )
    {
        MessageBox( NULL, "Cannot open shader file!", "ERROR",
            MB_OK | MB_ICONEXCLAMATION );
		return 0;
    }

    struct _stat fileStats;

    if( _stat( fileName, &fileStats ) != 0 )
    {
        MessageBox( NULL, "Cannot get file stats for shader file!", "ERROR",
                    MB_OK | MB_ICONEXCLAMATION );
        return 0;
    }

    unsigned char *buffer = new unsigned char[fileStats.st_size];

	int bytes = fread( buffer, 1, fileStats.st_size, file );

    buffer[bytes] = 0;

	fclose( file );

	return buffer;
}

void m3_ShaderService::_insertShader(std::string key)
{
	/*m3_Shader *_Shader = new m3_Shader();

	const char *vertexShaderStrings[1];
    const char *fragmentShaderStrings[1];
    GLint bVertCompiled;
    GLint bFragCompiled;
    GLint bLinked;
    char str[4096];

	_Shader->_vertexShader = glCreateShaderObjectARB( GL_VERTEX_SHADER_ARB );

	unsigned char *vertexShaderAssembly = _ReadShaderFile( "Content\\shaders\\vertex_shader.vert" );
    vertexShaderStrings[0] = (char*)vertexShaderAssembly;
    glShaderSourceARB( _Shader->_vertexShader, 1, vertexShaderStrings, NULL );
    glCompileShaderARB( _Shader->_vertexShader);
    delete vertexShaderAssembly;

    glGetObjectParameterivARB( _Shader->_vertexShader, GL_OBJECT_COMPILE_STATUS_ARB, 
                               &bVertCompiled );
    if( bVertCompiled  == false )
	{
		glGetInfoLogARB(_Shader->_vertexShader, sizeof(str), NULL, str);
		MessageBox( NULL, str, "Vertex Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	}


	_Shader->_fragmentShader = glCreateShaderObjectARB( GL_FRAGMENT_SHADER_ARB );

    unsigned char *fragmentShaderAssembly = _ReadShaderFile( "Content\\shaders\\fragment_shader.frag" );
    fragmentShaderStrings[0] = (char*)fragmentShaderAssembly;
    glShaderSourceARB( _Shader->_fragmentShader, 1, fragmentShaderStrings, NULL );
    glCompileShaderARB( _Shader->_fragmentShader );
    delete fragmentShaderAssembly;

    glGetObjectParameterivARB( _Shader->_fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, 
                               &bFragCompiled );
    if( bFragCompiled == false )
	{
		glGetInfoLogARB( _Shader->_fragmentShader, sizeof(str), NULL, str );
		MessageBox( NULL, str, "Fragment Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	}


	_Shader->shaderProgram = glCreateProgramObjectARB();
    glAttachObjectARB( _Shader->shaderProgram , _Shader->_vertexShader );
    glAttachObjectARB( _Shader->shaderProgram , _Shader->_fragmentShader );

    //
    // Link the program object and print out the info log...
    //

    glLinkProgramARB( _Shader->shaderProgram );
    glGetObjectParameterivARB( _Shader->shaderProgram, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

    if( bLinked == false )
	{
		glGetInfoLogARB( _Shader->shaderProgram, sizeof(str), NULL, str );
		MessageBox( NULL, str, "Linking Error", MB_OK|MB_ICONEXCLAMATION );
	}

	_shaderContainer.insert(std::pair<std::string,m3_Shader*>(key,_Shader));*/

	m3_CgShader *_cgShader = new m3_CgShader();

	if(cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
        _cgShader->cg_VertexProfile = CG_PROFILE_ARBVP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
        _cgShader->cg_VertexProfile = CG_PROFILE_VP40;
	
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
        _cgShader->cg_PixelProfile = CG_PROFILE_ARBFP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
        _cgShader->cg_PixelProfile = CG_PROFILE_FP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
        _cgShader->cg_PixelProfile = CG_PROFILE_FP20;


	_cgShader->cg_Context = cgCreateContext();

	std::string pxShaderStr = "Content\\shaders\\" + key + "_px.cg";
	std::string vxShaderStr = "Content\\shaders\\" + key + "_vx.cg";
	
	_cgShader->cg_VertexProgram = cgCreateProgramFromFile(_cgShader->cg_Context,
										          CG_SOURCE,
												  vxShaderStr.c_str(),
										         _cgShader->cg_VertexProfile,
										         NULL, 
										         NULL );

	_cgShader->cg_PixelProgram = cgCreateProgramFromFile( _cgShader->cg_Context,
										         CG_SOURCE,
												 pxShaderStr.c_str(),
										         _cgShader->cg_PixelProfile,
										         NULL, 
										         NULL );

	cgGLLoadProgram( _cgShader->cg_VertexProgram );
	cgGLLoadProgram( _cgShader->cg_PixelProgram );
	
	_shaderContainer.insert(std::pair<std::string,m3_CgShader*>(key,_cgShader));
}

m3_CgShader* m3_ShaderService::GetShader(std::string value)
{
	std::map<std::string,m3_CgShader*>::iterator shaderIterator = _shaderContainer.find(value);
	if(shaderIterator != _shaderContainer.end())
		return shaderIterator->second;
	else
	{
		_insertShader(value);
		shaderIterator = _shaderContainer.find(value);
		if(shaderIterator != _shaderContainer.end())
			return shaderIterator->second;
		else
			return NULL;
	}
}