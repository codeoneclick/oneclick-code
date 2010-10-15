#include "Texture.h"
#include "Resource.h"
#include "Device.h"
#include "Window.h"

using namespace Core;

CTexture::CTexture()
{
	m_is_read_data = false;
	m_is_commit = false;
}

CTexture::~CTexture()
{

}

void CTexture::ReadData(std::string _value)
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{
		LPD3DXBUFFER error_buffer = NULL;
		HRESULT error_result = NULL;
		char* error_text = NULL;
		
		error_result = D3DXCreateTextureFromFile(Core::CDevice::GetD3DDevice(), _value.c_str(), &m_dx_texture);
	
		if(FAILED( error_result ))
		{
			error_text = ( char* )error_buffer->GetBufferPointer();
			MessageBox(NULL, error_text ,"TextureController::TEXTURE", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else
	{
		switch(m_extension)
		{
		case DDS_EXT :
			{
				 _m_data = Loader::CDDS::ReadData(_value);		
			}
			break;
		case PNG_EXT :
			{

			}
			break;
		}
	}
	m_is_read_data = true;
}

void CTexture::Commit(std::string _value)
{
	if(Core::CDevice::GetDeviceType() == Core::CDevice::D3D)
	{

	}
	else
	{
		m_ogl_texture = Loader::CDDS::Commit((Loader::CDDS::SDDSFile*)_m_data);
	}
	m_is_commit = true;
}