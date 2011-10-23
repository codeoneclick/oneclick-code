#include "gWater.h"
#include "gCore.h"

gWater::gWater(){
	this->Effect = NULL;	
	this->Mesh = NULL;
	this->D3D_Result = NULL;
}

gWater::~gWater(){
}

void gWater::Create(int map_index_i,int map_index_j){
	
	this->water_num_vertices = 4;
    this->water_num_primitives = 2;

	LPD3DXBUFFER errors = NULL;

	char* error_name = NULL;

	this->Effect = gCore::ShadersService()->Find("water_effect");
	this->camera = gCore::Camera();
	this->light =  gCore::Light();
   
	gVertex* p_vertex_data = NULL;
    short* p_index_data = NULL;

	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Scale    = D3DXVECTOR3(1.0f,1.0f,1.0f);
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//D3DVERTEXELEMENT9 shader_declaration[] =
	//{
	//    {0, sizeof( float ) * 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	//	{0, sizeof( float ) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	//    D3DDECL_END()
	//};

	/*D3DVERTEXELEMENT9 shader_declaration[] =
{
	{0, 0,   D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, 24,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{0, 32,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	{0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
	{0, 56,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
	{0, 72,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
	D3DDECL_END()
};*/



	D3DXCreateMesh(this->water_num_primitives,this->water_num_vertices,D3DXMESH_MANAGED ,gCore::shaderVertexElemets,gDevice::device,&this->Mesh);


	this->D3D_Result = this->Mesh->LockVertexBuffer(D3DLOCK_NOSYSLOCK,(void**)&p_vertex_data);	

	p_vertex_data[0].position = D3DXVECTOR3(map_index_i*64.0f*10.0f, 128.0f,map_index_j*64.0f*10.0f);
	p_vertex_data[0].texture = D3DXVECTOR2(0.0f,0.0f);
	p_vertex_data[1].position = D3DXVECTOR3(map_index_i*64.0f*10.0f, 128.0f, map_index_j*64.0f*10.0f + 64.0f*10.0f);
	p_vertex_data[1].texture = D3DXVECTOR2(0.0f,1.0f);
	p_vertex_data[2].position = D3DXVECTOR3(map_index_i*64.0f*10.0f + 64.0f*10.0f, 128.0f, map_index_j*64.0f*10.0f);
	p_vertex_data[2].texture = D3DXVECTOR2(1.0f,0.0f);
	p_vertex_data[3].position = D3DXVECTOR3(map_index_i*64.0f*10.0f + 64.0f*10.0f, 128.0f, map_index_j*64.0f*10.0f + 64.0f*10.0f);
	p_vertex_data[3].texture = D3DXVECTOR2(1.0f,1.0f);
	this->Mesh->UnlockVertexBuffer();

	this->Mesh->LockIndexBuffer(D3DLOCK_NOSYSLOCK,(void**)&p_index_data);
	p_index_data[0] = 0;
	p_index_data[1] = 2;
	p_index_data[2] = 1;

	p_index_data[3] = 1;
	p_index_data[4] = 2;
	p_index_data[5] = 3;
	this->Mesh->UnlockIndexBuffer();
}

void gWater::Textures()
{
	Effect->SetTexture("normalMap",gCore::TexturesService()->Find("water_texture_normal"));
}					  

void gWater::Update()
{
	
	//Effect->SetTexture("sky_reflection_texture",gCore::TexturesService()->Find("sky_reflection_texture"));
	Effect->SetTexture("models_reflection_texture",gCore::TexturesService()->Find("models_reflection_texture"));

	D3DXMatrixIdentity(&world_matrix);

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scaling_matrix;

	D3DXMatrixScaling(&scaling_matrix,this->Scale.x,this->Scale.y,this->Scale.z);
	D3DXMatrixTranslation(&translation_matrix, this->Position.x,this->Position.y, this->Position.z);
	D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
	world_matrix = scaling_matrix*rotation_matrix*translation_matrix;
	
	world_view_projection_matrix = world_matrix*this->camera->view*this->camera->projection;

	D3DXMATRIX matrix_scale,matrix_translation,matrix_reflection;
	D3DXMatrixMultiply(&matrix_reflection, &this->camera->view, &this->camera->projection);
	D3DXMatrixScaling(&matrix_scale, 0.5f, 0.5f, 0.5f);
	D3DXMatrixTranslation(&matrix_translation, 0.5f, 0.5f , 0.5f);
	matrix_reflection *= matrix_scale*matrix_translation;
	 
	Effect->SetFloat("timer",(float)GetTickCount()/1000.0f);
	Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
	Effect->SetMatrix("matrix_world", &world_matrix);
	Effect->SetMatrix("matrix_reflection", &matrix_reflection);
	Effect->SetFloatArray("light_direction", gCore::Light()->light_direction,4);
	Effect->SetFloatArray("camera_position",this->camera->Position,3);
}

void gWater::Render(){
	Effect->Begin(NULL,NULL);
    Effect->BeginPass(NULL);
    this->Mesh->DrawSubset(NULL);
    Effect->EndPass();
    Effect->End();
}