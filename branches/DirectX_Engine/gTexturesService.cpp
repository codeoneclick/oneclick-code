#include "gTexturesService.h"

void gTexturesService::Load()
{
	//Insert("mucklowlands.dds","tile_layer_color_01");
	//Insert("stones.bmp","tile_layer_color_01");
	
	Insert("grass.dds","tile_layer_color_01");
	Insert("sand.dds","tile_layer_color_02");
	Insert("rock.dds","tile_layer_color_03");
	Insert("road.dds","tile_layer_color_04");

	//Insert("mucklowlands_NRM_DISP.dds","tile_layer_normal_01");
	//Insert("stones_NM_height.tga","tile_layer_normal_01");
	Insert("grass_nh.dds","tile_layer_normal_01");
	Insert("sand_nh.dds","tile_layer_normal_02");
	Insert("rock_nh.dds","tile_layer_normal_03");
	Insert("road_nh.dds","tile_layer_normal_04");
	
	//Insert("Tower_01.dds","Tower_01");
	//Insert("Tower_01_n.dds","Tower_01_n");
	//Insert("Champel.dds","Champel");
	//Insert("Defender.dds","Defender");

	Insert("water.dds", "water_texture_normal");

	Insert("mod_03.dds", "grassTexture_01");
	Insert("mod_02.dds", "grassTexture_02");
	Insert("mod_04.dds", "grassTexture_03");
	Insert("mod_03.dds", "grassTexture_04");

	

	//Insert("WESTFALLWEATHEREDBARN01SKIN.dds", "WESTFALLWEATHEREDBARN01SKIN.dds");
	//Insert("WestFallBaseStone.dds", "WestFallBaseStone.dds");
	//Insert("WESTFALLWEATHEREDBARN01ROOFSKIN.dds", "WESTFALLWEATHEREDBARN01ROOFSKIN.dds");
	//Insert("WestFarmWindow.dds", "WestFarmWindow.dds");
	//Insert("WestFallDoor.dds", "WestFallDoor.dds");

	
}

void gTexturesService::Insert(std::string key,IDirect3DTexture9* texture)
{
	_texturesContainer.insert(std::pair<std::string,IDirect3DTexture9*>(key,texture));
}

void gTexturesService::Insert(std::string name, std::string key)
{
	IDirect3DTexture9* texture;
	std::string file_name = name;
	std::string file_path = "Content\\textures\\";
	file_path += file_name;
	error_result =  D3DXCreateTextureFromFile(gDevice::device, file_path.c_str(), &texture);

	if(FAILED( error_result ))
	{
        error_name = ( char* )errors->GetBufferPointer();
		MessageBox(NULL, error_name ,"gEngine::TexturesService", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	_texturesContainer.insert(std::pair<std::string,IDirect3DTexture9*>(key,texture));

}

IDirect3DTexture9* gTexturesService::Find(std::string name)
{
	std::map<std::string,IDirect3DTexture9*>::iterator texture_iterator;
	texture_iterator = this->_texturesContainer.find(name);
	if(texture_iterator != this->_texturesContainer.end())
		return texture_iterator->second;
	else
		return NULL;
}