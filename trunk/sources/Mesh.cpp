#include "Mesh.h"

Mesh::Mesh()
{
	_vertexBuffer = new VertexBuffer();;
	_indexBuffer  = new IndexBuffer();;
	_shaderStr = "basic";
}

void Mesh::Load(const char* fileName,const char* meshName)
{
	meshOriginalName = meshName;
	_meshFileName = fileName;
	std::string _textureFilePath   = "Content\\Textures\\";
	std::string _textureName = meshName;
	std::string extension = "";
	unsigned int extensionCutSize = 0;

	for( int i = (_meshFileName.length() - 1); i > -1; --i)
		if(_meshFileName[i] != '.')
			extension += _meshFileName[i];
		else
		{
			if(extension == "3m")
				extensionCutSize = 3;
			if(extension == "sd3")
				extensionCutSize = 4;
		}

	_textureName.erase(_textureName.length() - extensionCutSize,extensionCutSize);
	_textureFilePath.insert(_textureFilePath.length(),_textureName);
	_textureFilePath.insert(_textureFilePath.length(),"_diffuse.dds");
	_textureStr[0] = _textureFilePath;
}

void Mesh::Update()
{
	if(!_vertexBuffer->vertexBufferAddr)
	{
		if(Resource::MeshContainer()->GetMesh(_meshFileName))
			_vertexBuffer->vertexBufferAddr = Resource::MeshContainer()->GetMesh(_meshFileName)->vertexBufferId;
		if(_vertexBuffer->vertexBufferAddr)
		{
			_chunkBuffer = Resource::MeshContainer()->GetMesh(_meshFileName)->chunkBuffer;
			_vertexBuffer->nVerteces      = Resource::MeshContainer()->GetMesh(_meshFileName)->nVerteces;
			_indexBuffer->indexBufferAddr = Resource::MeshContainer()->GetMesh(_meshFileName)->indexBufferId;
			_indexBuffer->nIndeces        = Resource::MeshContainer()->GetMesh(_meshFileName)->nIndeces;
			_vertexDeclaration.bPosition = true;
			_vertexDeclaration.bTexCoord = true;
		}
	}	

	_UpdateWorldMatrix();
}

void Mesh::RenderChunk(std::string value)
{
	if(!_vertexBuffer->vertexBufferAddr) return;

	std::map<std::string,ChunkData*>::iterator chunkIterator = _chunkBuffer->chunkData.find(value);
	if(chunkIterator == _chunkBuffer->chunkData.end())
		return;

	EnableShader("basic","basic");
	_UpdateShaderParams();
	EnableVB();
	EnableIB();
	glCullFace(GL_BACK);
	
	glDrawElements( GL_TRIANGLES, chunkIterator->second->nIndeces, GL_UNSIGNED_INT, &chunkIterator->second->indexBufferAddr[0]);

	DisableShader();
}

void Mesh::Render()
{
	if(!_vertexBuffer->vertexBufferAddr) return;

	EnableShader("basic","basic");
	_UpdateShaderParams();
	EnableVB();
	EnableIB();
	glCullFace(GL_BACK);
	
	glDrawElements( GL_TRIANGLES, _indexBuffer->nIndeces, GL_UNSIGNED_INT, NULL);

	DisableShader();
}