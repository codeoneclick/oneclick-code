#ifndef ITEXTURE_H
#define ITEXTURE_H

#include <string>

namespace Core
{
	class ITexture  
	{
	public :
		enum TEXTURE_EXTENSION { DDS_EXT = 0, PNG_EXT = 1 };
	public :
		ITexture()
		{
			m_is_file_read = false;
			m_is_commit = false;
		}
		~ITexture();

		virtual void ReadFromFile(std::string _file_name) { }
		virtual void CommitToVRAM() { }

		bool m_is_file_read;
		bool m_is_commit;
		TEXTURE_EXTENSION m_extension;
	};
};

#endif