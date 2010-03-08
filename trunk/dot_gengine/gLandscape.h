#define FILE_MAP_SIZE 128
#define MAP_SIZE 64
#define NUMBER_OF_ZONES 1

DWORD WINAPI load_map_thread(LPVOID map_data);


class gLandscape
{
private :
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	LPDIRECT3DINDEXBUFFER9 index_buffer;
	
	IDirect3DTexture9* sand_texture_color;
    IDirect3DTexture9* grass_texture_color;
    IDirect3DTexture9* rock_texture_color;
    IDirect3DTexture9* snow_texture_color;
	IDirect3DTexture9* road_texture_color;

	IDirect3DTexture9* sand_texture_normal;
    IDirect3DTexture9* grass_texture_normal;
    IDirect3DTexture9* rock_texture_normal;
    IDirect3DTexture9* snow_texture_normal;
	IDirect3DTexture9* road_texture_normal;

	IDirect3DTexture9* sand_texture_height;
    IDirect3DTexture9* grass_texture_height;
    IDirect3DTexture9* rock_texture_height;
    IDirect3DTexture9* snow_texture_height;
	IDirect3DTexture9* road_texture_height;

	DWORD lastTime;

	ID3DXMesh* Mesh[NUMBER_OF_ZONES];

	//ID3DXPMesh* LOD_Mesh[NUMBER_OF_ZONES];

	ID3DXEffect* Effect;
	
	ID3DXBuffer* adjBuffer;
	DWORD land_num_vertices, land_num_primitives;

	struct struct_map_mask {
		float r;
		float g;
		float b;
	};

	float **heightmap;
	struct_map_mask map_mask[FILE_MAP_SIZE + 1][FILE_MAP_SIZE + 1];
	struct_map_mask road_mask[FILE_MAP_SIZE + 1][FILE_MAP_SIZE + 1];
	
	//int cell_spacing;
	int height_power;

	int last_tile_map_position_x;
	int last_tile_map_position_z;

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scale_matrix;
	D3DXMATRIX world_matrix;

public :
	int Id;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 Color;
	D3DXMATRIX matrix;

	gBox* box;

	D3DXVECTOR3 *camera_main_position;

	int LOD_detail;	
	
public :
	gLandscape();
	~gLandscape() ;
	void Create(int id);
	void Render();
	void Update(gCamera *camera,gLight *light);
	float getHeight(float x, float z);
	void morph_land(float power,float point_position_x, float point_position_z);

	void load_map();

	bool is_preload;

	int cell_spacing;

	void Run();

};

gLandscape::gLandscape()
{
	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);

	this->last_tile_map_position_x = -1;
	this->last_tile_map_position_z = -1;

	this->vertex_buffer = NULL;
	this->index_buffer = NULL;

	this->LOD_detail = 0.0f;

	this->Effect = NULL;

	this->is_preload = false;
	
	this->sand_texture_color = NULL;
    this->grass_texture_color = NULL;
    this->rock_texture_color = NULL;
    this->snow_texture_color = NULL;
	this->road_texture_color = NULL;

	lastTime = 0;

	this->sand_texture_normal = NULL;
    this->grass_texture_normal = NULL;
    this->rock_texture_normal = NULL;
    this->snow_texture_normal = NULL;
	this->road_texture_normal = NULL;
	
	this->sand_texture_height = NULL;
    this->grass_texture_height = NULL;
    this->rock_texture_height = NULL;
    this->snow_texture_height = NULL;
	this->road_texture_height = NULL;
	this->Mesh[0] = NULL;
	this->height_power = 1;
	this->cell_spacing = 10;
}

gLandscape::~gLandscape()
{
	if(this->vertex_buffer != NULL){
		this->vertex_buffer->Release();
		this->vertex_buffer = NULL;
	}

	if(this->index_buffer = NULL){
		this->index_buffer->Release();
		this->index_buffer = NULL;
	}
}

