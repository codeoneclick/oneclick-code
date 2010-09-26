#ifndef _DUMMY_H_
#define _DUMMY_H_

#include "StructExt.h"
#include "VBExtension.h"
#include "Matrix4x4.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Enviroment
{
class CDummy
{
	protected :
		Core::CShader *_shader;
		type::STexture *_textures[8];
		type::SMesh *_meshData;

		math::Matrix4x4 _mTranslation;
		math::Matrix4x4 _mRotationX;
		math::Matrix4x4 _mRotationY;
		math::Matrix4x4 _mRotationZ;
		math::Matrix4x4 _mRotation;
		math::Matrix4x4 _mScale;
		math::Matrix4x4 _mWorld;

		math::Matrix4x4 *_mView;
		math::Matrix4x4 *_mProjection;

		math::Matrix4x4 _mWorldViewProjection;

		math::Vector3d  *_vCameraPosition;
		math::Vector3d  *_vLightDirection;
		void _UpdateMatrix();
	public :
		CDummy();
		virtual void Load(std::string value) = NULL;
		virtual void Update() = NULL;
		virtual void Render() = NULL;

		math::Vector3d vPosition;
		math::Vector3d vRotation;
		math::Vector3d vScale;
	};
};

#endif