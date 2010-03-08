#include "gMap.h"

gMap::gMap(int mapChankIndexI, int mapChankIndexJ){
	this->_mapChankIndexI = mapChankIndexI;
	this->_mapChankIndexJ = mapChankIndexJ;

	this->load_lod_flag = L_UNLOAD;
	this->render_lod_flag = R_UNLOAD;

	this->ground = new gGround();
	gResourceData resource;
	resource.currentEffectName = "ground_effect";
	resource.effectResources.push_back("ground_effect");
	resource.effectResources.push_back("shadow_effect");
	resource.textureResources.push_back("tile_layer_color_01");
	resource.textureResources.push_back("tile_layer_color_02");
	resource.textureResources.push_back("tile_layer_color_03");
	resource.textureResources.push_back("tile_layer_normal_01");
	resource.textureResources.push_back("tile_layer_normal_02");
	resource.textureResources.push_back("tile_layer_normal_03");
	resource.textureResources.push_back("tile_layer_color_04");
	resource.textureResources.push_back("tile_layer_normal_04");
	this->ground->Load(&resource);
	this->ground->SetMapChankIndex(this->_mapChankIndexI,this->_mapChankIndexJ);
	this->water = new gWater();
	this->grass = new gGrass();
}

gMap::~gMap()
{

}

void gMap::SetMapHeights(float** mapHeightsReference)
{
	this->_mapHeightsReference = mapHeightsReference;
	this->ground->SetMapHeights(this->_mapHeightsReference);
}

void gMap::SetTextureMask(gMapTileMask** mapTextureMaskReference)
{
	this->_mapTextureMaskReference = mapTextureMaskReference;
	this->ground->SetTextureMask(this->_mapTextureMaskReference);
}

void gMap::SetDecorationMask(gMapDecoration** mapDecorationMaskReference)
{
	this->_mapDecorationMaskReference = mapDecorationMaskReference;
	this->ground->SetDecorationMask(this->_mapDecorationMaskReference);
}

/*bool gMap::IntersectRay(const D3DXVECTOR3 *pRayPos, const D3DXVECTOR3 *pRayDir, float * toPointDistance,D3DXVECTOR3 * Point){
	//if(this->render_lod_flag != R_UNLOAD)
	//	return this->ground->IntersectRay(pRayPos,pRayDir,toPointDistance,Point);
	//else
		return false;
}*/

void gMap::Create(){
	this->water->Create(this->_mapChankIndexI,this->_mapChankIndexJ);
	this->grass->Create(this->_mapHeightsReference,this->_mapDecorationMaskReference,this->_mapChankIndexI,this->_mapChankIndexJ);
}

/*void gMap::EditGrass(float** map_heightmap,struct_map_mask **map_tile_mask)
{
	this->grass->Create(map_heightmap,map_tile_mask,this->map_index_i,this->map_index_j);
}*/


void gMap::Textures(){
	this->water->Textures();
	this->grass->Textures();

}
//void gMap::CreateGrass(){
//	this->grass->Create(map_heightmap,map_tile_mask);
//}

//void gMap::GroundTextures(){
//    this->ground->Textures();
//}

//void gMap::GrassTextures(){
//	this->grass->Textures();
//}

//void gMap::WaterTextures(){
//	this->water->TextureNormal();
//	this->water->TextureReflection(NULL);
//}

/*void gMap::EditHeightMap(float** heightmap){
	//this->ground->EditHeightMap(heightmap);
}

void gMap::Texturize(struct_map_mask** map_tile_mask,float power_color_r,float power_color_g,float power_color_b, float point_position_x, float point_position_z){
	//this->ground->Texturize(map_tile_mask,power_color_r,power_color_g,power_color_b,point_position_x,point_position_z,this->render_lod_flag);
}

void gMap::DrawGrassMask(struct_map_mask** map_decoration_mask,float power_color_r,float power_color_g,float power_color_b, float point_position_x, float point_position_z){
	//this->ground->DrawGrassMask(map_decoration_mask,power_color_r,power_color_g,power_color_b,point_position_x,point_position_z,this->render_lod_flag);
}*/

void gMap::Load()
{
	
	switch(this->load_lod_flag)
	{
		case L_HIGH:
			this->ground->SetHighChankMap();
			this->render_lod_flag = R_HIGH;
			break;
		case L_MIDDLE:
			this->ground->SetMiddleChankMap();
			this->render_lod_flag = R_MIDDLE;
			break;
		case L_LOW:
			this->ground->SetLowChankMap();
			this->render_lod_flag = R_LOW;
			break;
		case L_UNLOAD:
			this->render_lod_flag = R_UNLOAD;
			this->load_lod_flag = L_UNLOAD;
			this->ground->UnloadChankMap();
			break;
	}
}

void gMap::Unload(){
	this->render_lod_flag = R_UNLOAD;
	this->load_lod_flag = L_UNLOAD;
	this->ground->UnloadChankMap();
}

