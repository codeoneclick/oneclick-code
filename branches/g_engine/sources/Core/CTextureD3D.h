#ifndef CTEXTURED3D_H
#define CTEXTURED3D_H

#include <d3dx9.h>
#include "ITexture.h"

namespace Core
{
	class CTextureD3D : public ITexture 
	{
	public :
		CTextureD3D();
		~CTextureD3D();

		IDirect3DTexture9 *m_addr;
		LPDIRECT3DSURFACE9 m_addr_surf;

		virtual void ReadFromFile(std::string _file_name);
		virtual void CommitToVRAM();
		virtual void SetAsRenderTarget(unsigned int _Width, unsigned int _Height);
	};
};

#endif