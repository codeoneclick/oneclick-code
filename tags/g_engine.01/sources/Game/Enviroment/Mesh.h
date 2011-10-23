#ifndef _MESH_H_
#define _MESH_H_

#include "../../Core/IVertexBuffer.h"
#include "../../Core/IIndexBuffer.h"
#include "../../Core/ITexture.h"
#include "../../Core/IShader.h"
#include "../../Core/CGlobal.h"

namespace Core
{
	class CMesh
	{
	public :
		enum MESH_EXTENSION { EXT_3DS = 0, EXT_MD2 };
		MESH_EXTENSION m_Extension;
		
		IVertexBuffer *m_VertexBuffer;
		IIndexBuffer  *m_IndexBuffer;
		IShader  *m_Shader;
		ITexture *m_TextureArray[8];

		CMesh();
		~CMesh();

		void Draw();
		
	};
};

#endif
