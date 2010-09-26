#ifndef _SHADER_H_
#define _SHADER_H_

#include <Cg/Cg.h>
#include <Cg/cgGL.h>

#include <d3dx9.h>

#include "Matrix4x4.h"
#include "Vector3d.h"
#include "Texture.h"
#include <string>

namespace Core
{
	class CShader
	{
	public:
		enum EShader { VS_SHADER = 0, PS_SHADER };
	private :
		class SCGShader
		{
		public :
				CGcontext   m_context;
				CGprofile   m_vs_profile;
				CGprofile   m_ps_profile;
				CGprogram   m_vs_program;
				CGprogram   m_ps_program;
		};

		ID3DXEffect* _m_dx_hlsl_shader;
		SCGShader*   _m_ogl_cg_shader;
	public :
		CShader();
		~CShader();

		void ReadData(std::string _value);
		void Commit(std::string _value);

		void Enable();
		void Disable();

		void SetMatrix(math::Matrix4x4 &_matrix, std::string _param, EShader _type);
		void SetVector(math::Vector3d  &_vector, std::string _param, EShader _type);
		void SetVector(math::Vector4d  &_vector, std::string _param, EShader _type);
		void SetFloat(float  &_value, std::string _param, EShader _type);	
		void SetTexture(CTexture &_texture, std::string _param, EShader _type);

		bool m_is_read_data;
		bool m_is_commit;
	};
}

#endif
