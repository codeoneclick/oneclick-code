#ifndef ITEXTURECUBE_H
#define ITEXTURECUBE_H

#include <string>

namespace Core
{
	class ITextureCube  
	{
	public :
		enum TEXTURE_EXTENSION { DDS_EXT = 0 };
	public :
		ITextureCube()
		{
			m_is_read_data = false;
			m_is_commit = false;
		}
		~ITextureCube();

		virtual void ReadFromFile(std::string _file_name) = 0;
		virtual void CommitToVRAM() = 0;

		bool m_is_read_data;
		bool m_is_commit;
		TEXTURE_EXTENSION m_extension;
	};
};

#endif