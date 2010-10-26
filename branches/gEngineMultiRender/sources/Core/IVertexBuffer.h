#ifndef IVERTEXBUFFER_H
#define IVERTEXBUFFER_H

#include <windows.h>

namespace Core
{
	class IVertexBuffer 
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

	protected :
		unsigned int m_element_size;
		unsigned int m_vertex_count;
		char *m_data;
		SVertexDeclaration m_declaration;
		
	public :
		IVertexBuffer()
		{
			m_element_size = 0;
			m_vertex_count = 0;
		}
		~IVertexBuffer()
		{
			delete[] m_data;
		}

		__forceinline unsigned int GetVertexCount() { return  m_vertex_count; }
		
		virtual void* Load(unsigned int _vertex_count, unsigned int _element_size) { return NULL; }
		virtual void CommitToVRAM() { }
		virtual void SetDeclaration(SVertexDeclaration &_declaration) { }
		virtual void* Lock() { return NULL; }
		virtual void Unlock() { }
		virtual void Enable() { }
		virtual void Disable() { }
	};
};

#endif