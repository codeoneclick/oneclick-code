#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "VBExtension.h"
#include "Vector3d.h"

class CVertexBuffer
{
	public :
	struct SVertexVT
	{
		math::Vector3d vPosition;
		math::Vector2d vTexCoord;
	};
	struct SVertexVTTBN
	{
		math::Vector3d vPosition;
		math::Vector2d vTexCoord;
		math::Vector3d vNormal;
		math::Vector3d vTangent;
		math::Vector3d vBinormal;
	};
	struct SVertexVTTBNW
	{
		math::Vector3d vPosition;
		math::Vector2d vTexCoord;
		math::Vector3d vNormal;
		math::Vector3d vTangent;
		math::Vector3d vBinormal;
		math::Vector4d vWeight;
	};
	protected :
		unsigned int _addr_ptr;
		unsigned int _vertexSize;
		unsigned int _nVerteces;
		char *_vb_data;
	public :
		CVertexBuffer();
		~CVertexBuffer();
		void *Create(unsigned int nVerteces, unsigned int vertexSize);
		void  Commit();
		void* Lock();
		void  Unlock();
		void  Enable();
		void  Disable();
};

#endif
