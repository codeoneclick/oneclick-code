#ifndef _MESHCONTROLLER_H_
#define _MESHCONTROLLER_H_

#include "IResourceController.h"
#include "../Loader/3DS.h"


namespace Controller
{
	class CMeshController : public IResourceController
	{
	private :
		std::map<std::string,Core::CMesh*> m_ResourceContainer;
		std::map<std::string,void*> m_DataContainer;
		Core::IVertexBuffer *m_Default_vb;
		Core::IIndexBuffer *m_Default_ib;

		void ReadData(std::string _value);
		void LoadDefault();
	public :
		CMeshController();
		~CMeshController();
		Core::CMesh* Load(std::string _value, Core::CMesh::MESH_EXTENSION _extension);
		virtual void Update();
	};
};

#endif