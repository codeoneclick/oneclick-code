#ifndef CDEVICED3D_H
#define CDEVICED3D_H

#include "IDevice.h"

#include "CTextureD3D.h"
#include "CShaderD3D.h"
#include "CVertexBufferD3D.h"
#include "CIndexBufferD3D.h"

namespace Core
{
	class CDeviceD3D : public IDevice 
	{
	private :
		LPDIRECT3D9 m_handle;
	public :
		CDeviceD3D();
		~CDeviceD3D();

		virtual ITexture* CreateTexture();
		virtual IShader* CreateShader();
		virtual IVertexBuffer* CreateVertexBuffer();
		virtual IIndexBuffer* CreateIndexBuffer();
	};
};

#endif