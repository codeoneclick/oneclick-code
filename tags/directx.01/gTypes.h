#pragma once
#ifndef _G_TYPE_H_
#define _G_TYPE_H_

#include <d3dx9.h>
#include <map>
#include <vector>

typedef unsigned char uint8;
typedef char int8;
typedef unsigned __int16 uint16;
typedef __int16 int16;
typedef unsigned __int32 uint32;
typedef __int32 int32;

#define POLYGON_SIZE  10

#define HIGH_MAP_SIZE   64
#define MIDDLE_MAP_SIZE 32
#define LOW_MAP_SIZE    16

#define HIGH_VERTECES (HIGH_MAP_SIZE + 1)*(HIGH_MAP_SIZE + 1)
#define HIGH_PRIMITIVES HIGH_MAP_SIZE*HIGH_MAP_SIZE*2

#define MIDDLE_VERTECES (MIDDLE_MAP_SIZE + 1)*(MIDDLE_MAP_SIZE + 1)
#define MIDDLE_PRIMITIVES MIDDLE_MAP_SIZE*MIDDLE_MAP_SIZE*2

#define LOW_VERTECES (LOW_MAP_SIZE + 1)*(LOW_MAP_SIZE + 1)
#define LOW_PRIMITIVES LOW_MAP_SIZE*LOW_MAP_SIZE*2

enum RenderFlags {GROUND = 0, WATER, GRASS};

enum BlockedFlags {NONE = 0,X, Y, Z};

enum TextureType {NORMAL = 0,CUBE};

enum LoadLODFlags {L_LOW = 0, L_MIDDLE, L_HIGH, L_UNLOAD};

enum RenderLODFlags {R_LOW = 0, R_MIDDLE, R_HIGH, R_UNLOAD};

enum GUITextureFlags {T_MAIN = 0, T_ON_MOUSE, T_ON_PRESS, T_DISABLE};

enum GUIColorFlags {C_MAIN = 0, C_ON_MOUSE, C_ON_PRESS, C_DISABLE};

enum TextAlignFlag { T_LEFT = 0, T_RIGHT, T_TOP, T_BOTTOM, T_VERTICAL_CENTER, T_HORIZONTAL_CENTER};

enum GroundFlags   {G_HIGH,G_MIDDLE,G_LOW};

enum Md2Animation {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH, 
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,
	MAX_ANIMATIONS
};

struct gSimpleVertexFormat
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 textureCoordinates;
};

struct gTBNInfo
{
	D3DXVECTOR3 _normal;
	D3DXVECTOR3 _tangent;
	D3DXVECTOR3 _binormal;
};

struct gMeshOptions
{
	unsigned short nVerteces;
	unsigned short nIndeces;
	unsigned short nPrimitives;
	unsigned short nTextures;
	unsigned short groundChankSize;
	unsigned short incGroundChankSize;
	unsigned short vertexOffset;

	gMeshOptions()
	{
	}
};

struct gmt
{

};

struct gmi
{
	unsigned short startIndex;
	unsigned short countPrimitive;
};

struct gMeshStaticData
{
	IDirect3DVertexBuffer9* vb;
	IDirect3DIndexBuffer9*  ib;
	
	std::vector<IDirect3DTexture9*> texturesColorList;
	std::vector<IDirect3DTexture9*> texturesNormalList;
	
	std::map<std::string,ID3DXEffect*> effectsList;
	
	gmi *indexInfo;
	
	unsigned short nVertices;
	unsigned short nTextures;
	unsigned short nIndices;
};

struct SMD2Header
	{
	  int ident;
	  int version;
	  int skinwidth;		
	  int skinheight;	
	  int framesize;
	  int num_skins;	
	  int num_xyz;			
	  int num_st;
	  int num_tris;		
	  int num_glcmds;
	  int num_frames;			
	  int ofs_skins;
	  int ofs_st;
	  int ofs_tris;
	  int ofs_frames;
	  int ofs_glcmds; 
	  int ofs_end;
};

struct gMd2IndexList
{
	D3DXVECTOR3 index;
	D3DXVECTOR2 textureCoord[3];
};

struct gMd2FrameVertexList
{
	D3DXVECTOR3 *vertex;
};

struct gMd2TriangleData
{
	short index_xyz[3];
	short index_st[3];
};

struct gMd2NormalData
{
	unsigned char v[3];
	unsigned char lightnormalindex;
};

struct gMd2TriangleFrameData
{
	float scale[3];
	float translate[3];
	char  name[16];
	gMd2NormalData verts[1];
};

struct gMd2Vertex 
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 textureCoordinates;
    D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;
	D3DXVECTOR4 layer_0;
	D3DXVECTOR4 layer_1;
};

struct gMd2FrameVertexData
{
	gMd2Vertex *verteces;
};

struct gMd2TextureCoordData
{
	short s;
	short t;
};

struct gMeshDynamicData
{
	std::vector<IDirect3DTexture9*> texturesColorList;
	std::vector<IDirect3DTexture9*> texturesNormalList;
	std::map<std::string,ID3DXEffect*> effectsList;
	gMd2FrameVertexData *ptrFrameVertexData;

	IDirect3DVertexBuffer9* tvb;
	IDirect3DVertexBuffer9** vb;
	IDirect3DIndexBuffer9*  ib;

	int nTriangles;
	int nVerteces;
};



namespace md2
{
struct header
{
	int magic_number;
	int version;

	int skinwidth;
	int skinheight;
	int framesize;

	int num_skin;
	int num_xyz;
	int num_st;
	int num_tris;
	int num_glcmds;
	int num_frames;

	int ofs_skins;
	int ofs_st;
	int ofs_tris;
	int ofs_frames;
	int ofs_glcmds;
	int ofs_end;
};

struct raw_vertex
{
	byte vertex[3];
	byte unused_normal_index;
};

struct frame
{
	float scale[3];
	float translate[3];
	char name[16];
	raw_vertex verticies[1];
};

struct triangle
{
	short vertex_indicies[3];
	short texture_indicies[3];
};
typedef short index_buffer[3];

struct tex_coord
{
	short s, t;
};

typedef char skin_name[64];

};

struct MD2_POSITION_VERTEX
{
	union
	{
		struct
		{
			float x, y, z;
		};
		float a[3];
	};
};

struct MD2_TEXTURE_VERTEX
{
	union
	{
		struct
		{
			float s, t;
		};
		float a[2];
	};
};

struct gStaticModelTag
{
	char tagName[2];
	unsigned int dataBlockOffset;
	unsigned int dataBlockSize;
};

struct gStaticModelHeader
{
	char id[3];
	gStaticModelTag vertexData;
	gStaticModelTag indexData;
	gStaticModelTag textureData;
};

struct gStaticModelVertexBlock
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 textCoords;
};

#endif