void gLandscape::Create(int id)
{
	LPD3DXBUFFER errors = NULL;
	HRESULT error_result;
	char* error_name;

	this->land_num_vertices = (64 + 1) * (64 + 1);
    this->land_num_primitives = (64 * 64 * 2);

	this->heightmap = new float*[FILE_MAP_SIZE+1];
	for(int i = 0; i < FILE_MAP_SIZE + 1; ++i){
		this->heightmap[i] = new float[FILE_MAP_SIZE+1];
	}
   
    ifstream file;

	file.open("Content\\maps\\map_03.raw",ios::binary);

	for(unsigned y = 0;y < (FILE_MAP_SIZE + 1);++y)
	{
		for(unsigned x = 0;x < (FILE_MAP_SIZE + 1);++x)
		 {
			heightmap[x][y] = file.get();
		 }
	}

	file.close();

	file.open("Content\\maps\\map_03_mask.raw",ios::binary);
	for(unsigned y = 0;y < (FILE_MAP_SIZE + 1);++y)
	{
		for(unsigned x = 0;x < (FILE_MAP_SIZE + 1);++x)
		 {
			map_mask[x][y].r = file.get() / 255.0f;
			map_mask[x][y].g = file.get() / 255.0f;
			map_mask[x][y].b = file.get() / 255.0f;
		 }
	}

	file.close();

	file.open("Content\\maps\\map_01_road.raw",ios::binary);
	for(unsigned y = 0;y < (FILE_MAP_SIZE + 1);++y)
	{
		for(unsigned x = 0;x < (FILE_MAP_SIZE + 1);++x)
		 {
			road_mask[x][y].r = file.get() / 255.0f;
			road_mask[x][y].g = file.get() / 255.0f;
			road_mask[x][y].b = file.get() / 255.0f;
		 }
	}

	file.close();

	/*D3DXCreateTextureFromFile(Device, "Content\\textures\\scrubdirtcanyon01.dds", &sand_texture_color);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\grass.dds", &grass_texture_color);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\rockwasteland04.dds", &rock_texture_color);
	//D3DXCreateTextureFromFile(Device, "Content\\textures\\snow.dds", &snow_texture_color);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\asphaltwasteland02.dds", &road_texture_color);

	D3DXCreateTextureFromFile(Device, "Content\\textures\\scrubdirtcanyon01_n.dds", &sand_texture_normal);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\grass_normal.dds", &grass_texture_normal);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\rockwasteland04_n.dds", &rock_texture_normal);
	//D3DXCreateTextureFromFile(Device, "Content\\textures\\snow_normal.dds", &snow_texture_normal);
	D3DXCreateTextureFromFile(Device, "Content\\textures\\asphaltwasteland02_n.dds", &road_texture_normal);


	error_result = D3DXCreateEffectFromFile(Device, "Content\\shaders\\ground.fx", NULL, NULL, 0, NULL, &Effect, &errors);

	if(FAILED( error_result ))
        error_name = ( char* )errors->GetBufferPointer();

	Effect->SetTechnique("ground");
	Effect->SetTexture("textureColorLayer0",sand_texture_color);
    Effect->SetTexture("textureColorLayer1",grass_texture_color);
    Effect->SetTexture("textureColorLayer2",rock_texture_color);
    //Effect->SetTexture("textureColorLayer3",snow_texture_color);
	Effect->SetTexture("textureColorLayer4",road_texture_color);

	Effect->SetTexture("textureNormalLayer0",sand_texture_normal);
    Effect->SetTexture("textureNormalLayer1",grass_texture_normal);
    Effect->SetTexture("textureNormalLayer2",rock_texture_normal);
    //Effect->SetTexture("textureNormalLayer3",snow_texture_normal);
	Effect->SetTexture("textureNormalLayer4",road_texture_normal);*/

	//CreateThread(NULL,NULL,load_map_thread,this,NULL,NULL);
}

