#pragma once
#ifndef _G_RESOURCEDATA_H_
#define _G_RESOURCEDATA_H_

#include <d3dx9.h>
#include <vector>

struct gResourceData
{
	std::vector<char*> meshResources;
	std::vector<char*> textureResources;
	std::vector<std::string> effectResources;
	
	std::string currentEffectName;

	char* vertexFileName;
	char* indexFileName;
	char* texturesListFileName;

	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vRotation;
	D3DXVECTOR3 vScale;

	gResourceData()
	{
		this->vPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
		this->vRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
		this->vScale    = D3DXVECTOR3(1.0f,1.0f,1.0f);

		vertexFileName = NULL;
		indexFileName = NULL;
		texturesListFileName = NULL;
	}
};

#endif