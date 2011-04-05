#include "CTextureCubeD3D.h"
#include "IDevice.h"

using namespace Core;

CTextureCubeD3D::CTextureCubeD3D()
{
	m_addr = NULL;
}

void CTextureCubeD3D::ReadFromFile(std::string _file_name)
{
	LPD3DXBUFFER error_buffer = NULL;
	HRESULT error_result = NULL;
	char* error_text = NULL;
	error_result = D3DXCreateCubeTextureFromFile(Core::IDevice::Ref(), _file_name.c_str(), &m_addr);
	if(FAILED( error_result ))
	{
		error_text = ( char* )error_buffer->GetBufferPointer();
		MessageBox(NULL, error_text ,"TextureController::TEXTURE", MB_OK | MB_ICONEXCLAMATION);
	}
	m_is_read_data = true;
}

void CTextureCubeD3D::CommitToVRAM()
{
	m_is_commit = true;
}
