#ifndef _MESH_H_
#define _MESH_H_

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"

namespace Core
{
	class CMesh
	{
	public :
		enum MESH_EXTENSION { EXT_3DS = 0 };
		MESH_EXTENSION m_Extension;
		
		CVertexBuffer *m_VertexBuffer;
		CIndexBuffer  *m_IndexBuffer;
		CShader  *m_Shader;
		CTexture *m_TextureArray[8];

		CMesh();
		~CMesh();

		void Draw();
		
	};
};

#endif
