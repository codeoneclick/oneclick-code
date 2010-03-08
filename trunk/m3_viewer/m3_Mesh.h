#pragma once
#ifndef _M3_MESH_H_
#define _M3_MESH_H_

#include <string>
#include <fstream>
#include <math.h>
#include "m3_DDSLoader.h"
#include "m3_FileFormat.h"
#include "m3_Input.h"

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
	// FUNCTION
private :
	void _CalculateNormals();
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