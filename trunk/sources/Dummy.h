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
		CShader *_shader;
		type::STexture *_textures[8];
		type::SMesh *_meshData;

		math::matrix::Matrix4x4 _mTranslation;
		math::matrix::Matrix4x4 _mRotationX;
		math::matrix::Matrix4x4 _mRotationY;
		math::matrix::Matrix4x4 _mRotationZ;
		math::matrix::Matrix4x4 _mRotation;
		math::matrix::Matrix4x4 _mScale;
		math::matrix::Matrix4x4 _mWorld;

		math::matrix::Matrix4x4 *_mView;
		math::matrix::Matrix4x4 *_mProjection;

		math::matrix::Matrix4x4 _mWorldViewProjection;

		math::vector::Vector3d  *_vCameraPosition;
		math::vector::Vector3d  *_vLightDirection;
		void _UpdateMatrix();
	public :
		CDummy();
		virtual void Load(std::string value) = NULL;
		virtual void Update() = NULL;
		virtual void Render() = NULL;

		math::vector::Vector3d vPosition;
		math::vector::Vector3d vRotation;
		math::vector::Vector3d vScale;
	};
};

#endif