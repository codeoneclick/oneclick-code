#ifndef _3DS_H_
#define _3DS_H_

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "../../Game/Enviroment/Mesh.h"
#include "../../Math/Util.h"

namespace Loader
{
class C3DS
{
private :
	struct S3DSReadData
	{
		unsigned int nVerteces;
		unsigned int nIndeces;

		math::Vector3d *vPosition;
		math::Vector2d<float> *vTexCoord;
		unsigned int           *indexData;
	};

public :
	struct S3DSVertex
	{
		math::Vector3d vPosition;
		math::Vector2d<float> vTexCoord;
		math::Vector3d vNormal;
		math::Vector3d vTangent;
		math::Vector3d vBinormal;
	};

	struct S3DSChunk
	{	
		unsigned int *indexData;
		unsigned int nIndeces;
	};

	struct S3DSFile
	{
		S3DSVertex  *vertexData;
		unsigned int nVerteces;

		unsigned int nIndeces;
		unsigned int *indexData;

		unsigned int nChunks;
		std::map<std::string, S3DSChunk*> chunks;
	};

public :
	static S3DSFile* ReadData(std::string value);
	static void Commit(S3DSFile *in_value, Core::CMesh *out_value);
};
};

#endif