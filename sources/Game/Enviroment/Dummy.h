#ifndef _DUMMY_H_
#define _DUMMY_H_

#include <string>
#include <vector>
#include <map>

#include "../../Math/Matrix4x4.h"
#include "Mesh.h"
#include "../../Math/Util.h"
#include "../Controller/CIntersectController.h"

#define K_MAX_TEXTURES_PER_MESH 8

namespace Enviroment
{

	struct SResource
	{
		Core::CMesh::MESH_EXTENSION m_Extension;
		std::string m_ResouceFile;
		std::string m_ShaderFile;
		std::string m_TextureFileList[K_MAX_TEXTURES_PER_MESH];
	};

	class CDummy
	{
		protected :
			std::map<std::string,Core::CMesh*> m_MeshList;
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
			std::string m_Name;

			Enviroment::CIntersectController::SIntersectBlock* m_intersectBlock;

			void Matrix();
		public :
			CDummy();
			virtual void Load(std::vector<SResource> _resource) = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;

			math::Vector3d m_vPosition;
			math::Vector3d m_vRotation;
			math::Vector3d m_vScale;
	};
};

#endif