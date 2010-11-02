#ifndef _DUMMY_H_
#define _DUMMY_H_

#include <string>
#include <map>

#include "Matrix4x4.h"
#include "Mesh.h"
#include "Math/Util.h"

namespace Enviroment
{
	class CDummy
	{
	protected :
		std::map<std::string,Core::CMesh*> m_MeshArray;
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
		void Matrix();
	public :
		CDummy();
		virtual void Load(std::string _fileName) { }
		virtual void Update() { }
		virtual void Render() { }

		math::Vector3d m_vPosition;
		math::Vector3d m_vRotation;
		math::Vector3d m_vScale;
	};
};

#endif