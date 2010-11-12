#ifndef IRENDER_H
#define IRENDER_H

#include "ITexture.h"
#include "../Vector3d.h"

namespace Core
{
	class IRender
	{
	public :
		enum ECULLFACE { CULL_NONE = 0, CULL_CW, CULL_CCW };
	public :
		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
		virtual void Draw(unsigned int _vertex_count, unsigned int _index_count, unsigned int _primitive_count) = 0;
		virtual void BeginRenderTarget(ITexture *_texture) = 0;
		virtual void EndRenderTarget() = 0;
		virtual void EnableClipPlane(unsigned int _index, math::Vector3d _point_01, math::Vector3d _point_02, math::Vector3d _point_03) = 0;
		virtual void DisableClipPlane(unsigned int _index) = 0;
		virtual void SetCullFace(ECULLFACE _value) = 0;
	};
};

#endif
