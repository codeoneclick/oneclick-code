#include "gShadersService.h"


void gShadersService::Load()
{
	Insert("ground.fx",			 "ground_effect");
	Insert("water.fx",			 "water_effect");
	Insert("sky_and_clouds.fx",  "sky_effect");
	Insert("grass.fx",			 "grass_effect");
	Insert("mesh.fx",			 "mesh_effect");
	Insert("ShadowMap.fx",		 "shadow_effect");
	Insert("ShadowMapPost.fx",	 "shadow_effect_post");
	Insert("meshDynamic.fx",	 "dynamic_mesh_effect");
}

void gShadersService::Insert(std::string key,ID3DXEffect* shader)
{
	_shadersContainer.insert(std::pair<std::string,ID3DXEffect*>(key,shader));
}

void gShadersService::Insert(std::string name,std::string key)
{
	ID3DXEffect* shader;
	std::string file_name = name;
	std::string file_path = "Content\\shaders\\";
	file_path += file_name;

	error_result = D3DXCreateEffectFromFile(gDevice::device, file_path.c_str(), NULL, NULL, 0, NULL, &shader, &errors);
	
	if(FAILED( error_result ))
	{
        error_name = ( char* )errors->GetBufferPointer();
		MessageBox(NULL, error_name ,"gEngine::ShadersService", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	_shadersContainer.insert(std::pair<std::string,ID3DXEffect*>(key,shader));

}

ID3DXEffect* gShadersService::Find(std::string name)
{
	std::map<std::string,ID3DXEffect*>::iterator shader_iterator;
	shader_iterator = this->_shadersContainer.find(name);
	if(shader_iterator != this->_shadersContainer.end())
		return shader_iterator->second;
	else
		return NULL;
}