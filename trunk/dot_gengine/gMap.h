#pragma once
#ifndef _G_MAP_H_
#define _G_MAP_H_

#include "gGround.h"
#include "gWater.h"
#include "gGrass.h"

class gMap
{
private:
	gGround *ground;
	gWater *water;
	gGrass *grass;

	LoadLODFlags load_lod_flag;
	RenderLODFlags render_lod_flag;
	LoadLODFlags realtime_load_lod_flag;

    int _mapChankIndexI;
    int _mapChankIndexJ;

	float** _mapHeightsReference;
	gMapTileMask** _mapTextureMaskReference;
	gMapDecoration** _mapDecorationMaskReference;

public :
	gMap(int mapChankIndexI,int mapChankIndexJ);
	~gMap();
	void Create();
	void Render(RenderFlags flag);
	void Update(bool reflection_flag);
	void Load();
	void Unload();
	__forceinline void SetEffectName(std::string currentEffectName) { this->ground->currentEffectName = currentEffectName; }
	__forceinline LoadLODFlags GetLoadFlag(){return this->load_lod_flag;}
	__forceinline RenderLODFlags GetRenderFlag(){return this->render_lod_flag;}
	__forceinline LoadLODFlags GetRealTimeLoadFlag(){return this->realtime_load_lod_flag;}
	__forceinline void SetRealTimeLoadFlag(LoadLODFlags flag){this->realtime_load_lod_flag = flag;}
	__forceinline void SetLoadFlag(LoadLODFlags flag){ this->load_lod_flag = flag;}
	__forceinline void SelRenderFlag(RenderLODFlags flag){this->render_lod_flag = flag;}
	void EditGround() { this->ground->EditGround(); }
	//void EditHeightMap(float** heightmap);
	//void EditGrass(float** map_heightmap,struct_map_mask **map_tile_mask);
	void Textures();

	void SetReflection(LPDIRECT3DTEXTURE9 models_texture,LPDIRECT3DTEXTURE9 sky_texture);

	void SetMapHeights(float** mapHeightsReference);
	void SetTextureMask(gMapTileMask** mapTextureMaskReference);
	void SetDecorationMask(gMapDecoration** mapDecorationMaskReference);

	__forceinline int GetMapChankIndexI() { return this->_mapChankIndexI; }
	__forceinline int GetMapChankIndexJ() { return this->_mapChankIndexJ; }
	//void Texturize(struct_map_mask** map_tile_mask,float power_color_r,float power_color_g,float power_color_b,float point_position_x, float point_position_z);
	//void DrawGrassMask(struct_map_mask** map_tile_mask,float power_color_r,float power_color_g,float power_color_b,float point_position_x, float point_position_z);
	//bool IntersectRay(const D3DXVECTOR3 *pRayPos, const D3DXVECTOR3 *pRayDir, float * toPointDistance,D3DXVECTOR3 * Point);

	//void CreateDeepTexture();
};

#endif