DWORD WINAPI load_map_thread(LPVOID map_data){
	gLandscape *map = (gLandscape*)map_data;
	for(;;)
		map->load_map();
	return 0;
}

float gLandscape::getHeight(float x, float z)
{
	x = abs(x / this->cell_spacing);
	z = abs(z / this->cell_spacing);

	int leftX = x;
	int outZ = z;

	float fracX = x - leftX;
	float fracZ = z - outZ;
	
	float h11 = this->heightmap[leftX][outZ];
	float h12 = this->heightmap[leftX][outZ +1];
	float h21 = this->heightmap[leftX + 1][outZ];
	float h22 = this->heightmap[leftX + 1][outZ + 1];

    float height;

    if( fracX > fracZ )
	{
		height = h11 + (h22 - h21)*fracZ + (h21 - h11)*fracX;
	}
	else
	{
		height = h11 + (h22 - h12)*fracX + (h12 - h11)*fracZ;
	}

	return (1 - fracX) * ((1 - fracZ) * h11 + fracZ * h12) + fracX * ((1 - fracZ) * h21 + fracZ * h22) + this->Position.y;
}

void gLandscape::morph_land(float power, float point_position_x, float point_position_z){
	  float index_x = point_position_x;
	  float index_z = point_position_z;
	  gLandVertex* p_vertex_data = NULL;
	  Mesh[0]->LockVertexBuffer(D3DLOCK_NOOVERWRITE,(LPVOID*)&p_vertex_data);
	  for(unsigned y = 0;y < (64 + 1);++y)
	  {
			for(unsigned x = 0;x < (64 + 1);++x)
			{
				//if((p_vertex_data[x + y * (64 + 1)].position.x > index_x - 25.0f) && (p_vertex_data[x + y * (64 + 1)].position.x < index_x + 25.0f))
				//if((p_vertex_data[x + y * (64 + 1)].position.z > index_z - 25.0f) && (p_vertex_data[x + y * (64 + 1)].position.z < index_z + 25.0f)){
					float radius =  (float)sqrt(pow((p_vertex_data[x + y * (64 + 1)].position.x - index_x), 2) /*+ pow((End.y - this->y), 2)*/ + pow((p_vertex_data[x + y * (64 + 1)].position.z - index_z), 2));//(float)sqrt(p_vertex_data[x + y * (64 + 1)].position.x * index_x + p_vertex_data[x + y * (64 + 1)].position.z * index_z);
					if(radius < this->cell_spacing) radius = this->cell_spacing;
					if(radius < 25.0f) p_vertex_data[x + y * (64 + 1)].position.y += power/radius;
					this->heightmap[(int)(p_vertex_data[x + y * (64 + 1)].position.x/this->cell_spacing)][(int)(p_vertex_data[x + y * (64 + 1)].position.z/this->cell_spacing)] = p_vertex_data[x + y * (64 + 1)].position.y;
				//}
			}
	  }
	  Mesh[0]->UnlockVertexBuffer();
}

