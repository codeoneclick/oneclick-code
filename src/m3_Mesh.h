#pragma once
#ifndef _M3_MESH_H_
#define _M3_MESH_H_

#include <string>
#include <math.h>
#include "m3_Entity.h"
#include "m3_DDSLoader.h"
#include "m3_Input.h"
#include "m3_Resource.h"
#include "Matrix4x4.h"

class m3_Mesh : public m3_Entity
{
	// VARIBLES
private :
	m3_ComplexMeshData *_complexMeshData;
	// FUNCTION
private :
	void _CalculateNormals();	
public :
	std::string meshOriginalName;
	std::string _meshFileName;
	// FUNCTION
public :
	m3_Mesh();
	void Load(const char* fileName,const char* meshName);
	virtual void Load(std::string value) {};
	virtual void Update();
	virtual void Render();
	void RenderChunk(std::string value);
	void RenderNormals();
};

#endif