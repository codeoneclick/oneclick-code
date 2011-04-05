#ifndef CTEXTURECUBED3D_H
#define CTEXTURECUBED3D_H

#include <d3dx9.h>
#include "ITexture.h"

namespace Core
{
	class CTextureCubeD3D : public ITexture
	{
	public :
		CTextureCubeD3D();
		~CTextureCubeD3D();

		IDirect3DCubeTexture9 *m_addr;

		virtual void ReadFromFile(std::string _file_name);
		virtual void CommitToVRAM();
		virtual void SetAsRenderTarget(unsigned int _Width, unsigned int _Height) { };
	};
};

#endif