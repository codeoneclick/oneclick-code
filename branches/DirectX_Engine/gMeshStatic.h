#pragma once
#ifndef _G_MESHSTATIC_H_
#define _G_MESHSTATIC_H_

#include "gModel3D.h"
#include "gResource.h"

class gMeshStatic : public gModel3D
{	
private:
	gmi *indexInfo;

	unsigned short nVertices;
	unsigned short nTextures;
	unsigned short nIndices;

public :
	gMeshStatic();
	virtual void Load(const gResourceData *resource) {};
	void Load(gMeshStaticData _meshData);
	void Update(std::string effectName);
	void Render(std::string effectName);

	virtual void Update() {};
	virtual void Render() {};

};
#endif