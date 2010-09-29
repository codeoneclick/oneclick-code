#include "Shader.h"
#include "Resource.h"
#include "Device.h"
#include "Window.h"

using namespace Core;

CShader::CShader()
{
	m_is_read_data = false;
	m_is_commit = false;
}

CShader::~CShader()
{

}

void CShader::ReadData(std::string _value)
{	
	if(core::Window::m_D3DRender)
	{
		LPD3DXBUFFER error_buffer = NULL;
		HRESULT error_result = NULL;
		char* error_text = NULL;
		_value += ".fx";
		
		error_result = D3DXCreateEffectFromFile(core::Window::m_D3DDevice, _value.c_str(), NULL, NULL, 0, NULL, &_m_dx_hlsl_shader, &error_buffer);
	
		if(FAILED( error_result ))
		{
			error_text = ( char* )error_buffer->GetBufferPointer();
			MessageBox(NULL, error_text ,"ShaderController::SHADER", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else
	{

	}
	m_is_read_data = true;
}

void CShader::Commit(std::string _value)
{
	if(core::Window::m_D3DRender)
	{

	}
	else
	{
		_m_ogl_cg_shader = new SCGShader();

		if(cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
			_m_ogl_cg_shader->m_vs_profile = CG_PROFILE_ARBVP1;
		else if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
			_m_ogl_cg_shader->m_vs_profile = CG_PROFILE_VP40;
	
		if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
			_m_ogl_cg_shader->m_ps_profile = CG_PROFILE_ARBFP1;
		else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
			_m_ogl_cg_shader->m_ps_profile = CG_PROFILE_FP30;
		else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
			_m_ogl_cg_shader->m_ps_profile = CG_PROFILE_FP20;

		_m_ogl_cg_shader->m_context = cgCreateContext();

		std::string vs_str = _value + "_vs.cg";
		std::string ps_str = _value + "_ps.cg";

		_m_ogl_cg_shader->m_vs_program = cgCreateProgramFromFile(_m_ogl_cg_shader->m_context,
														  CG_SOURCE,
														  vs_str.c_str(),
														  _m_ogl_cg_shader->m_vs_profile,
														  NULL, 
														  NULL );

		_m_ogl_cg_shader->m_ps_program = cgCreateProgramFromFile(_m_ogl_cg_shader->m_context,
										         CG_SOURCE,
												 ps_str.c_str(),
												 _m_ogl_cg_shader->m_ps_profile,
										         NULL, 
										         NULL );

		cgGLLoadProgram( _m_ogl_cg_shader->m_vs_program );
		cgGLLoadProgram( _m_ogl_cg_shader->m_ps_program );
	}
	m_is_commit = true;
}

void CShader::Enable()
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->Begin(NULL,NULL);
		_m_dx_hlsl_shader->BeginPass(NULL);
	}
	else
	{
		cgGLBindProgram( _m_ogl_cg_shader->m_vs_program );
		cgGLEnableProfile( _m_ogl_cg_shader->m_vs_profile );
	
		cgGLBindProgram( _m_ogl_cg_shader->m_ps_program );
		cgGLEnableProfile( _m_ogl_cg_shader->m_ps_profile );
	}
}

void CShader::Disable()
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->EndPass();
		_m_dx_hlsl_shader->End();
	}
	else
	{
		cgGLDisableProfile( _m_ogl_cg_shader->m_vs_profile );
		cgGLDisableProfile( _m_ogl_cg_shader->m_ps_profile );
	}
}


void CShader::SetMatrix(math::Matrix4x4 &_matrix, std::string _param, EShader _type)
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		D3DXMATRIX dx_matrix;
		memcpy(dx_matrix.m,_matrix.m,sizeof(float) * 16);
		_m_dx_hlsl_shader->SetMatrix(_param.c_str(), &dx_matrix);
	}
	else
	{
		switch(_type)
		{
		case VS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_vs_program, _param.c_str());
				cgGLSetMatrixParameterfc(param, _matrix.m);
			}
			break;
		case PS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_ps_program, _param.c_str());
				cgGLSetMatrixParameterfc(param, _matrix.m);
			}
			break;
		}
	}

}
void CShader::SetVector(math::Vector3d  &_vector, std::string _param, EShader _type)
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->SetFloatArray(_param.c_str(), _vector.v, 3);
	}
	else
	{
		switch(_type)
		{
		case VS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_vs_program, _param.c_str());
				cgGLSetParameter3fv( param, _vector.v );
			}
			break;
		case PS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_ps_program, _param.c_str());
				cgGLSetParameter3fv( param, _vector.v );
			}
			break;
		}
	}
}
void CShader::SetVector(math::Vector4d &_vector, std::string _param, EShader _type)
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->SetFloatArray(_param.c_str(), _vector.v, 4);
	}
	else
	{
		switch(_type)
		{
		case VS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_vs_program, _param.c_str());
				cgGLSetParameter4fv( param, _vector.v );
			}
			break;
		case PS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_ps_program, _param.c_str());
				cgGLSetParameter4fv( param, _vector.v );
			}
			break;
		}
	}
}
void CShader::SetFloat(float &_value, std::string _param, EShader _type)
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->SetFloat(_param.c_str(),_value);
	}
	else
	{
		switch(_type)
		{
		case VS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_vs_program, _param.c_str());
				cgGLSetParameter1fv( param, &_value );
			}
			break;
		case PS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_ps_program, _param.c_str());
				cgGLSetParameter1fv( param, &_value );
			}
			break;
		}
	}
}

void CShader::SetTexture(CTexture &_texture, std::string _param, EShader _type)
{
	if(!m_is_commit) return;
	if(core::Window::m_D3DRender)
	{
		_m_dx_hlsl_shader->SetTexture(_param.c_str(),_texture.m_dx_texture);
	}
	else
	{
		switch(_type)
		{
		case VS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_vs_program, _param.c_str());
				cgGLSetTextureParameter(param, _texture.m_ogl_texture);
				cgGLEnableTextureParameter(param);
			}
			break;
		case PS_SHADER :
			{
				CGparameter param = cgGetNamedParameter(_m_ogl_cg_shader->m_ps_program, _param.c_str());
				cgGLSetTextureParameter(param, _texture.m_ogl_texture);
				cgGLEnableTextureParameter(param);
			}
			break;
		}
	}
}
