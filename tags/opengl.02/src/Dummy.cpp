#include "Dummy.h"

#include "RenderController.h"

Dummy::Dummy()
{
	_vertexBufferPtr2 = NULL;
	_cgShader = NULL;

	_mView = &Core::GetCamera()->mView;
	_mProjection = &Core::GetCamera()->mProjection;

	_vCameraEye = &Core::GetCamera()->vPosition;
	_vLightDirection = new Vector3d(-100.0f,-10.0f,-100.0f);

	vPosition = Vector3d(0.0f,0.0f,0.0f);
	vRotation = Vector3d(0.0f,0.0f,0.0f);
	vScale    = Vector3d(1.0f,1.0f,1.0f);

	_shaderStr  = "";
	for(unsigned int i = 0; i < 8; ++i)
		_textureStr[i] = "";
}

void Dummy::_UpdateWorldMatrix()
{
	_mTranslation = Translation(vPosition);
	_mRotationX = RotationX(vRotation.x);
	_mRotationY = RotationY(vRotation.y);
	_mRotationZ = RotationZ(vRotation.z);
	_mScale = Scale(vScale);
	_mRotation = _mRotationY*_mRotationZ*_mRotationX;
	_mWorld = _mScale*_mRotation*_mTranslation;
	_mWorldView = _mWorld*(*_mView);
	_mWorldViewInverse = Inverse(_mWorldView);
	_mWorldViewProjection = _mWorldView*(*_mProjection);
}

void Dummy::EnableShader(std::string vs_name, std::string ps_name)
{
	if(!_cgShader) return;

	if(vs_name.length())
	{
		cgGLBindProgram( _cgShader->cg_VertexProgram );
		cgGLEnableProfile( _cgShader->cg_VertexProfile );
	}

	if(ps_name.length())
	{
		cgGLBindProgram( _cgShader->cg_PixelProgram );
		cgGLEnableProfile( _cgShader->cg_PixelProfile );
	}
}

void Dummy::DisableShader()
{
	if(!_cgShader) return;

	cgGLDisableProfile( _cgShader->cg_VertexProfile );
	cgGLDisableProfile( _cgShader->cg_PixelProfile );
}

