#ifndef IVERTEXBUFFER_H
#define IVERTEXBUFFER_H

#include <windows.h>

namespace Core
{
#define k_MAX_STREAM_COUNT  8
	class IVertexBuffer 
	{
	public :
		enum DECLARATION_ELEMENT_SIZE { ELEMENT_FLOAT = 0, ELEMENT_FLOAT2 = 1, ELEMENT_FLOAT3 = 2, ELEMENT_FLOAT4 = 3, ELEMENT_BYTE4 = 4, ELEMENT_SHORT2 = 6 };
		enum DECLARATION_ELEMENT_TYPE { ELEMENT_POSITION = 0, ELEMENT_NORMAL = 3, ELEMENT_TEXCOORD = 5, ELEMENT_TANGENT = 6, ELEMENT_BINORMAL = 7, ELEMENT_COLOR = 10};
		
		struct SElementDeclaration
		{
			unsigned int m_stream;
			unsigned int m_offset;
			unsigned int m_index;
			DECLARATION_ELEMENT_SIZE m_size;
			DECLARATION_ELEMENT_TYPE m_type;
			
			SElementDeclaration()
			{
				m_stream = 0;
				m_offset = 0;
				m_index = 0;
			}
		};

		struct SVertexDeclaration
		{
			SElementDeclaration *m_Elements;
			unsigned int m_ElementCount;	
		};

	protected :
		unsigned int m_elementSize[k_MAX_STREAM_COUNT];
		unsigned int m_vertexCount;
		char *m_data;
		SVertexDeclaration m_declaration;
		
	public :
		IVertexBuffer()
		{
			for(int i = 0; i < k_MAX_STREAM_COUNT; ++i)
				m_elementSize[i] = 0;
			m_vertexCount = 0;
		}
		~IVertexBuffer()
		{
			delete[] m_data;
		}

		__forceinline unsigned int GetVertexCount() { return  m_vertexCount; }
		
		virtual void* Load(unsigned int _vertexCount, unsigned int _elementSize, unsigned int _streamId) = 0;
		virtual void CommitToVRAM(unsigned int _streamId) = 0;
		virtual void SetDeclaration(SVertexDeclaration &_declaration) = 0;
		virtual void* Lock(unsigned int _streamId) = 0;
		virtual void Unlock(unsigned int _streamId) = 0;
		virtual void Enable() = 0;
		virtual void Disable() = 0;
		virtual void EnableDeclaration() = 0;
		virtual void CopyVertexBufferRef(IVertexBuffer *_value, unsigned int _srcStreamId, unsigned int _dstStreamId) = 0;
	};
};

#endif