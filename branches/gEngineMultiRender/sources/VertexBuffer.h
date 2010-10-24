#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <d3dx9.h>
#include "VBExtension.h"
#include "Vector3d.h"

class CVertexBuffer
{
	public :

	enum DECLARATION_ELEMENT_SIZE { ELEMENT_FLOAT = 1, ELEMENT_FLOAT2 = 2, ELEMENT_FLOAT3 = 3, ELEMENT_FLOAT4 = 4 };
	enum DECLARATION_ELEMENT_TYPE { ELEMENT_POSITION = 0, ELEMENT_NORMAL = 3, ELEMENT_TEXCOORD = 5, ELEMENT_TANGENT = 6, ELEMENT_BINORMAL = 7};

	struct SElementDeclaration
	{
		unsigned int m_Offset;
		DECLARATION_ELEMENT_SIZE m_Size;
		DECLARATION_ELEMENT_TYPE m_Type;
		unsigned int m_Index;
	};

	struct SVertexDeclaration
	{
		SElementDeclaration *m_Elements;
		unsigned int m_ElementCount;	
	};

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
		unsigned int _m_ogl_addr;
		IDirect3DVertexBuffer9* _m_dx_addr;

		unsigned int _m_element_size;
		unsigned int _m_vertex_count;

		char *_m_vb_data;

		SVertexDeclaration _m_declaration;
		LPDIRECT3DVERTEXDECLARATION9 _prt_vertex_declaration;
	public :
		CVertexBuffer();
		~CVertexBuffer();
		void* Load(unsigned int vertex_count, unsigned int element_size);
		void CommitVRAM();
		void SetDeclaration(SVertexDeclaration &_declaration);
		__forceinline unsigned int GetVertexCount() { return  _m_vertex_count; }
		void* Lock();
		void Unlock();
		void Enable();
		void Disable();
};

#endif
