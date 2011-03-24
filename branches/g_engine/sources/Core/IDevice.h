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
	public :
		enum ECULLFACE { CULL_NONE = 0, CULL_CW, CULL_CCW };

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

		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count) = 0;
		virtual void BeginRenderTarget(ITexture *_texture) = 0;
		virtual void EndRenderTarget() = 0;
		virtual void EnableClipPlane(unsigned int _index, math::Vector3d _point_01, math::Vector3d _point_02, math::Vector3d _point_03) = 0;
		virtual void DisableClipPlane(unsigned int _index) = 0;
		virtual void SetCullFace(ECULLFACE _value) = 0;
		virtual void AlphaBlendEnable() = 0;
		virtual void AlphaBlendDisable() = 0;
		virtual void AlphaTestEnable() = 0;
		virtual void AlphaTestDisable() = 0;
	};
};

#endif