#include "Mesh.h"

Mesh::Mesh()
{
	_vertexBufferPtr = NULL;
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
	if(!_vertexBufferPtr)
	{
		_vertexBufferPtr = Resource::MeshContainer()->GetMesh(_meshFileName);
		if(_vertexBufferPtr)
		{
			_vertexBufferPtr->bPosition = true;
			_vertexBufferPtr->bTexCoord = true;
		}
	}	

	_UpdateWorldMatrix();
}

void Mesh::RenderChunk(std::string value)
{
	if(!_vertexBufferPtr) return;

	std::map<std::string,MeshChunkBlock*>::iterator chunkIterator = _vertexBufferPtr->chunkIndecesPtr.find(value);
	if(chunkIterator == _vertexBufferPtr->chunkIndecesPtr.end())
		return;

	EnableShader("basic","basic");
	_UpdateShaderParams();
	EnableVB();
	EnableIB();
	glCullFace(GL_BACK);
	
	glDrawElements( GL_TRIANGLES, chunkIterator->second->nIndeces, GL_UNSIGNED_INT, &chunkIterator->second->indecesPtr[0]);

	VB::glBindVB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
	VB::glBindVB(GL_ARRAY_BUFFER_ARB, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	VB::glBindDataVB(GL_TEXTURE0);

	DisableShader();
}

void Mesh::Render()
{
	/*if(!_vertexBufferPtr) return;
	_EnableShader();
	_UpdateShaderParams();
	_UpdateVB();

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, &_vertexBufferPtr->indecesPtr[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	VB::glBindDataVB(GL_TEXTURE0);
	_DisableShader();*/
}