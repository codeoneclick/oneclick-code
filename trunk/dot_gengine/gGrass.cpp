#include "gGrass.h"

gGrass::gGrass(){
	this->Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	this->Effect = NULL;
	this->is_create = false;

	map_index_i = 0;
	map_index_j = 0;
}

gGrass::~gGrass(){
}

void gGrass::Textures(){
	//this->grass_texture_color =  ;//= grass_texture_color;
	Effect->SetTexture("grassTexture_01",gCore::TexturesService()->Find("grassTexture_01"));
	Effect->SetTexture("grassTexture_02",gCore::TexturesService()->Find("grassTexture_02"));
	Effect->SetTexture("grassTexture_03",gCore::TexturesService()->Find("grassTexture_03"));
	Effect->SetTexture("grassTexture_04",gCore::TexturesService()->Find("grassTexture_04"));
}

int gGrass::Random(int min,int max)
{
	int result = 0;
	srand((unsigned)GetTickCount()*GetTickCount() - 2*GetTickCount() + 1);
	int range = (max - min) + 1;
	result = (int) (min + (rand()*range/(RAND_MAX +1)));
	return result;

}

void gGrass::Create(float **map_heightmap,gMapDecoration **map_tile_mask,int map_index_i,int map_index_j)
{
	this->camera = gCore::Camera();//camera;
	this->light = gCore::Light();//light;
	this->Effect = gCore::ShadersService()->Find("grass_effect");///Effect;

	this->grass_num_vertices = 0;
	this->grass_num_primitives = 0;

	this->position_x.clear();
	this->position_z.clear();

	this->map_index_i = map_index_i;
	this->map_index_j = map_index_j;
	this->heightmap = map_heightmap;//heightmap;

	for(int i =  map_index_i*64; i < (64 + map_index_i*64); ++i)
		for(int j = map_index_j*64; j < (64 +map_index_j*64); ++j)
			if(map_tile_mask[i][j].plantsFlag > 0.0f){
				if(this->heightmap[i][j] < 128.0f) 
					continue;
				this->grass_num_vertices += 8;
				this->grass_num_primitives += 4;
				this->position_x.push_back((float)i);
				this->position_z.push_back((float)j);
				++j;
			}

	if(this->grass_num_vertices == 0) return;
	gVertex* p_vertex_data = NULL;
    short* p_index_data = NULL;

	//DWORD* adjacency = NULL;

	//int size = 8.0f;
	float width = 4.0f;
	float height = 48.0f;
	int grass_height = -1;

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


	D3DXCreateMesh(this->grass_num_primitives,this->grass_num_vertices, D3DXMESH_MANAGED ,gCore::shaderVertexElemets,gDevice::device,&this->mesh);
	int index = 0;
	float angle = 0;
	float angle_offset = 0;
	this->mesh->LockVertexBuffer(D3DLOCK_NOOVERWRITE,(LPVOID*)&p_vertex_data);	
	for(unsigned index0 = 0; index0 < this->position_x.size(); ++index0){
		angle = (float)rand();
		angle_offset = 10;//Random(5,15);
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f + width,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + grass_height,this->position_z[index0]*10.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(0.0f,0.0,1.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		//angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f  + width,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + height + grass_height,this->position_z[index0]*10.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(0.0f,0.0,1.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f  - width,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + grass_height,this->position_z[index0]*10.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(0.0f,0.0,1.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		//angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f  - width,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + height + grass_height,this->position_z[index0]*10.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(0.0f,0.0,1.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		//////////////////////////////////////////////////////////////////////////////
		angle = (float)rand();
		angle_offset = 10;//Random(5,15);
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f ,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + grass_height,this->position_z[index0]*10.0f  + width);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(1.0f,0.0f,0.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f ,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + height + grass_height,this->position_z[index0]*10.0f  + width);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(1.0f,0.0f,0.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f ,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + grass_height,this->position_z[index0]*10.0f  - width);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(1.0f,0.0f,0.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		angle = (float)rand();
		p_vertex_data[index].position = D3DXVECTOR3(this->position_x[index0]*10.0f ,this->heightmap[(int)this->position_x[index0]][(int)this->position_z[index0]] + height + grass_height,this->position_z[index0]*10.0f  - width);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
		p_vertex_data[index].normal  = D3DXVECTOR3(1.0f,0.0f,0.0f);
		p_vertex_data[index].position.x += cos(angle)*angle_offset;
		p_vertex_data[index].position.z += sin(angle)*angle_offset;
		index++;
		//////////////////////////////////////////////////////////////////////////////
	}

	this->mesh->UnlockVertexBuffer();

	index = 0;

	this->mesh->LockIndexBuffer(0,(void**)&p_index_data);
	int a = 0;
	for(unsigned index0 = 0; index0 < this->position_x.size(); ++ index0){
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a--;

		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;

		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a--;

		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
	}
	this->mesh->UnlockIndexBuffer();

	
	
	DWORD* contiguity_buffer;

	contiguity_buffer = NULL;
    contiguity_buffer = new DWORD[this->mesh->GetNumFaces() * 3];
    this->mesh->GenerateAdjacency( 1e-6f, contiguity_buffer ); 

	D3DXComputeNormals(this->mesh,contiguity_buffer);
	//D3DXComputeTangentFrame(this->mesh, 0); 
	//D3DXComputeTangentFrameEx( this->mesh, D3DDECLUSAGE_TEXCOORD, 0, D3DDECLUSAGE_TANGENT, 0, D3DDECLUSAGE_BINORMAL, 0, D3DDECLUSAGE_NORMAL , 0, D3DXTANGENT_CALCULATE_NORMALS, contiguity_buffer, -1.01f,-0.01f, -1.01f, & this->mesh, NULL );
	this->mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,contiguity_buffer,NULL,NULL,NULL);
	delete[] contiguity_buffer;

	this->is_create = true;
}
void gGrass::Update(){
	if(!this->is_create)
		return;
	Effect->SetFloat("timer",(float)GetTickCount()/1000.0f);
	//Effect->SetVector("ambient_color",&this->light->light_ambient_color);
	Effect->SetFloatArray("light_direction",gCore::Light()->light_direction,4);
	Effect->SetFloatArray("camera_position",this->camera->Position,3);
	D3DXMATRIX world_matrix;
    D3DXMatrixIdentity(&world_matrix);
	D3DXMATRIX world_view_projection_matrix = world_matrix*this->camera->view*this->camera->projection;
	Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
}

void gGrass::Render(){
	if(!this->is_create)
		return;
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	gDevice::device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	gDevice::device->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gDevice::device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	gDevice::device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}