#include "CTextureD3D.h"
#include "IDevice.h"

using namespace Core;

CTextureD3D::CTextureD3D()
{
	m_addr = NULL;
}

void CTextureD3D::ReadFromFile(std::string _file_name)
{
	LPD3DXBUFFER error_buffer = NULL;
	HRESULT error_result = NULL;
	char* error_text = NULL;
	error_result = D3DXCreateTextureFromFile(Core::IDevice::GetDeviceRef(), _file_name.c_str(), &m_addr);
	if(FAILED( error_result ))
	{
		error_text = ( char* )error_buffer->GetBufferPointer();
		MessageBox(NULL, error_text ,"TextureController::TEXTURE", MB_OK | MB_ICONEXCLAMATION);
	}
}

void CTextureD3D::CommitToVRAM()
{

}