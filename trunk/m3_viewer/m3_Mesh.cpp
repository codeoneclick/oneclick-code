#include "m3_Mesh.h"

m3_Mesh::m3_Mesh()
{
	d_Verteces = NULL;
	d_Indeces = NULL;

	data_vertex = NULL;
	data_normal = NULL;
	data_textureCoord = NULL;

	nVerteces = 0;;
	nIndeces = 0;

	_extVersion = true;

	meshName = "";
	textureColorId = -1;
	textureNormalId = -1;
}

void m3_Mesh::Load(const char* fileName,const char* meshName)
{
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

	this->meshName = meshName;

	std::ifstream inStream;
	inStream.open(fileName,std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();

	m3_Header *header = (m3_Header*)fileData;
	m3_Tag *tags =(m3_Tag*)(fileData + header->tagsOffset);
	
	m3_VertexBlockExt *vertexBlockExt;
	m3_VertexBlock *vertexBlock;
	short *indexBlock;

	std::string diffuseTextureName;

	bool firstIndexBlockFlag = false;

	for(unsigned int i = 0; i < header->nTags; ++i)
	{
		if((tags[i].tagName[2] == '8') && (tags[i].tagName[3] == 'U'))
		{
			_extVersion = true;
			nVerteces = (tags[i].blockSize)/sizeof(m3_VertexBlockExt);
			vertexBlockExt = (m3_VertexBlockExt*)(fileData + tags[i].blockOffset);
			
			if(vertexBlockExt[0].unknValues[7] != 255)
			{
				nVerteces = (tags[i].blockSize)/sizeof(m3_VertexBlock);
				vertexBlock = (m3_VertexBlock*)(fileData + tags[i].blockOffset);
				_extVersion = false;
			}
		}
		if((tags[i].tagName[1] == '6') && (tags[i].tagName[2] == '1') && (tags[i].tagName[3] == 'U'))
		{
			if(firstIndexBlockFlag) continue;
			firstIndexBlockFlag = true;
			nIndeces = tags[i].blockSize;
			indexBlock = (short*)(fileData + tags[i].blockOffset);
		}

		if((tags[i].tagName[0] == '_') && (tags[i].tagName[1] == 'T') && (tags[i].tagName[2] == 'A') && (tags[i].tagName[3] == 'M'))
		{
			diffuseTextureName = (char*)(fileData + tags[i + 3].blockOffset);
		}
	}
	
	d_Verteces = new m3_Vertex[nVerteces];

	data_vertex = new m3_Data_Vertex[nVerteces];
	data_normal = new m3_Data_Normal[nVerteces];
	data_textureCoord = new m3_Data_TextureCoord[nVerteces];

	for(unsigned int i = 0; i < nVerteces; ++i)
	{
		if(_extVersion)
		{
			data_vertex[i].x = vertexBlockExt[i].position[0];
			data_vertex[i].y = vertexBlockExt[i].position[1];
			data_vertex[i].z = vertexBlockExt[i].position[2];

			data_normal[i].x = (float)2*vertexBlockExt[i].normal[0]/255.0f - 1.0f;
			data_normal[i].y = (float)2*vertexBlockExt[i].normal[1]/255.0f - 1.0f;
			data_normal[i].z = (float)2*vertexBlockExt[i].normal[2]/255.0f - 1.0f;

			data_textureCoord[i].u = (float)vertexBlockExt[i].uv[0]/2048.0f;
			data_textureCoord[i].v = (float)vertexBlockExt[i].uv[1]/2048.0f;

			d_Verteces[i].normal[0] = (float)vertexBlockExt[i].normal[0]/254.0f;
			d_Verteces[i].normal[1] = (float)vertexBlockExt[i].normal[1]/254.0f;
			d_Verteces[i].normal[2] = (float)vertexBlockExt[i].normal[2]/254.0f;
			d_Verteces[i].u = (float)vertexBlockExt[i].uv[0]/2048.0f; d_Verteces[i].v =(float)vertexBlockExt[i].uv[1]/2048.0f;
			d_Verteces[i].x = vertexBlockExt[i].position[0]; d_Verteces[i].y = vertexBlockExt[i].position[1]; d_Verteces[i].z = vertexBlockExt[i].position[2];
		}
		else
		{
			data_vertex[i].x = vertexBlock[i].position[0];
			data_vertex[i].y = vertexBlock[i].position[1];
			data_vertex[i].z = vertexBlock[i].position[2];

			data_normal[i].x = (float)2*vertexBlock[i].normal[0]/255.0f - 1.0f; 
			data_normal[i].y = (float)2*vertexBlock[i].normal[1]/254.0f - 1.0f;
			data_normal[i].z = (float)2*vertexBlock[i].normal[2]/255.0f - 1.0f;

			data_textureCoord[i].u = (float)vertexBlock[i].uv[0]/2048.0f;
			data_textureCoord[i].v = (float)vertexBlock[i].uv[1]/2048.0f;

			d_Verteces[i].normal[0] = (float)vertexBlock[i].normal[0]/254.0f;
			d_Verteces[i].normal[1] = (float)vertexBlock[i].normal[1]/254.0f;
			d_Verteces[i].normal[2] = (float)vertexBlock[i].normal[2]/254.0f;
			d_Verteces[i].u = (float)vertexBlock[i].uv[0]/2048.0f; d_Verteces[i].v =(float)vertexBlock[i].uv[1]/2048.0f;
			d_Verteces[i].x = vertexBlock[i].position[0]; d_Verteces[i].y = vertexBlock[i].position[1]; d_Verteces[i].z = vertexBlock[i].position[2];
		}
	}

	d_Indeces = new unsigned short[nIndeces];

	for(unsigned int i = 0; i < nIndeces; ++i)
	{
		d_Indeces[i] = indexBlock[i];
		if(d_Indeces[i] > nVerteces) 
			int g = 0;
	}

	//if(_extVersion)
	//_CalculateNormals();

	std::string _textureFilePath   = "Content\\Textures\\";

	std::string _textureFileName = meshName;
	_textureFileName.erase(_textureFileName.length() - 3,3);
	

	_textureFilePath.insert(_textureFilePath.length(),_textureFileName);
	_textureFilePath.insert(_textureFilePath.length(),"_diffuse.dds");

	textureName = _textureFilePath;

	//m3_DDSLoader::Load(_textureFilePath.c_str(),&textureColorId);


	// Generate And Bind The Vertex Buffer
	glGenBuffersARB( 1, &vb_id );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vb_id );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, nVerteces*3*sizeof(float), data_vertex, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &tb_id );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, tb_id );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, nVerteces*2*sizeof(float), data_textureCoord, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &nb_id );							
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, nb_id );		
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, nVerteces*3*sizeof(float), data_normal, GL_STATIC_DRAW_ARB );

	// Generate And Bind The Texture Coordinate Buffer
	//glGenBuffersARB( 1, &m_nVBOTexCoords );							// Get A Valid Name
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBOTexCoords );		// Bind The Buffer
	// Load The Data
	//glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_nVertexCount*2*sizeof(float), m_pTexCoords, GL_STATIC_DRAW_ARB );


	//_textureFilePath   = "Content\\Textures\\";
    //_textureFilePath.insert(_textureFilePath.length(),_textureFileName);
	//_textureFilePath.insert(_textureFilePath.length(),"_normal.dds");

	//m3_DDSLoader::Load(_textureFilePath.c_str(),&textureNormalId);
}


