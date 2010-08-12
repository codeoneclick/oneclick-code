#include "ShaderService.h"

using namespace service;

ShaderService::ShaderService()
{

}

void ShaderService::_insertShader(std::string key)
{
	type::CGShader *cgShader = new type::CGShader();

	if(cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
        cgShader->vertexProfile = CG_PROFILE_ARBVP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
        cgShader->vertexProfile = CG_PROFILE_VP40;
	
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
        cgShader->pixelProfile = CG_PROFILE_ARBFP1;
    else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
        cgShader->pixelProfile = CG_PROFILE_FP30;
	else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
        cgShader->pixelProfile = CG_PROFILE_FP20;


	cgShader->context = cgCreateContext();

	std::string pxShaderStr = "Content\\shaders\\" + key + "_px.cg";
	std::string vxShaderStr = "Content\\shaders\\" + key + "_vx.cg";
	
	cgShader->vertexProgram = cgCreateProgramFromFile(cgShader->context,
										          CG_SOURCE,
												  vxShaderStr.c_str(),
										         cgShader->vertexProfile,
										         NULL, 
										         NULL );

	cgShader->pixelProgram = cgCreateProgramFromFile(cgShader->context,
										         CG_SOURCE,
												 pxShaderStr.c_str(),
										         cgShader->pixelProfile,
										         NULL, 
										         NULL );

	cgGLLoadProgram( cgShader->vertexProgram );
	cgGLLoadProgram( cgShader->pixelProgram );
	
	_shaderContainer.insert(std::pair<std::string,type::CGShader*>(key,cgShader));
}

type::CGShader* ShaderService::GetShader(std::string value)
{
	std::map<std::string,type::CGShader*>::iterator shaderIterator = _shaderContainer.find(value);
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