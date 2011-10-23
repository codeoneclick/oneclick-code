#include "m3_Heightmap.h"

m3_Heightmap::m3_Heightmap()
{
	_width  = 256;
	_height = 256;
	_heightmap = NULL;

	_vertexBufferPtr = new m3_VertexBufferPtr();
	_vertexBufferId = new m3_VertexBufferID();

	glGenBuffersARB = NULL;
    glBindBufferARB = NULL;
    glBufferDataARB = NULL;
    glDeleteBuffersARB = NULL;
}

void m3_Heightmap::Load(std::string value)
{
	_heightmap = new float*[_width];
	for(unsigned int i = 0; i < _width; ++i)
	{
		_heightmap[i] = new float[_height];
		for(unsigned int j = 0; j < _height; ++j)
			_heightmap[i][j] = 0.0f;
	}

	unsigned char byteReadValue = 0;
	FILE * file;
	file = fopen( value.c_str(), "rb" );
	for(unsigned int i = 0; i < _width;++i)
        for(unsigned int j = 0; j < _height;++j)
		{
              fread(&byteReadValue,sizeof(unsigned char),1,file);
			  _heightmap[i][j] = (float)byteReadValue;
		}
	fclose( file );

	_vertexBufferPtr->nVerteces = _width*_height;

	_vertexBufferPtr->vertexDataPtr = new m3_VertexData[_width*_height];
	_vertexBufferPtr->normalDataPtr = new m3_NormalData[_width*_height];
	_vertexBufferPtr->textureCoordPtr = new m3_TextureCoordData[_width*_height];

	unsigned int _vertexBufferIndex = 0;
	for(unsigned int i = 0; i < _width;++i)
        for(unsigned int j = 0; j < _height;++j)
		{
			_vertexBufferPtr->vertexDataPtr[_vertexBufferIndex].x = i;
			_vertexBufferPtr->vertexDataPtr[_vertexBufferIndex].y = _heightmap[i][j]*0.1f - 32.0f;
			_vertexBufferPtr->vertexDataPtr[_vertexBufferIndex].z = j;

			_vertexBufferPtr->normalDataPtr[_vertexBufferIndex].x = 0.0f;
			_vertexBufferPtr->normalDataPtr[_vertexBufferIndex].y = 1.0f;
			_vertexBufferPtr->normalDataPtr[_vertexBufferIndex].z = 0.0f;

			_vertexBufferPtr->textureCoordPtr[_vertexBufferIndex].u = i/(float)_width;
			_vertexBufferPtr->textureCoordPtr[_vertexBufferIndex].v = j/(float)_height;

			++_vertexBufferIndex;
		}

	if(glGenBuffersARB == NULL)
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	if(glBindBufferARB == NULL)
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	if(glBufferDataARB == NULL)
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	if(glDeleteBuffersARB == NULL)
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

	glGenBuffersARB( 1, &_vertexBufferId->vertexId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*3*sizeof(float), _vertexBufferPtr->vertexDataPtr, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &_vertexBufferId->textureCoordId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*2*sizeof(float), _vertexBufferPtr->textureCoordPtr, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &_vertexBufferId->normalId );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*3*sizeof(float), _vertexBufferPtr->normalDataPtr, GL_STATIC_DRAW_ARB );


	_vertexBufferPtr->nIndeces = 255*255*6;
	_vertexBufferPtr->indecesPtr = new unsigned int[255*255*6];
	_vertexBufferIndex = 0;

	for(unsigned int i = 0; i < 255; ++i)
		for(unsigned int j = 0; j < 255; ++j)
		{
			this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + j * _width;
            _vertexBufferIndex++;
            this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + j * _width ;
            _vertexBufferIndex++;
            this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;

            this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + (j + 1) * _width;
            _vertexBufferIndex++;
            this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + j * _width;
            _vertexBufferIndex++;
            this->_vertexBufferPtr->indecesPtr[_vertexBufferIndex] = i + 1 + (j + 1) * _width;
            _vertexBufferIndex++;
		}
}

void m3_Heightmap::Update()
{
	m3_Core::GetCamera()->ApplyViewMatrix();
}

void m3_Heightmap::Render()
{
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId);
	glVertexPointer( 3, GL_FLOAT, 0,  NULL );		
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId );
	glTexCoordPointer( 2, GL_FLOAT, 0,NULL );	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId );
	glNormalPointer( GL_FLOAT, 0,NULL );

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, &_vertexBufferPtr->indecesPtr[0] );

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}