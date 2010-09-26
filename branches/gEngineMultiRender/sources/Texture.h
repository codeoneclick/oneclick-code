#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3dx9.h>
#include <string>

namespace Core
{
	class CTexture
	{
	public :
		enum TEXTURE_EXTENSION { DDS_EXT = 0, PNG_EXT = 1 };
	private :
		void *_m_data;
	public :
		CTexture();
		~CTexture();

		void ReadData(std::string _value);
		void Commit(std::string _value);

		bool m_is_read_data;
		bool m_is_commit;

		TEXTURE_EXTENSION m_extension;

		IDirect3DTexture9* m_dx_texture;
		unsigned int m_ogl_texture;
	};
}

#endif