void gLandscape::load_map(){
    int index_first = (int) this->camera_main_position->x / (64 * this->cell_spacing);
	int index_second = (int) this->camera_main_position->z / (64 * this->cell_spacing);

	if((this->last_tile_map_position_x != index_first) ||  (this->last_tile_map_position_z != index_second)){
	this->is_preload = false;
	LPD3DXBUFFER errors = NULL;
	HRESULT error_result;
	char* error_name;

	float uCoordIncrementSize = 1.0f / 64.0f;
    float vCoordIncrementSize = 1.0f / 64.0f;

	D3DVERTEXELEMENT9 shader_declaration[] =
	{
	    {0, sizeof( float ) * 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	    {0, sizeof( float ) * 3, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, sizeof( float ) * 6, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	    {0, sizeof( float ) * 8, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
        {0, sizeof( float ) * 11, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		{0, sizeof( float ) * 14, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, sizeof( float ) * 18, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
	    D3DDECL_END()
	};

	int index = 0;

	DWORD* adjacency = NULL;

	this->last_tile_map_position_x = index_first;
	this->last_tile_map_position_z = index_second;

	//for(int index_first = 0; index_first < ((int)sqrt((float)NUMBER_OF_ZONES)); index_first++)
	//for(int index_second = 0; index_second < ((int)sqrt((float)NUMBER_OF_ZONES)); index_second++){

	gLandVertex* p_vertex_data = NULL;
    short* p_index_data = NULL;

	D3DXCreateMesh(this->land_num_primitives,this->land_num_vertices,0,shader_declaration,Device,&this->Mesh[index]);

	this->Mesh[index]->LockVertexBuffer(D3DLOCK_DISCARD,(LPVOID*)&p_vertex_data);

	int index_j = 0;
	for(int y = index_second*64;y < (64 + index_second*64 + 1);++y)
	{
		int index_i = 0;
		for(unsigned x = index_first*64;x < (64 + index_first*64 + 1);++x)
		{
			p_vertex_data[index_i + index_j * (64 + 1)].position.x = (float)x*this->cell_spacing;
			//float h = 10.0 * sin(x/24.0) + 7.0 * cos((y-50.0)/18.0);
           // p_vertex_data[x + y * (LAND_SIZE_X + 1)].y = h;
			p_vertex_data[index_i + index_j * (64 + 1)].position.y = (float)heightmap[x][y] / this->height_power;
			p_vertex_data[index_i + index_j * (64 + 1)].position.z = (float)y*this->cell_spacing;

			p_vertex_data[index_i + index_j * (64 + 1)].texture.x = x*uCoordIncrementSize*16;
			p_vertex_data[index_i + index_j * (64 + 1)].texture.y = y*vCoordIncrementSize*16;

			p_vertex_data[index_i + index_j * (64 + 1)].layer_1.x = road_mask[x][y].r;
			p_vertex_data[index_i + index_j * (64 + 1)].layer_1.y = 0.0f;
			p_vertex_data[index_i + index_j * (64 + 1)].layer_1.z = 0.0f;
			
			if(road_mask[x][y].r >= 0.8f){
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.y  = map_mask[x][y].r/8.0f;
		    	p_vertex_data[index_i + index_j * (64 + 1)].layer_0.z  = map_mask[x][y].g/8.0f;
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.x  = map_mask[x][y].b/8.0f;
			} else if(road_mask[x][y].r >= 0.5f && road_mask[x][y].r < 0.8f){
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.y  = map_mask[x][y].r/2.0f;
		    	p_vertex_data[index_i + index_j * (64 + 1)].layer_0.z  = map_mask[x][y].g/2.0f;
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.x  = map_mask[x][y].b/2.0f;
			}else {
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.y  = map_mask[x][y].r;
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.z  = map_mask[x][y].g;
				p_vertex_data[index_i + index_j * (64 + 1)].layer_0.x  = map_mask[x][y].b;
			}
			index_i++;
		}
		index_j++;
    }
	this->Mesh[index]->UnlockVertexBuffer();

	this->Mesh[index]->LockIndexBuffer(0,(void**)&p_index_data);
	index_j = 0;
	for(int y = index_second*64;y < (64 + index_second*64);++y)
	{
		int index_i = 0;
		for(unsigned x = index_first*64;x < (64 + index_first*64);++x)
		{
			*p_index_data++ = index_i + index_j * (64 + 1);
			*p_index_data++ = index_i + 1 + index_j * (64 + 1);
			*p_index_data++ = index_i + 1 + (index_j + 1) * (64 + 1);

			*p_index_data++ = index_i + index_j * (64 + 1);
			*p_index_data++ = index_i + 1 + (index_j + 1) * (64 + 1);
		    *p_index_data++ = index_i + (index_j + 1) * (64 + 1);
			index_i++;
	    }
		index_j++;
   }
	this->Mesh[index]->UnlockIndexBuffer();


	
    adjacency = new DWORD[ Mesh[index]->GetNumFaces() * 3 ];
    Mesh[index]->GenerateAdjacency( 1e-6f, adjacency ); 
    //Mesh[index]->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_STRIPREORDER, adjacency, NULL, NULL, NULL );
    //ID3DXMesh* temp_mesh;
    D3DXComputeTangentFrameEx(Mesh[index], D3DDECLUSAGE_TEXCOORD, 0, D3DDECLUSAGE_TANGENT, 0,D3DDECLUSAGE_BINORMAL, 0,D3DDECLUSAGE_NORMAL, 0,D3DXTANGENT_CALCULATE_NORMALS | D3DXTANGENT_GENERATE_IN_PLACE, adjacency, -1.01f,-0.01f, -1.01f, &Mesh[index], NULL );
	//Mesh[index]->Release();
    //Mesh[index] = temp_mesh;

	

	//error_result = D3DXGeneratePMesh(Mesh[index], adjacency, 0, 0, 1, D3DXMESHSIMP_FACE, &LOD_Mesh[index]);
	//if(FAILED( error_result ))
   //     error_name = ( char* )errors->GetBufferPointer();

	delete[] adjacency;
	adjacency = NULL;

	//DWORD maxFaces = LOD_Mesh[index]->GetMaxFaces();
	//LOD_Mesh[index]->SetNumFaces(maxFaces);

	p_vertex_data = NULL;
	p_index_data = NULL;
	
	index++;
	this->is_preload = true;
	}
	
}


void gLandscape::Update(gCamera *camera,gLight *light)
{
	//int numFaces = LOD_Mesh[0]->GetNumFaces();
	//if( ::GetAsyncKeyState('Z') & 0x8000f )
	//	LOD_Mesh[0]->SetNumFaces(numFaces - 10);
	//if( ::GetAsyncKeyState('X') & 0x8000f )
	//	LOD_Mesh[0]->SetNumFaces(numFaces + 10);
	////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	if(this->is_preload){
	D3DXMatrixTranslation(&translation_matrix, this->Position.x,this->Position.y,this->Position.z);
	D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	D3DXMatrixScaling(&scale_matrix,this->Scale.x,this->Scale.y,this->Scale.z);

	rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
	this->matrix = scale_matrix*rotation_matrix*translation_matrix;
	//Device->SetTransform(D3DTS_WORLD, &this->matrix);

	D3DXMatrixIdentity(&world_matrix);
	D3DXMATRIX world_view_projection_matrix = world_matrix*camera->view*camera->projection;
	D3DXMatrixTranspose(&world_view_projection_matrix,&world_view_projection_matrix);
	Effect->SetMatrix("matrixWorldView", &world_matrix);
	Effect->SetFloat("fTime",(float)GetTickCount()/1000.0f);
	Effect->SetMatrix("matrixWorldViewProjection", &world_view_projection_matrix);
	Effect->SetVector("lightPosition", &light->light_position/*D3DXVECTOR4(512.0f,256.0f,256.0f,0.0f)*/);/*light->light_position*/
	Effect->SetVector("cameraPosition", &D3DXVECTOR4(camera->Position.x,camera->Position.y,camera->Position.z,1.0f ));
	Effect->SetVector("light_ambient_color",&light->light_ambient_color);
	Effect->SetVector("camera_target",&D3DXVECTOR4(camera->Target,1.0f));

	}
}

void gLandscape::Render()
{
	if(this->is_preload){
	 Effect->Begin(NULL, 0);
     Effect->BeginPass(0);
     this->Mesh[0]->DrawSubset(NULL);
	 scene_num_faces +=  this->Mesh[0]->GetNumFaces();
     Effect->EndPass();
     Effect->End();
	}
}