void Dummy::_UpdateShaderParams()
{
	if(!_cgShader)
	{
		_cgShader = Resource::ShaderContainer()->GetShader(_shaderStr);
		if(_cgShader)
		{
			_cgShaderParams.cg_Texture[0]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_01");
			_cgShaderParams.cg_Texture[1]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_02");
			_cgShaderParams.cg_Texture[2]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_03");
			_cgShaderParams.cg_Texture[3]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_04");
			_cgShaderParams.cg_Texture[4]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_05");
			_cgShaderParams.cg_Texture[5]			   = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "Texture_06");
			_cgShaderParams.cg_mWorldViewProjection    = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "mWorldViewProjection" );
		    _cgShaderParams.cg_mWorldViewInverse       = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "mWorldViewInverse" );
			_cgShaderParams.cg_mWorldView              = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "mWorldView" );
	        _cgShaderParams.cg_vCamera		           = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "vCameraEye" );
	        _cgShaderParams.cg_vLight                  = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "vLightDirection");
			_cgShaderParams.cg_fVerTimer               = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "fTimer");
			_cgShaderParams.cg_fPixTimer               = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "fTimer");
			_cgShaderParams.cg_mWorld                  = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "mWorld");
			_cgShaderParams.cg_mReflection             = cgGetNamedParameter(_cgShader->cg_VertexProgram,  "mReflection");
			_cgShaderParams.cg_fReflectionPass         = cgGetNamedParameter(_cgShader->cg_PixelProgram,   "bReflectionPass");
			_cgShaderParams.cg_mProjection             = cgGetNamedParameter(_cgShader->cg_VertexProgram,   "mProjection");
		}
	}

	if(!_cgShader) return;

	for(unsigned int i = 0; i < 8; i++)
		if(_textureStr[i].length())
		{
			if(_textureStr[i] == "REFLECTION")
			{
				cgGLSetTextureParameter(_cgShaderParams.cg_Texture[i], RenderController::GetRenderTexture(RENDER_REFLECTION_TEXTURE) );
				cgGLEnableTextureParameter(_cgShaderParams.cg_Texture[i]);
				continue;
			}
			if(_textureStr[i] == "REFRACTION")
			{
				cgGLSetTextureParameter(_cgShaderParams.cg_Texture[i], RenderController::GetRenderTexture(RENDER_REFRACTION_TEXTURE) );
				cgGLEnableTextureParameter(_cgShaderParams.cg_Texture[i]);
				continue;
			}
			if(_textureStr[i] == "SCREEN")
			{
				cgGLSetTextureParameter(_cgShaderParams.cg_Texture[i], RenderController::GetRenderTexture(RENDER_SIMPLE_TEXTURE) );
				cgGLEnableTextureParameter(_cgShaderParams.cg_Texture[i]);
				continue;
			}
			cgGLSetTextureParameter(_cgShaderParams.cg_Texture[i], Resource::TextureContainer()->GetTexture(_textureStr[i]) );
		    cgGLEnableTextureParameter(_cgShaderParams.cg_Texture[i]);
		}

	static float fLightVector[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float fAngle = 0.0f;
	fAngle += 0.0001f;
	fLightVector[0] = cos(fAngle);
	fLightVector[1] = 0.0f;
	fLightVector[2] = sin(fAngle);
	
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mWorldViewProjection,_mWorldViewProjection.m);
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mWorldView,_mWorldView.m);
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mWorldViewInverse,_mWorldViewInverse.m);
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mWorld,_mWorld.m);
	cgGLSetMatrixParameterfc(_cgShaderParams.cg_mProjection,_mProjection->m);

	cgGLSetParameter4fv( _cgShaderParams.cg_vCamera, (float*)&Core::GetCamera()->vPosition );
	cgGLSetParameter4fv( _cgShaderParams.cg_vLight, fLightVector );
	
	static float fTimer = 0.0f;
	fTimer += 0.0001f;

	if(Core::GetCamera()->vPosition.y < WATER_LEVEL)
		fTimer = -0.0001f;

	cgGLSetParameter1fv( _cgShaderParams.cg_fVerTimer, &fTimer );
	cgGLSetParameter1fv( _cgShaderParams.cg_fPixTimer, &fTimer );
}


void Dummy::EnableVB()
{
	unsigned int vertexBufferOffset = 0;
	unsigned int vertexBufferOffsetInc = 0;
	
	VB::glBindVB(GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->vertexBufferId);

	if(_vertexBufferPtr->bPosition)
	{
		VB::glEnableVertexAttrib(0);
		VB::glBindDataVB_2(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);	
	}

	vertexBufferOffsetInc = 3;
	vertexBufferOffset += sizeof(float) * vertexBufferOffsetInc;

	if(_vertexBufferPtr->bTexCoord)
	{
		VB::glEnableVertexAttrib(1);
		VB::glBindDataVB_2(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);
	}

	vertexBufferOffsetInc = 2;
	vertexBufferOffset += sizeof(float) * vertexBufferOffsetInc;

	if(_vertexBufferPtr->bNormal)
	{
		VB::glEnableVertexAttrib(2);
		VB::glBindDataVB_2(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);
	}

	vertexBufferOffsetInc = 3;
	vertexBufferOffset += sizeof(float) * vertexBufferOffsetInc;

	if(_vertexBufferPtr->bTangent)
	{
		VB::glEnableVertexAttrib(3);
		VB::glBindDataVB_2(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);	
	}

	vertexBufferOffsetInc = 3;
	vertexBufferOffset += sizeof(float) * vertexBufferOffsetInc;

	if(_vertexBufferPtr->bBinormal)
	{
		VB::glEnableVertexAttrib(4);
		VB::glBindDataVB_2(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);
	}

	vertexBufferOffsetInc = 3;
	vertexBufferOffset += sizeof(float) * vertexBufferOffsetInc;

	if(_vertexBufferPtr->bExtValue)
	{
		VB::glEnableVertexAttrib(5);
		VB::glBindDataVB_2(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)vertexBufferOffset);
	}
}

void Dummy::EnableIB()
{
	VB::glBindVB(GL_ELEMENT_ARRAY_BUFFER_ARB, _vertexBufferPtr->indexBufferId);
    glIndexPointer(GL_UNSIGNED_INT, NULL, NULL);
}