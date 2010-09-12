#pragma once
#ifndef _G_MESHDYNAMIC_H_
#define _G_MESHDYNAMIC_H_

#include "gModel3D.h"
#include "gResource.h"
#include "gM3FileFormat.h"

struct gMd2Animation
{
	int	startFrameIndex;			
	int	lastFrameIndex;			
	int	fps;					
};

class gMeshDynamic : public gModel3D
{	
private:
	static gMd2Animation _animationList[21];
	gMd2FrameVertexData *_framesVertexData;
	int _nTriangles;
	int _nVerteces;
	int animationSpeed;
	int currentFrame;
	int startFrame;
	int endFrame;
    DWORD timerLastTime;
	Md2Animation currentAnimation;

	gMd2Vertex *points;
	short* indices;

	unsigned int nVertecesM3;
	unsigned int nIndicesM3;

	IDirect3DVertexBuffer9* m3vb;
	IDirect3DIndexBuffer9*  m3ib;

	short* _m3indexBuffer;
	gMd2Vertex* _m3vertexBuffer;


	IDirect3DVertexBuffer9** mvb;
	IDirect3DVertexBuffer9* tvb;

	//ID3DXEffect* Effect;
	IDirect3DTexture9* Texture;

public :
	gMeshDynamic();
	virtual void Load(const gResourceData *resource) {};
	void Load(gMeshDynamicData _meshData);
	void Update(std::string effectName);
	void Render(std::string effectName);

	void SetAnimation(Md2Animation value);

	virtual void Update() {};
	virtual void Render() {};

};
#endif