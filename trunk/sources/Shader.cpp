#include "Shader.h"
#include "Resource.h"

CShader::CShader()
{

}

CShader::~CShader()
{

}

void CShader::Create(std::string name)
{
	_cgShader = Resource::GetShaderControllerInstance()->GetShader(name);
	if(_cgShader)
	{
		_cgShaderParams.texture[0]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_01");
		_cgShaderParams.texture[1]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_02");
		_cgShaderParams.texture[2]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_03");
		_cgShaderParams.texture[3]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_04");
		_cgShaderParams.texture[4]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_05");
		_cgShaderParams.texture[5]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_06");
		_cgShaderParams.texture[6]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_07");
		_cgShaderParams.texture[7]			   = cgGetNamedParameter(_cgShader->pixelProgram,   "Texture_08");
		_cgShaderParams.fClipHeigth			   = cgGetNamedParameter(_cgShader->pixelProgram,   "fClipHeigth");
		_cgShaderParams.bClipInc			   = cgGetNamedParameter(_cgShader->pixelProgram,   "bClipInc");
		_cgShaderParams.fTimer			       = cgGetNamedParameter(_cgShader->pixelProgram,   "fTimer");
		_cgShaderParams.mWorldViewProjection   = cgGetNamedParameter(_cgShader->vertexProgram,  "mWorldViewProjection" );
		_cgShaderParams.mWorld				   = cgGetNamedParameter(_cgShader->vertexProgram,  "mWorld" );
	    _cgShaderParams.vCameraPosition		   = cgGetNamedParameter(_cgShader->vertexProgram,  "vCameraPosition" );
	    _cgShaderParams.vLightDirection        = cgGetNamedParameter(_cgShader->vertexProgram,  "vLightDirection");
	}
}

void CShader::Enable()
{
	if(!_cgShader) return;

	cgGLBindProgram( _cgShader->vertexProgram );
	cgGLEnableProfile( _cgShader->vertexProfile );

	cgGLBindProgram( _cgShader->pixelProgram );
	cgGLEnableProfile( _cgShader->pixelProfile );
}

void CShader::Disable()
{
	if(!_cgShader) return;

	cgGLDisableProfile( _cgShader->vertexProfile );
	cgGLDisableProfile( _cgShader->pixelProfile );
}

void CShader::SetWVPMatrix(math::matrix::Matrix4x4 &matrix)
{
	cgGLSetMatrixParameterfc(_cgShaderParams.mWorldViewProjection, matrix.m);
}

void CShader::SetWMatrix(math::matrix::Matrix4x4 &matrix)
{
	cgGLSetMatrixParameterfc(_cgShaderParams.mWorld, matrix.m);
}

void CShader::SetTexture(unsigned int index, unsigned int addr_ptr)
{
	cgGLSetTextureParameter(_cgShaderParams.texture[index], addr_ptr);
	cgGLEnableTextureParameter(_cgShaderParams.texture[index]);
}

void CShader::SetCamera(math::vector::Vector3d &position)
{
	cgGLSetParameter3fv( _cgShaderParams.vCameraPosition, position.value );
}

void CShader::SetLight(math::vector::Vector3d &direction)
{
	cgGLSetParameter3fv( _cgShaderParams.vLightDirection, direction.value );
}

void CShader::SetClip(float incValue, float clipValue)
{
	cgGLSetParameter1fv( _cgShaderParams.bClipInc, &incValue );
	cgGLSetParameter1fv( _cgShaderParams.fClipHeigth, &clipValue );
}

void CShader::UpdateTimer()
{
	float fTime = static_cast<float>(GetTickCount());
	cgGLSetParameter1fv( _cgShaderParams.fTimer, &fTime );
}