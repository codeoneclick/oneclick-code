#ifndef IDEVICE_H
#define IDEVICE_H

#include <d3dx9.h>

#include "ITexture.h"
#include "IShader.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

namespace Core
{
	class IDevice  
	{
	protected :
		static LPDIRECT3DDEVICE9 m_device;
	public :
		IDevice();
		~IDevice();

		__forceinline static LPDIRECT3DDEVICE9 Ref() { return m_device; } 

		virtual ITexture* CreateTexture() = 0;
		virtual IShader* CreateShader() = 0;
		virtual IVertexBuffer* CreateVertexBuffer() = 0;
		virtual IIndexBuffer* CreateIndexBuffer() = 0;
	};
};

#endif