void m3_Mesh::_CalculateNormals()
{
	float v1[3];
	float v2[3];
	float normal[3];

	for( int i = 0; i < nIndeces; i += 3 )
	{
		if(d_Indeces[i] > nVerteces) 
			continue;

		v1[0] = d_Verteces[d_Indeces[i+1]].x - d_Verteces[d_Indeces[i]].x;
		v1[1] = d_Verteces[d_Indeces[i+1]].y - d_Verteces[d_Indeces[i]].y;
		v1[2] = d_Verteces[d_Indeces[i+1]].z - d_Verteces[d_Indeces[i]].z;

		v2[0] = d_Verteces[d_Indeces[i+2]].x - d_Verteces[d_Indeces[i]].x;
		v2[1] = d_Verteces[d_Indeces[i+2]].y - d_Verteces[d_Indeces[i]].y;
		v2[2] = d_Verteces[d_Indeces[i+2]].z - d_Verteces[d_Indeces[i]].z;

		normal[0] =  v1[1] * v2[2] - v1[2] * v2[1];
		normal[1] =  v2[0] * v1[2] - v2[2] * v2[0];
		normal[2] =  v1[0] * v2[1] - v1[1] * v2[0];

		float vLength = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));
		normal[0] /= vLength;
		normal[1] /= vLength;
		normal[2] /= vLength;

		d_Verteces[d_Indeces[i]].normal[0] = normal[0];
		d_Verteces[d_Indeces[i]].normal[1] = normal[1];
		d_Verteces[d_Indeces[i]].normal[2] = normal[2];

		d_Verteces[d_Indeces[i + 1]].normal[0] = normal[0];
		d_Verteces[d_Indeces[i + 1]].normal[1] = normal[1];
		d_Verteces[d_Indeces[i + 1]].normal[2] = normal[2];

		d_Verteces[d_Indeces[i + 2]].normal[0] = normal[0];
		d_Verteces[d_Indeces[i + 2]].normal[1] = normal[1];
		d_Verteces[d_Indeces[i + 2]].normal[2] = normal[2];

		data_normal[d_Indeces[i]].x = normal[0];
		data_normal[d_Indeces[i]].y = normal[1];
		data_normal[d_Indeces[i]].z = normal[2];

		data_normal[d_Indeces[i + 1]].x = normal[0];
		data_normal[d_Indeces[i + 1]].y = normal[1];
		data_normal[d_Indeces[i + 1]].z = normal[2];

		data_normal[d_Indeces[i + 2]].x = normal[0];
		data_normal[d_Indeces[i + 2]].y = normal[1];
		data_normal[d_Indeces[i + 2]].z = normal[2];
	}
}

