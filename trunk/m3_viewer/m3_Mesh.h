#pragma once
#ifndef _M3_MESH_H_
#define _M3_MESH_H_

#include <string>
#include <fstream>
#include <math.h>
#include "m3_DDSLoader.h"
#include "m3_FileFormat.h"
#include "m3_Input.h"

#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_STATIC_DRAW_ARB 0x88E4
typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);

struct m3_Vertex
{
	float u,v;
	float normal[3];
	float x, y, z;
};

struct m3_Data_Vertex
{
	float x,y,z;
};

struct m3_Data_Normal
{
	float x,y,z;
};

struct m3_Data_TextureCoord
{
	float u,v;
};

class m3_Mesh
{
	// VARIBLES
private :
	m3_Vertex *d_Verteces;
	unsigned short *d_Indeces;

	m3_Data_Vertex *data_vertex;
	m3_Data_Normal *data_normal;
	m3_Data_TextureCoord *data_textureCoord;

	unsigned int nVerteces;
	unsigned int nIndeces;

	bool _extVersion;

		// Vertex Buffer Object Names
	unsigned int vb_id;				
	unsigned int tb_id;		
	unsigned int nb_id;			
	// FUNCTION
private :
	void _CalculateNormals();

	// VBO Extension Function Pointers
	PFNGLGENBUFFERSARBPROC glGenBuffersARB;					// VBO Name Generation Procedure
	PFNGLBINDBUFFERARBPROC glBindBufferARB;					// VBO Bind Procedure
	PFNGLBUFFERDATAARBPROC glBufferDataARB;					// VBO Data Loading Procedure
	PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;			// VBO Deletion Procedure
    // VARIBLES
public :
	std::string meshName;
	GLuint textureColorId;
	GLuint textureNormalId;
	// FUNCTION
public :
	m3_Mesh();
	void Load(const char* fileName,const char* meshName);
	void Convert();
	void Update();
	void Render();
	void RenderNormals();
};

#endif