void gMap::Update(bool reflection_flag){
	if(this->render_lod_flag != R_UNLOAD){
		this->ground->Update();
		if(!reflection_flag)
			this->water->Update();
		this->grass->Update();
	}
}

/*void gMap::CreateDeepTexture(){
	LPDIRECT3DTEXTURE9 temp_deep_texture = NULL;
	temp_deep_texture = this->water->GetDeepTexture();
	D3DXCreateTexture(Device,64,64,1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &temp_deep_texture);
	D3DLOCKED_RECT texture_rectangle;
	temp_deep_texture->LockRect(0, &texture_rectangle, NULL, 0);
	for(int i = 0; i < 64; ++i)
		for(int j = 0; j < 64; ++j){
			((DWORD*)texture_rectangle.pBits)[i*64+j] = 128;
		}
	temp_deep_texture->UnlockRect(0);

	this->water->SetDeepTexture(temp_deep_texture);

	
	//LPDIRECT3DDEVICE9 pDevice=NGECore::GetDevice();
	//HRESULT res=D3DXCreateTexture(pDevice , DEEP_TEXTURE_SIZE, DEEP_TEXTURE_SIZE, 1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &theDeepTexture);
	//if (res==D3D_OK){
	//	D3DLOCKED_RECT lockrect;
	//	HRESULT	dxres = theDeepTexture->LockRect(0, &lockrect, NULL, 0);
	//	bool falseFormat = (lockrect.Pitch / DEEP_TEXTURE_SIZE) == 4;
	//	if (dxres==S_OK){
	//		float dx=(theTileBound.max.x-theTileBound.min.x)/(float)(DEEP_TEXTURE_SIZE-1);
	//		float dz=(theTileBound.max.z-theTileBound.min.z)/(float)(DEEP_TEXTURE_SIZE-1);
	//		for (int z=0;z<DEEP_TEXTURE_SIZE;z++){
	//			float z_offset=((dz*z)/theGroundCellSize)+1.0f;
	//			int indexZ=(int)z_offset;
	//			float lerpZ=z_offset-indexZ;
	//			for (int x=0;x<DEEP_TEXTURE_SIZE;x++){
	//				float x_offset=((dx*x)/theGroundCellSize)+1.0f;
	//				int indexX=(int)x_offset;
	//				float lerpX=x_offset-indexX;
	//				int heightIndex=indexX+indexZ*theGroundHeightCountX;
	//				D3DXVECTOR4 heights;
	//				heights.x=theHeightData[heightIndex];
	//				heights.y=theHeightData[heightIndex+1];
	//				heights.z=theHeightData[heightIndex+theGroundHeightCountX];
	//				heights.w=theHeightData[heightIndex+theGroundHeightCountX+1];
	//				float height=lerp(lerp(heights.x,heights.y,lerpX),lerp(heights.z,heights.w,lerpX),lerpZ)*GROUND_HEIGHT_COEFF - this->water_level;
	//				if(height < 0)
	//					height = 0.0f;
	//				if (height< DEFAULT_WATER_HEIGHT ){
	//					if (falseFormat){
	//						DWORD color=(255-(BYTE)(height/DEFAULT_WATER_HEIGHT*255)) << 24;
	//						((DWORD*)lockrect.pBits)[z*DEEP_TEXTURE_SIZE+x]=color;
	//					}else{
	//						BYTE color=(255-(BYTE)(height/DEFAULT_WATER_HEIGHT*255));
	//						((BYTE*)lockrect.pBits)[z*DEEP_TEXTURE_SIZE+x]=color;
	//					}
	//				}else 
	//					if (falseFormat)
	//						((DWORD*)lockrect.pBits)[z*DEEP_TEXTURE_SIZE+x]=0;
	//					else
	//						((BYTE*)lockrect.pBits)[z*DEEP_TEXTURE_SIZE+x]=0;
	//					
	//			}
	//		}
	//		theDeepTexture->UnlockRect(0);
	//	}
	//}
	
}*/
/*

void gMap::SetReflection(LPDIRECT3DTEXTURE9 models_texture,LPDIRECT3DTEXTURE9 sky_texture){
	if((this->render_lod_flag != R_UNLOAD) && this->ground->WaterEnable())
		this->water->SetReflection(models_texture,sky_texture);
}*/

void gMap::Render(RenderFlags flag){
	//this->ground->flag = render_lod_flag;
	if(this->render_lod_flag != R_UNLOAD && flag == GROUND){
		this->ground->SetRenderFlag(this->render_lod_flag);
		this->ground->Render();
	}
	//if(this->render_lod_flag != R_UNLOAD && flag == GROUND){
	//	this->ground->Render(false);
	//}
	if((this->render_lod_flag != R_UNLOAD) && (flag == WATER) && this->ground->WaterEnable()){
		this->water->Render();
	}
	if(flag == GRASS){
		this->grass->Render();
	}
}