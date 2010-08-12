#ifndef _MESH_H_
#define _MESH_H_

#include <string>
#include <math.h>
#include "Dummy.h"
#include "Resource.h"
#include "Matrix4x4.h"

class Mesh : public Dummy
{
	// VARIBLES
private :
	//m3_ComplexMeshData *_complexMeshData;
	// FUNCTION
private :
	void _CalculateNormals();
public :
	ChunkBuffer *_chunkBuffer;
	std::string meshOriginalName;
	std::string _meshFileName;
	// FUNCTION
public :
	Mesh();
	void Load(const char* fileName,const char* meshName);
	virtual void Load(std::string value) {};
	virtual void Update();
	virtual void Render();
	void RenderChunk(std::string value);
	void RenderNormals();
};

#endif