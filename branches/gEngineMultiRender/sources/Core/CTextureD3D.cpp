#include "CTextureD3D.h"
#include "IDevice.h"

using namespace Core;

CTextureD3D::CTextureD3D()
{
	m_addr = NULL;
	m_addr_surf = NULL;
	m_Width = 0;
	m_Height = 0;
}

void CTextureD3D::ReadFromFile(std::string _file_name)
{
	LPD3DXBUFFER error_buffer = NULL;
	HRESULT error_result = NULL;
	char* error_text = NULL;
	error_result = D3DXCreateTextureFromFile(Core::IDevice::Ref(), _file_name.c_str(), &m_addr);
	if(FAILED( error_result ))
	{
		error_text = ( char* )error_buffer->GetBufferPointer();
		MessageBox(NULL, error_text ,"TextureController::TEXTURE", MB_OK | MB_ICONEXCLAMATION);
	}
	m_is_read_data = true;
}

void CTextureD3D::CommitToVRAM()
{
	m_is_commit = true;
}

void CTextureD3D::SetAsRenderTarget(unsigned int _Width, unsigned int _Height)
{
	Core::IDevice::Ref()->CreateTexture(_Width, _Height, 1, D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_addr, NULL );
	Core::IDevice::Ref()->CreateDepthStencilSurface(_Width,_Height,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&m_addr_surf,NULL);
	m_Width = _Width;
	m_Height = _Height;
	m_is_commit = true;
	m_is_read_data = true;
}