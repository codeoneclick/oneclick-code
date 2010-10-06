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
		Core::CShader  *m_Shader;
		Core::CTexture *m_TextureArray[8];
		type::SMesh *m_MeshData;

		math::Matrix4x4 m_mTranslation;
		math::Matrix4x4 m_mRotationX;
		math::Matrix4x4 m_mRotationY;
		math::Matrix4x4 m_mRotationZ;
		math::Matrix4x4 m_mRotation;
		math::Matrix4x4 m_mScale;

		math::Matrix4x4 m_mWorld;
		math::Matrix4x4 *m_mView;
		math::Matrix4x4 *m_mProjection;

		math::Matrix4x4 m_mWorldViewProjection;

		math::Vector3d  *m_vCameraPosition;
		math::Vector3d  *m_vLightDirection;
		void RefreshMatrix();
	public :
		CDummy();
		virtual void Load(std::string _fileName) = NULL;
		virtual void Update() = NULL;
		virtual void Render() = NULL;

		math::Vector3d m_vPosition;
		math::Vector3d m_vRotation;
		math::Vector3d m_vScale;
	};
};

#endif