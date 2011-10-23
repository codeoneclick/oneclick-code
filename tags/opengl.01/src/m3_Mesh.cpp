#include "m3_Mesh.h"

m3_Mesh::m3_Mesh()
{
	_complexMeshData = NULL;
	_shaderStr = "basic";
}

void m3_Mesh::Load(const char* fileName,const char* meshName)
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

void m3_Mesh::Update()
{
	if(!_complexMeshData)
	{
		_complexMeshData = m3_Resource::MeshContainer()->GetMesh(_meshFileName);
		if(_complexMeshData)
		{
			_vertexBufferId = _complexMeshData->vertexDataId;
			_vertexBufferPtr = _complexMeshData->vertexDataPtr;
		}
	}
	_UpdateWorldMatrix();
}

void m3_Mesh::RenderNormals()
{
	if(!_complexMeshData || !_cgShader) return;
	
	glDisable(GL_TEXTURE_2D);
	
	int normalLengthDiv = 4.0f;
	glBegin(GL_LINES);
	for(unsigned int i = 0; i < _complexMeshData->vertexDataPtr->nVerteces; ++i)
	{
		glColor4f(1.0f,1.0f,1.0f,0.7f);			
		glVertex3f(_complexMeshData->vertexDataPtr->vertexDataPtr[i].x, _complexMeshData->vertexDataPtr->vertexDataPtr[i].y, _complexMeshData->vertexDataPtr->vertexDataPtr[i].z);	
		glColor4f(0.0f,0.0f,1.0f,0.1f);			
		glVertex3f(_complexMeshData->vertexDataPtr->vertexDataPtr[i].x +_complexMeshData->vertexDataPtr->normalDataPtr[i].x/normalLengthDiv, _complexMeshData->vertexDataPtr->vertexDataPtr[i].y  + _complexMeshData->vertexDataPtr->normalDataPtr[i].y/normalLengthDiv, _complexMeshData->vertexDataPtr->vertexDataPtr[i].z + _complexMeshData->vertexDataPtr->normalDataPtr[i].z/normalLengthDiv);	
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f,1.0f,1.0f,1.0f);		
}

void m3_Mesh::RenderChunk(std::string value)
{
	if(!_complexMeshData) return;

	std::map<std::string,m3_ChunkData*>::iterator chunkIterator = _complexMeshData->vertexDataPtr->chunkIndecesPtr.find(value);
	if(chunkIterator == _complexMeshData->vertexDataPtr->chunkIndecesPtr.end())
		return;

	_EnableShader();
	_UpdateShaderParams();

	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId);
	glVertexPointer( 3, GL_FLOAT, 0,  NULL );	
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId );
	glTexCoordPointer( 2, GL_FLOAT, 0,NULL );	
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId );
	glNormalPointer( GL_FLOAT, 0,NULL );

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawElements( GL_TRIANGLES, chunkIterator->second->nIndeces, GL_UNSIGNED_INT, &chunkIterator->second->indecesPtr[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	_DisableShader();
}

void m3_Mesh::Render()
{
	if(!_complexMeshData) return;
	_EnableShader();
	_UpdateShaderParams();

	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId);
	glVertexPointer( 3, GL_FLOAT, 0,  NULL );	
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId );
	glTexCoordPointer( 2, GL_FLOAT, 0,NULL );	
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId );
	glNormalPointer( GL_FLOAT, 0,NULL );

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, &_vertexBufferPtr->indecesPtr[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	_DisableShader();
}