#ifndef CDEVICED3D_H
#define CDEVICED3D_H

#include "IDevice.h"

#include "CTextureD3D.h"
#include "CTextureCubeD3D.h"
#include "CShaderD3D.h"
#include "CVertexBufferD3D.h"
#include "CIndexBufferD3D.h"

namespace Core
{
	class CDeviceD3D : public IDevice 
	{
	private :
		LPDIRECT3D9 m_handle;

		LPDIRECT3DSURFACE9 m_OldRenderSurface;
		LPDIRECT3DSURFACE9 m_OldStencilSurface;
		LPDIRECT3DSURFACE9 m_CurrentStencilSurface;
		D3DVIEWPORT9 m_OldViewport;

	public :
		CDeviceD3D();
		~CDeviceD3D();

		virtual ITexture* CreateTexture();
		virtual ITexture* CreateTextureCube();
		virtual IShader* CreateShader();
		virtual IVertexBuffer* CreateVertexBuffer();
		virtual IIndexBuffer* CreateIndexBuffer();

		virtual void BeginRender();
		virtual void EndRender();
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count);
		virtual void BeginRenderTarget(ITexture *_texture);
		virtual void EndRenderTarget();
		virtual void EnableClipPlane(unsigned int _index, math::Vector3d _point_01, math::Vector3d _point_02, math::Vector3d _point_03);
		virtual void DisableClipPlane(unsigned int _index);
		virtual void SetCullFace(ECULLFACE _value);

		virtual void AlphaBlendEnable();
		virtual void AlphaBlendDisable();
		virtual void AlphaTestEnable();
		virtual void AlphaTestDisable();
	};
};

#endif