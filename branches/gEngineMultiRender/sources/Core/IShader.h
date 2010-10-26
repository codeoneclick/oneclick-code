#ifndef ISHADER_H
#define ISHADER_H

#include "../Matrix4x4.h"
#include "../Vector3d.h"
#include "ITexture.h"
#include <string>

namespace Core
{
	class IShader 
	{
	public : 
		enum EShader { VS_SHADER = 0, PS_SHADER };
	public :
		IShader()
		{

		}
		~IShader()
		{

		}

		bool m_is_read_data;
		bool m_is_commit;
		
		virtual void ReadData(std::string _file_name) { }
		virtual void Commit(std::string _name) { }

		virtual void Enable() { }
		virtual void Disable() { }

		virtual void SetMatrix(math::Matrix4x4 &_matrix, std::string _param, EShader _type) { }
		virtual void SetVector(math::Vector3d  &_vector, std::string _param, EShader _type) { }
		virtual void SetVector(math::Vector4d  &_vector, std::string _param, EShader _type) { }
		virtual void SetFloat(float  &_value, std::string _param, EShader _type) { } 
		virtual void SetTexture(ITexture *_texture, std::string _param, EShader _type) { }
	};
};

#endif