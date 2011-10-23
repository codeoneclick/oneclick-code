#include "CShaderD3D.h"
#include "IDevice.h"
#include "CTextureD3D.h"

using namespace Core;

CShaderD3D::CShaderD3D()
{

}

CShaderD3D::~CShaderD3D()
{

}

void CShaderD3D::ReadData(std::string _file_name)
{
	LPD3DXBUFFER error_buffer = NULL;
	HRESULT error_result = NULL;
	char* error_text = NULL;
	_file_name += ".fx";
	error_result = D3DXCreateEffectFromFile(Core::IDevice::Ref(), _file_name.c_str(), NULL, NULL, 0, NULL, &m_addr, &error_buffer);
	if(FAILED( error_result ))
	{
		error_text = ( char* )error_buffer->GetBufferPointer();
		MessageBox(NULL, error_text ,"ShaderController::SHADER", MB_OK | MB_ICONEXCLAMATION);
	}
	m_is_read_data = true;
}

void CShaderD3D::Commit(std::string _name)
{
	m_is_commit = true;
}

void CShaderD3D::Enable()
{
	if(!m_is_commit) return;
	m_addr->Begin(NULL,NULL);
	m_addr->BeginPass(NULL);
}

void CShaderD3D::Disable()
{
	if(!m_is_commit) return;
	m_addr->EndPass();
	m_addr->End();
}

void CShaderD3D::SetFloat(float &_value, std::string _param, Core::IShader::EShader _type)
{
	if(!m_is_commit) return;
	m_addr->SetFloat(_param.c_str(),_value);
}

void CShaderD3D::SetVector(math::Vector3d &_vector, std::string _param, Core::IShader::EShader _type)
{
	if(!m_is_commit) return;
	m_addr->SetFloatArray(_param.c_str(), _vector.v, 3);
}

void CShaderD3D::SetVector(math::Vector4d &_vector, std::string _param, Core::IShader::EShader _type)
{
	if(!m_is_commit) return;
	m_addr->SetFloatArray(_param.c_str(), _vector.v, 4);
}

void CShaderD3D::SetMatrix(math::Matrix4x4 &_matrix, std::string _param, Core::IShader::EShader _type)
{
	if(!m_is_commit) return;
	D3DXMATRIX dx_matrix;
	memcpy(dx_matrix.m,_matrix.m,sizeof(float) * 16);
	m_addr->SetMatrix(_param.c_str(), &dx_matrix);
}

void CShaderD3D::SetTexture(Core::ITexture *_texture, std::string _param, Core::IShader::EShader _type)
{
	if(!m_is_commit) return;
	m_addr->SetTexture(_param.c_str(), ((CTextureD3D*)_texture)->m_addr );
}