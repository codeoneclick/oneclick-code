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

		__forceinline static LPDIRECT3DDEVICE9 GetDeviceRef() { return m_device; } 

		virtual ITexture* CreateTexture() { return NULL; }
		virtual IShader* CreateShader() { return NULL; }
		virtual IVertexBuffer* CreateVertexBuffer() { return NULL; }
		virtual IIndexBuffer* CreateIndexBuffer() { return NULL; }
	};
};

#endif