#ifndef CSHADERD3D_H
#define CSHADERD3D_H

#include <d3dx9.h>

#include "IShader.h"

namespace Core
{
	class CShaderD3D : public IShader 
	{
	private :
		ID3DXEffect* m_addr;
	public :
		CShaderD3D();
		~CShaderD3D();

		virtual void ReadData(std::string _file_name);
		virtual void Commit(std::string _name);

		virtual void Enable();
		virtual void Disable();

		virtual void SetMatrix(math::Matrix4x4 &_matrix, std::string _param, EShader _type);
		virtual void SetVector(math::Vector3d  &_vector, std::string _param, EShader _type);
		virtual void SetVector(math::Vector4d  &_vector, std::string _param, EShader _type);
		virtual void SetFloat(float  &_value, std::string _param, EShader _type);
		virtual void SetTexture(ITexture *_texture, std::string _param, EShader _type);
		virtual void SetD3DTexture(LPDIRECT3DTEXTURE9 _texture, std::string _param, EShader _type);
	};
};

#endif