void m3_Mesh::Convert()
{
	std::string fileName = "Content\\Export\\";
	fileName += meshName;

	fileName.erase(fileName.length() - 3,3);
	fileName.insert(fileName.length(),".obj");

	char vertexTag = 'v';
	char indexTag  = 'f';
	char texCoordTag[2] =  { 'v','t' };
	char normalTag[2] = { 'v', 'n' };
	char space = ' ';
	char separator = '/';

	FILE *file = NULL;
	fopen_s(&file,fileName.c_str(),"w");



	for(int i = 0; i < nVerteces; ++i)
		 fprintf_s(file, "v %f %f %f\n", d_Verteces[i].x, d_Verteces[i].y, d_Verteces[i].z);


	for(int i = 0; i < nVerteces; ++i)
		 fprintf_s(file, "vt %f %f\n", d_Verteces[i].u, 1 - d_Verteces[i].v);


	for(int i = 0; i < nVerteces; ++i)
		 fprintf_s(file, "vn %f %f %f\n", d_Verteces[i].normal[0],d_Verteces[i].normal[1],d_Verteces[i].normal[2]);

	for(int i = 0; i < nIndeces; i+=3 )
		 fprintf_s(file, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", d_Indeces[i]+1, d_Indeces[i]+1, d_Indeces[i]+1,
                                                           d_Indeces[i + 1]+1, d_Indeces[i + 1]+1, d_Indeces[i + 1]+1,
                                                           d_Indeces[i + 2]+1, d_Indeces[i + 2]+1, d_Indeces[i + 2]+1);

	fclose(file);
}

void m3_Mesh::Update()
{
	glLoadIdentity();
	glTranslatef( 0.0f, -1.0f, -5.0f -m3_Input::mWheel );
	glRotatef( -m3_Input::mDeltaPosition.y - 90.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( -m3_Input::mDeltaPosition.x, 0.0f, 0.0f, 1.0f );
}

void m3_Mesh::RenderNormals()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	for(int i = 0; i < nVerteces; ++i)
	{
		glColor3f(0.5f,0.5f,0.5f);			
		glVertex3f(d_Verteces[i].x, d_Verteces[i].y, d_Verteces[i].z);	
		glColor3f(1.0f,1.0f,1.0f);			
		glVertex3f(d_Verteces[i].x -d_Verteces[i].normal[0]/2.0f, d_Verteces[i].y  - d_Verteces[i].normal[1]/2.0f, d_Verteces[i].z - d_Verteces[i].normal[2]/2.0f);	
	}
	glEnd();
}

void m3_Mesh::Render()
{
	//glVertexPointer(3,GL_FLOAT,0,&data_vertex[0]);
	//glNormalPointer(GL_FLOAT,0,&data_normal[0]);
	//glTexCoordPointer(2,GL_FLOAT,0,&data_textureCoord[0]);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vb_id );
	glVertexPointer( 3, GL_FLOAT, 0,  NULL );		// Set The Vertex Pointer To The Vertex Buffer
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, tb_id );
	glTexCoordPointer( 2, GL_FLOAT, 0,NULL );		// Set The TexCoord Pointer To The TexCoord Buffer
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, nb_id );
	glNormalPointer( GL_FLOAT, 0,NULL );

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//for( int i = 0; i < nIndeces; ++i)
	//{
	//	if(d_Indeces[i] > nVerteces) 
	//		continue;
	//}
	//glInterleavedArrays(GL_T2F_N3F_V3F, 0, &d_Verteces[0]);
	glDrawElements( GL_TRIANGLES, nIndeces, GL_UNSIGNED_SHORT, &d_Indeces[0] );

	//glDisableClientState( GL_VERTEX_ARRAY );					// Disable Vertex Arrays
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );				// Disable Texture Coord Arrays
	//glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}