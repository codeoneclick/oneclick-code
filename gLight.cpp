#include "gLight.h"

gLight::gLight(){
	this->light_position = D3DXVECTOR3(-256.0f, -256.0f, -256.0f);
	this->light_rotation = 0.0f;
	this->light_ambient_color = D3DXVECTOR4(0.12f, 0.12f, 0.12f, 0.0f);
	angle = 0.0f;

	light_direction = D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f);
	//D3DXCreateSphere(Device,10.0f,8,8,&this->Mesh,NULL);
	//LPD3DXBUFFER errors = NULL;
	//HRESULT error_result;
	//char* error_name;
	//error_result = D3DXCreateEffectFromFile(Device, "Content\\shaders\\light.fx", NULL, NULL, 0, NULL, &Effect, &errors);
	//if(FAILED( error_result ))
   //     error_name = ( char* )errors->GetBufferPointer();
	//int i = 0;
}

void gLight::Update(){
	angle+= 0.05f;
	Position.y = 2000.0f;
	Position.x = 2000.0f;//cos(angle)*2560.0f*1.4f;
	Position.z = 2000.0f;//sin(angle)*2560.0f*1.4f;
	//light_rotation += light_power;
	light_position.x = 1000;//camera->Position.x;// + cos(-(light_rotation)*0.0174532925f + 1.57f)*128.0f;
	//light_position.y = 0.0f + sin(-(light_rotation)*0.0174532925f + 1.57f)*1024.0f;
	light_position.z = 1000;//camera->Position.z;// + sin(-(light_rotation)*0.0174532925f + 1.57f)*128.0f;//camera->Position.z;
	light_position.y = 1000;//camera->Position.y + 1000;//+ sin(light_rotation+=0.01f)*1024;
	//light_rotation += 0.5f;
	//D3DXMatrixScaling(&matrix_scale,0.2f,0.2f,0.2f);
	//D3DXMatrixTranslation(&translation_matrix, light_position.x,light_position.y,light_position.z);
	//matrix_world = matrix_scale*translation_matrix;
	//D3DXMATRIX world_view_projection_matrix = matrix_world*camera->view*camera->projection;
	//Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
	//Device->SetTransform(D3DTS_WORLD, &this->matrix_world);
}

void gLight::Render(){
	//Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//Effect->Begin(NULL,NULL);
    //Effect->BeginPass(NULL);
    //Mesh->DrawSubset(NULL);
    //Effect->EndPass();
    //Effect->End();
	//Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
}