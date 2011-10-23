#include "m3_Heightmap.h"

m3_Heightmap::m3_Heightmap()
{
	_width  = 256;
	_height = 256;
	_heightmap = NULL;
	_shaderStr = "multitex";
	_textureStr[1] = "Content\\textures\\grass.dds";
	_textureStr[0] = "Content\\textures\\rock.dds";
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
	_vertexBufferPtr->multitextureDataPtr = new m3_MultiTextureData[_width*_height];


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

			_vertexBufferPtr->multitextureDataPtr[_vertexBufferIndex].value[0] = _heightmap[i][j]/127.0f;
			_vertexBufferPtr->multitextureDataPtr[_vertexBufferIndex].value[1] = _heightmap[i][j]/255.0f;
			_vertexBufferPtr->multitextureDataPtr[_vertexBufferIndex].value[2] = 0.5f;
			_vertexBufferPtr->multitextureDataPtr[_vertexBufferIndex].value[3] = 0.5f;

			++_vertexBufferIndex;
		}
		
	m3_VBO::glGenBufferVBO()( 1, &_vertexBufferId->vertexId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*3*sizeof(float), _vertexBufferPtr->vertexDataPtr, GL_STATIC_DRAW_ARB );

	m3_VBO::glGenBufferVBO()( 1, &_vertexBufferId->textureCoordId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*2*sizeof(float), _vertexBufferPtr->textureCoordPtr, GL_STATIC_DRAW_ARB );

	m3_VBO::glGenBufferVBO()( 1, &_vertexBufferId->multitexId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->multitexId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*4*sizeof(float), _vertexBufferPtr->multitextureDataPtr, GL_STATIC_DRAW_ARB );

	m3_VBO::glGenBufferVBO()( 1, &_vertexBufferId->normalId );							
	m3_VBO::glBindBufferVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId );		
	m3_VBO::glBufferDataVBO()( GL_ARRAY_BUFFER_ARB, _vertexBufferPtr->nVerteces*3*sizeof(float), _vertexBufferPtr->normalDataPtr, GL_STATIC_DRAW_ARB );


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

float m3_Heightmap::GetHeight(float _positionX,float _positionZ)
{
    int roundPositionX = (int) _positionX;
    int roundPositionZ = (int) _positionZ;

    float remainPositionX = _positionX - roundPositionX;
    float remainPositionZ = _positionZ - roundPositionZ;

    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (_width - 1)) || (roundPositionZ > (_height - 1)))
       return 0.0f;
        
    float height_11 = _heightmap[roundPositionX][roundPositionZ]*0.1f - 32.0f;
    float height_12 = _heightmap[roundPositionX][roundPositionZ +1]*0.1f - 32.0f;
    float height_21 = _heightmap[roundPositionX + 1][roundPositionZ]*0.1f - 32.0f;
    float height_22 = _heightmap[roundPositionX + 1][roundPositionZ + 1]*0.1f - 32.0f;
    float mainHeight;

    if( remainPositionX > remainPositionZ )
        {
                mainHeight = height_11 + (height_22 - height_21)*remainPositionZ + (height_21 - height_11)*remainPositionX;
        }
        else
        {
                mainHeight = height_11 + (height_22 - height_12)*remainPositionX + (height_12 - height_11)*remainPositionZ;
        }

        float height = (1 - remainPositionX) * ((1 - remainPositionZ) * height_11 + remainPositionZ * height_12) + remainPositionX * ((1 - remainPositionZ) * height_21 + remainPositionZ * height_22);
        return height;
}


void m3_Heightmap::Update()
{
	_UpdateWorldMatrix();
}

void m3_Heightmap::Render()
{
	_EnableShader();
	_UpdateShaderParams();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	m3_VBO::glBindBufferVBO()(GL_ARRAY_BUFFER_ARB, _vertexBufferId->vertexId);
	glVertexPointer(3, GL_FLOAT, 0,  NULL);		
	m3_VBO::glBindBufferVBO()(GL_ARRAY_BUFFER_ARB, _vertexBufferId->textureCoordId);
	glTexCoordPointer(2, GL_FLOAT, 0,NULL);
	m3_VBO::glBindBufferVBO()(GL_ARRAY_BUFFER_ARB, _vertexBufferId->multitexId);
	glColorPointer(4, GL_FLOAT, 0,NULL);
	m3_VBO::glBindBufferVBO()(GL_ARRAY_BUFFER_ARB, _vertexBufferId->normalId);
	glNormalPointer(GL_FLOAT, 0,NULL);

	glDrawElements( GL_TRIANGLES, _vertexBufferPtr->nIndeces, GL_UNSIGNED_INT, &_vertexBufferPtr->indecesPtr[0] );

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	_DisableShader();
}