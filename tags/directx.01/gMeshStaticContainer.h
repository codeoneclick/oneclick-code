#pragma once
#ifndef _G_MESHSTATICCONTAINER_H_
#define _G_MESHSTATICCONTAINER_H_

#include "gMeshContainer.h"

class gMeshStaticContainer : public gMeshContainer
{
private:
	void ReadVertexData(const char* name);
	void ReadTextureData(const char* name);
	void ReadIndexData(const char* name);

	virtual void _WriteToDeviceVertexBuffer();
	virtual void _WriteToDeviceIndexBuffer();

public :
	gMeshStaticContainer() {};
	virtual void Load(const gResourceData *resource);
	gMeshStaticData GetMeshData();
};

#endif