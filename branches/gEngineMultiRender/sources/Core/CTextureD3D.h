#ifndef CTEXTURED3D_H
#define CTEXTURED3D_H

#include <d3dx9.h>
#include "ITexture.h"

namespace Core
{
	class CTextureD3D : public ITexture 
	{
	private :
		IDirect3DTexture9* m_addr;
	public :
		CTextureD3D();
		~CTextureD3D();

		virtual void ReadFromFile(std::string _file_name);
		virtual void CommitToVRAM();
	};
};

#endif