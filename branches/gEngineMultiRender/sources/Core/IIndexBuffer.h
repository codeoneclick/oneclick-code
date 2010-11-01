#ifndef IINDEXBUFFER_H
#define IINDEXBUFFER_H

namespace Core
{
	class IIndexBuffer 
	{
	protected :
		unsigned int m_index_count;
		unsigned int *m_data;
	public :
		IIndexBuffer()
		{
			m_index_count = 0;
			m_data = NULL;
		}
		~IIndexBuffer()
		{
			delete[] m_data;
		}

		__forceinline const unsigned int GetIndexCount() { return m_index_count; }
		__forceinline const unsigned int GetPrimitiveCount() { return m_index_count / 3; }

		virtual unsigned int*  Load(unsigned int _index_count) = 0;
		virtual void CommitToVRAM() = 0;
		virtual unsigned int* Lock() = 0;
		virtual void Unlock() = 0;
		virtual void Enable() = 0;
		virtual void Disable() = 0;
	};
};

#endif