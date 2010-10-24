#ifndef CDEVICED3D_H
#define CDEVICED3D_H

#include "IDevice.h"

namespace Core
{
	class CDeviceD3D : public IDevice 
	{
	private :
		LPDIRECT3D9 m_handle;
	public :
		CDeviceD3D();
		~CDeviceD3D();

		virtual void CreateTexture( ITexture *_out_value);
		virtual void CreateShader( IShader *_out_value);
		virtual void CreateVertexBuffer( IVertexBuffer *_out_value);
		virtual void CreateIndexBuffer( IIndexBuffer *_out_value);
	};
};

#endif