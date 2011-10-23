#pragma once
#ifndef _G_MODEL3D_H_
#define _G_MODEL3D_H_

#include <vector>
#include "gEntity.h"
#include "gTypes.h"
#include "gResourceData.h"

class gModel3D : public gEntity
{
	protected :
		IDirect3DVertexBuffer9* vb;
		IDirect3DIndexBuffer9*  ib;
		std::vector<IDirect3DTexture9*> texturesColorList;
		std::vector<IDirect3DTexture9*> texturesNormalList;
		std::map<std::string,ID3DXEffect*> effectsList;

		unsigned short* _simpleIndexBuffer;
		unsigned short* _indexBuffer;
		gSimpleVertexFormat* _simpleVertexBuffer;
		gVertex* _vertexBuffer;

		gTBNInfo* _TBNInfo;

		gCamera	    *cCamera;
		gLight		*cLight;

		void _CalculateTBN(unsigned int nVerteces,unsigned int nIndeces);

	public :
		gModel3D();
		virtual void Load(const gResourceData *resource) = 0;
		virtual void Render() = 0;

		std::string currentEffectName;
};
#endif