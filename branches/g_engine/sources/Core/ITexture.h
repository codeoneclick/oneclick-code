#ifndef ITEXTURE_H
#define ITEXTURE_H

#include <string>

namespace Core
{
	class ITexture  
	{
	public :
		enum TEXTURE_EXTENSION { DDS_EXT = 0, PNG_EXT };
		enum TEXTURE_BPP { BPP_16 = 0, BPP_32 };
	public :
		ITexture()
		{
			m_is_read_data = false;
			m_is_commit = false;
		}
		~ITexture()
		{

		}

		virtual void ReadFromFile(std::string _file_name) = 0;
		virtual void CommitToVRAM() = 0;
		virtual void SetAsRenderTarget(unsigned int _Width, unsigned int _Height) = 0;
		virtual void* Lock() = 0;
		virtual void Unlock() = 0;

		unsigned int m_Width;
		unsigned int m_Height;

		bool m_is_read_data;
		bool m_is_commit;
		TEXTURE_EXTENSION m_extension;
	};
};

#endif