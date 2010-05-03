#include "m3_Entity.h"

m3_Entity::m3_Entity()
{
	_vertexBufferPtr = new m3_VertexBufferPtr();
	_vertexBufferId  = new m3_VertexBufferID();
	_cgShader = NULL;

	_mView = &m3_Core::GetCamera()->mView;
	_mProjection = &m3_Core::GetCamera()->mProjection;

	_vCameraEye = &m3_Core::GetCamera()->vPosition;
	_vLightDirection = new Vector3d(-100.0f,-10.0f,-100.0f);

	vPosition = Vector3d(0.0f,0.0f,0.0f);
	vRotation = Vector3d(0.0f,0.0f,0.0f);
	vScale    = Vector3d(1.0f,1.0f,1.0f);

	_shaderStr  = "";
	for(uint32 i = 0; i < 4; ++i)
		_textureStr[i] = "";
}

void m3_Entity::_UpdateWorldMatrix()
{
	_mTranslation = Translation(vPosition);
	_mRotationX = RotationX(vRotation.x);
	_mRotationY = RotationY(vRotation.y);
	_mRotationZ = RotationZ(vRotation.z);
	_mScale = Scale(vScale);
	_mRotation = _mRotationX*_mRotationY*_mRotationZ;
	_mWorld = _mScale*_mRotation*_mTranslation;
	_mWorldView = _mWorld*(*_mView);
	_mWorldViewProjection = _mWorldView*(*_mProjection);
}

void m3_Entity::_EnableShader()
{
	if(!_cgShader) return;

	cgGLBindProgram( _cgShader->cg_VertexProgram );
	cgGLBindProgram( _cgShader->cg_PixelProgram );

	cgGLEnableProfile( _cgShader->cg_VertexProfile );
	cgGLEnableProfile( _cgShader->cg_PixelProfile );
}

void m3_Entity::_DisableShader()
{
	if(!_cgShader) return;

	cgGLDisableProfile( _cgShader->cg_VertexProfile );
	cgGLDisableProfile( _cgShader->cg_PixelProfile );
}

void m3_Entity::_UpdateShaderParams()
{
	if(!_cgShader)
	{
		_cgShader = m3_Resource::ShaderContainer()->GetShader(_shaderStr);
		if(_cgShader)
		{
			_cgShaderParams.cg_Texture[0]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,  "Texture_01");
			_cgShaderParams.cg_Texture[1]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,  "Texture_02");
			_cgShaderParams.cg_mWorldViewProjection    = cgGetNamedParameter(_cgShader->cg_VertexProgram, "mWorldViewProjection" );
		    _cgShaderParams.cg_mWorldViewInverse       = cgGetNamedParameter(_cgShader->cg_PixelProgram,  "mWorldViewInverse" );
	        _cgShaderParams.cg_vCamera		           = cgGetNamedParameter(_cgShader->cg_PixelProgram,  "vCameraEye" );
	        _cgShaderParams.cg_vLight                  = cgGetNamedParameter(_cgShader->cg_PixelProgram,  "vLightDirection");
			_cgShaderParams.cg_fTimer                  = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "fTimer");
		}
	}

	if(!_cgShader) return;

	for(uint32 i = 0; i < 4; i++)
		if(_textureStr[i].length())
		{
			cgGLSetTextureParameter(_cgShaderParams.cg_Texture[i], m3_Resource::TextureContainer()->GetTexture(_textureStr[i]) );
		    cgGLEnableTextureParameter(_cgShaderParams.cg_Texture[i]);
		}

	float fEyePosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float fLightVector[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float fAngle = 0.0f;
	fAngle += 0.01f;
	fLightVector[0] = cos(fAngle);
	fLightVector[1] = sin(fAngle);
	fLightVector[2] = sin(fAngle);

	float fLength = sqrtf( fLightVector[0]*fLightVector[0] +
						   fLightVector[1]*fLightVector[1] +
						   fLightVector[2]*fLightVector[2] );
	fLightVector[0] /= fLength;
	fLightVector[1] /= fLength;
	fLightVector[2] /= fLength;
	
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mWorldViewProjection,_mWorldViewProjection.m);

	cgGLSetParameter4fv( _cgShaderParams.cg_vCamera, (float*)&m3_Core::GetCamera()->vPosition );
	cgGLSetParameter4fv( _cgShaderParams.cg_vLight, fLightVector );
	cgGLSetParameter1fv( _cgShaderParams.cg_fTimer, &_textureAnimSpeed );
}