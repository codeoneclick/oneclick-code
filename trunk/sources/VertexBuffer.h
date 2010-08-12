#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "VBExtension.h"
#include "Vector3d.h"

class CVertexBuffer
{
	public :
	struct SVertexVT
	{
		math::vector::Vector3d vPosition;
		math::vector::Vector2d vTexCoord;
	};
	struct SVertexVTTBN
	{
		math::vector::Vector3d vPosition;
		math::vector::Vector2d vTexCoord;
		math::vector::Vector3d vNormal;
		math::vector::Vector3d vTangent;
		math::vector::Vector3d vBinormal;
	};
	struct SVertexVTTBNW
	{
		math::vector::Vector3d vPosition;
		math::vector::Vector2d vTexCoord;
		math::vector::Vector3d vNormal;
		math::vector::Vector3d vTangent;
		math::vector::Vector3d vBinormal;
		math::vector::Vector4d vWeight;
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
