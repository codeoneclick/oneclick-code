#pragma once
class gPanel
{
private :
	//LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	//LPDIRECT3DINDEXBUFFER9 index_buffer;

    IDirect3DTexture9* shader_texture;
	IDirect3DTexture9* main_texture;
	IDirect3DTexture9* on_mouse_texture;
	IDirect3DTexture9* on_press_texture;
	IDirect3DTexture9* disable_texture;
	
	IDirect3DTexture9* text_texture;

	D3DXVECTOR4 shader_color;
	D3DXVECTOR4 main_color;
	D3DXVECTOR4 on_mouse_color;
	D3DXVECTOR4 on_press_color;
	D3DXVECTOR4 disable_color;

	ID3DXMesh* mesh;
	ID3DXMesh* text;

	gCamera *camera;
	
	std::string command;

	bool is_select;
	bool is_pick;
	bool is_camera_orientation;
	float rotate_angle;
	float rotate_speed;

	gLight *light;

	ID3DXEffect* Effect;

	D3DXMATRIX translation_matrix;
	D3DXMATRIX rotation_x_matrix;
	D3DXMATRIX rotation_y_matrix;
	D3DXMATRIX rotation_z_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX scale_matrix;
	D3DXMATRIX pick_matrix;

public :
	int Id;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;
	D3DXMATRIX matrix;

	std::vector<gPanel*> Childs;

	gPanel *Parent;

	bool Visible;

	D3DXVECTOR3 Position;

public :
	gPanel();
	~gPanel() ;
	void Create(ID3DXEffect* Effect,gCamera *camera,gLight *light);
	void Render();
	void Update();
	void SetTextures(IDirect3DTexture9* main_texture,IDirect3DTexture9* on_mouse_texture, IDirect3DTexture9* on_press_texture, IDirect3DTexture9* disable_texture);
	void SetColors(D3DXVECTOR4 main_color,D3DXVECTOR4 on_mouse_color,D3DXVECTOR4 on_press_color,D3DXVECTOR4 disable_color);
	void SetTextTexture(IDirect3DTexture9* text_texture);
	//void Textures(IDirect3DTexture9* panel_texture_color,IDirect3DTexture9* header_texture_color);
	inline bool IsPick(){ return this->is_pick;}
	void Pick();
	inline void SetCommand(std::string command) { this->command = command; }
	inline std::string GetCommand() { return this->command; }
	inline bool IsSelect() { return this->is_select; }
	inline void Select(bool flag) { this->is_select = flag; }
	//inline void SetBlinkColor(D3DXVECTOR4 color){this->color = color;}
	inline void CameraOrientationEnable(bool flag) { this->is_camera_orientation = flag; }
	inline void SetRotateAngle(float speed) { this->rotate_speed = speed;}

	void SetEventTexture(GUITextureFlags flag);
	void SetEventColor(GUIColorFlags flag);

	void SetText(std::string text);
};



gPanel::gPanel()
{
	this->Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	this->Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//this->fake_position = D3DXVECTOR3(0.0f,0.0f,0.0f);

	shader_texture = NULL;
	main_texture = NULL;
	on_mouse_texture = NULL;
	on_press_texture = NULL;
	disable_texture = NULL;
	text_texture = NULL;

	shader_color = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	main_color = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	on_mouse_color = D3DXVECTOR4(0.0f,0.0f,0.5f,1.0f);
	on_press_color = D3DXVECTOR4(0.0f,0.5f,0.0f,1.0f);
	disable_color = D3DXVECTOR4(0.8f,0.8f,0.8f,1.0f);

	mesh = NULL;
	text = NULL;

	//this->color = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);

	this->Parent = NULL;

	//this->Mesh_text = NULL;

	this->rotate_angle = 0.0f;

	this->rotate_speed = 0.0f;

	this->is_camera_orientation = true;

	this->Visible = true;

	this->command = "";

	//this->temp_angle = -15.0f;

	//this->Mesh_header = NULL;

	//this->Mesh_panel = NULL;

	this->is_select = false;

	this->is_pick = false;
	
	this->Effect = NULL;

	//this->vertex_buffer = NULL;
	//this->index_buffer = NULL;
}

gPanel::~gPanel()
{
	for(int index = 0; index < this->Childs.size(); ++index){
		if(this->Childs[index] != NULL)
			delete this->Childs[index];
	}
	this->Childs.clear();


	/*if(this->vertex_buffer != NULL){
		this->vertex_buffer->Release();
		this->vertex_buffer = NULL;
	}

	if(this->index_buffer = NULL){
		this->index_buffer->Release();
		this->index_buffer = NULL;
	}*/
}

void gPanel::SetTextTexture(IDirect3DTexture9* text_texture){
	this->text_texture = text_texture;
}

void gPanel::SetTextures(IDirect3DTexture9* main_texture,IDirect3DTexture9* on_mouse_texture, IDirect3DTexture9* on_press_texture, IDirect3DTexture9* disable_texture){
	this->main_texture = main_texture;
	this->on_mouse_texture = on_mouse_texture;
	this->on_press_texture = on_press_texture;
	this->disable_texture = disable_texture;
}

void gPanel::SetColors(D3DXVECTOR4 main_color,D3DXVECTOR4 on_mouse_color,D3DXVECTOR4 on_press_color,D3DXVECTOR4 disable_color){
	this->main_color = main_color;
	this->on_mouse_color = on_mouse_color;
	this->on_press_color = on_press_color;
	this->disable_color = disable_color;
}

void gPanel::SetEventTexture(GUITextureFlags flag){
	switch(flag){
		case T_MAIN:
			this->shader_texture = this->main_texture;
			break;
		case T_ON_MOUSE:
			if(this->on_mouse_texture != NULL)
				this->shader_texture = this->on_mouse_texture;
			else
				this->shader_texture = this->main_texture;
			break;
		case T_ON_PRESS:
			if(this->on_press_texture != NULL)
				this->shader_texture = this->on_press_texture;
			else
				this->shader_texture = this->main_texture;
			break;
		case T_DISABLE:
			if(this->disable_texture != NULL)
				this->shader_texture = this->disable_texture;
			else
				this->shader_texture = this->main_texture;
			break;
	}
}

void gPanel::SetEventColor(GUIColorFlags flag){
	switch(flag){
		case C_MAIN:
			this->shader_color = this->main_color;
			break;
		case C_ON_MOUSE:
				this->shader_color = this->on_mouse_color;
			break;
		case C_ON_PRESS:
				this->shader_color = this->on_press_color;
			break;
		case C_DISABLE:
				this->shader_color = this->disable_color;
			break;
	}
}

//void gPanel::Textures(IDirect3DTexture9* panel_texture_color,IDirect3DTexture9* header_texture_color){
//	this->panel_texture_color = panel_texture_color;
//	this->header_texture_color = header_texture_color;
//}

void gPanel::Create(ID3DXEffect* Effect,gCamera *camera,gLight *light)
{
	this->camera = camera;
	this->light = light;
	this->Effect = Effect;

	D3DVERTEXELEMENT9 shader_declaration[] =
	{
	    {0, sizeof( float ) * 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, sizeof( float ) * 4, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
        {0, sizeof( float ) * 7, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	    D3DDECL_END()
	};

	//int size = 16.0f;

	//gGUIVertex* p_vertex_data = NULL;
    //short* p_index_data = NULL;

	//int index = 0;



	/*D3DXCreateMesh(2,4, 0,shader_declaration,Device,&this->Mesh_panel);
	this->Mesh_panel->LockVertexBuffer(0,(LPVOID*)&p_vertex_data);	
		p_vertex_data[index].position = D3DXVECTOR4(0.0f + size,0.0f,0.0f,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f + size,0.0f + size,0.0f ,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f  - size,0.0f,0.0f,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f  - size,0.0f + size,0.0f ,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
		index++;
	this->Mesh_panel->UnlockVertexBuffer();

	index = 0;

	D3DXCreateMesh(2,4, 0,shader_declaration,Device,&this->Mesh_header);
	this->Mesh_header->LockVertexBuffer(0,(LPVOID*)&p_vertex_data);	
		p_vertex_data[index].position = D3DXVECTOR4(0.0f + size,0.0f,0.0f,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f + size,0.0f + size/8.0f,0.0f ,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f  - size,0.0f,0.0f,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR4(0.0f  - size,0.0f + size/8.0f,0.0f ,1.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
		index++;
	this->Mesh_header->UnlockVertexBuffer();
	
	index = 0;

	this->Mesh_panel->LockIndexBuffer(0,(void**)&p_index_data);
	
	int a = 0;

	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a--;

	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;

	this->Mesh_panel->UnlockIndexBuffer();


	index = 0;

	this->Mesh_header->LockIndexBuffer(0,(void**)&p_index_data);
	
	a = 0;

	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a--;

	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;
	p_index_data[index++] = a; a++;

	this->Mesh_header->UnlockIndexBuffer();*/

	D3DXLoadMeshFromX("Content\\models\\GUI_sphere.x",D3DXMESH_SYSTEMMEM,Device, NULL, NULL, NULL, NULL, &this->mesh );

	//D3DXComputeNormals(this->Mesh_panel,NULL);
	//D3DXComputeNormals(this->Mesh_header,NULL);
}

void gPanel::SetText(std::string text){
	if(this->text != NULL){
		this->text->Release();
		this->text = NULL;
	}

	HDC hdc;
    HFONT font;
    hdc=CreateCompatibleDC(NULL);
    font=CreateFont(0,0, 0,0,FW_BOLD,false,false, false, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE,"Tahoma");
    SelectObject(hdc, font);
	D3DXCreateText(Device,hdc, text.c_str(), 0.0f,  0.0f,   &this->text,  NULL,  NULL);         
}


void gPanel::Pick(){

	this->is_pick = false;
	if(!Visible)
		return;
    D3DXVECTOR3 ray_direction;
    D3DXVECTOR3 ray_position;
	D3DVIEWPORT9 viewport;
    Device->GetViewport(&viewport);

	
	D3DXMATRIX matrix_projection = this->camera->projection;
	D3DXMATRIX matrix_view = this->camera->view;
	D3DXMATRIX matrix_world_view = this->pick_matrix * matrix_view;
    D3DXMATRIX matrix_inverse;
    D3DXMatrixInverse(&matrix_inverse, NULL, &matrix_world_view);

    POINT cursor_position;
    GetCursorPos(&cursor_position);
    ScreenToClient(hwnd, &cursor_position);


    D3DXVECTOR3 vector;
    vector.x =  ( ( ( 2.0f * cursor_position.x ) / viewport.Width  ) - 1 ) / matrix_projection._11;
	vector.y = -( ( ( 2.0f * cursor_position.y ) / viewport.Height ) - 1 ) / matrix_projection._22;
    vector.z =  1.0f;

    ray_direction.x  = vector.x*matrix_inverse._11 + vector.y*matrix_inverse._21 + vector.z*matrix_inverse._31;
    ray_direction.y  = vector.x*matrix_inverse._12 + vector.y*matrix_inverse._22 + vector.z*matrix_inverse._32;
    ray_direction.z  = vector.x*matrix_inverse._13 + vector.y*matrix_inverse._23 + vector.z*matrix_inverse._33;
    ray_position.x = matrix_inverse._41;
    ray_position.y = matrix_inverse._42;
    ray_position.z = matrix_inverse._43;

	BOOL HIT = FALSE;

	D3DXIntersect(this->mesh, &ray_position, &ray_direction, &HIT, NULL, NULL, NULL, NULL, NULL, NULL);

	if(HIT) 
		this->is_pick = true; 
	else 
		this->is_pick = false;
}


void gPanel::Update(){

	if(!Visible)
		return;

	//D3DXVECTOR2 distance_position;
	//distance_position.x = this->camera->Target.x +cos(-(this->camera->Rotation.y) + 1.57)*(-128.0f);
	//distance_position.y = this->camera->Target.z +sin(-(this->camera->Rotation.y) + 1.57)*(-128.0f);
	//if(this->Position.x >=0){
	//	this->Rotation.y = this->camera->Rotation.y - 90.0f;
	//	this->fake_position.x = distance_position.x +cos(-(this->Rotation.y) + 1.57)*(this->Position.x);
	//    this->fake_position.z = distance_position.y +sin(-(this->Rotation.y) + 1.57)*(this->Position.x);
	//}
	//else{
	//	this->Rotation.y = this->camera->Rotation.y + 90.0f;
	//	this->fake_position.x = distance_position.x +cos(-(this->Rotation.y) + 1.57)*(-this->Position.x);
	//    this->fake_position.z = distance_position.y +sin(-(this->Rotation.y) + 1.57)*(-this->Position.x);
	//}

	//this->fake_position.x = distance_position.x +cos(-(this->Rotation.y) + 1.57)*(this->Position.x);
	//this->fake_position.z = distance_position.y +sin(-(this->Rotation.y) + 1.57)*(this->Position.x);
	//this->fake_position.y = this->camera->Target.y + this->Position.y;

	if(this->shader_texture == NULL)
		this->shader_texture = this->main_texture;
	
	this->Rotation.y = this->camera->Rotation.y;

	//this->fake_position.x = this->camera->Target.x + this->Position.x;
	//this->fake_position.z = this->camera->Target.z + this->Position.z;
	//this->fake_position.y = this->camera->Target.y + this->Position.y;

	this->rotate_angle += this->rotate_speed;

	//this->temp_angle += 1.0f;
}

void gPanel::Render()
{
	if(!Visible)
		return;
	
	//Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	//Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	//Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//Device->SetRenderState(D3DRS_ALPHAREF, (DWORD)128);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	//Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	D3DXMATRIX world_matrix;
	D3DXMatrixTranslation(&translation_matrix,this->Position.x + this->camera->LookAt.x,this->Position.y + this->camera->LookAt.y,this->Position.z + this->camera->LookAt.z);
	D3DXMatrixRotationX(&rotation_x_matrix,this->Rotation.x);
	D3DXMatrixRotationZ(&rotation_z_matrix,this->Rotation.z);
	if(this->is_camera_orientation)
		D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y);
	else
		D3DXMatrixRotationY(&rotation_y_matrix,this->rotate_angle);
	D3DXMatrixScaling(&scale_matrix,this->Scale.x*0.5f,this->Scale.y*0.5f,this->Scale.z*0.5f);
	rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
	world_matrix = scale_matrix*rotation_matrix*translation_matrix;
	this->pick_matrix = world_matrix;
	//this->matrix_picking = world_matrix;
	D3DXMATRIX world_view_projection_matrix = world_matrix*this->camera->view*this->camera->projection;
	Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
	Effect->SetTexture("texture_color",this->shader_texture);
	Effect->SetFloatArray("blink_color",this->shader_color,4);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();

	if(this->text != NULL){
		D3DXVECTOR2 distance_position;
		//distance_position.x = this->Position.x +cos(-(this->Rotation.y + 90.0f) + 1.57)*(32.0f);
		//distance_position.y = this->Position.x +sin(-(this->Rotation.y + 90.0f) + 1.57)*(32.0f);
		Device->SetRenderState(D3DRS_ZENABLE, FALSE);
		D3DXMatrixTranslation(&translation_matrix,this->Position.x + this->camera->LookAt.x,this->Position.y + this->camera->LookAt.y - 10.0f,this->Position.z + this->camera->LookAt.z);
		D3DXMatrixRotationY(&rotation_y_matrix,this->Rotation.y + 3.14f);
		D3DXMatrixRotationX(&rotation_x_matrix,0.0f);
		D3DXMatrixRotationZ(&rotation_z_matrix,0.0f);
		rotation_matrix = rotation_x_matrix*rotation_y_matrix*rotation_z_matrix;
		D3DXMatrixScaling(&scale_matrix,this->Scale.x*4.0f,this->Scale.y*4.0f,this->Scale.z*4.0f);
		world_matrix = scale_matrix*rotation_matrix*translation_matrix;
		world_view_projection_matrix = world_matrix*this->camera->view*this->camera->projection;
		Effect->SetTexture("texture_color",this->text_texture);
		Effect->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
		Effect->Begin(NULL,NULL);
		Effect->BeginPass(NULL);
		this->text->DrawSubset(NULL);
		Effect->EndPass();
		Effect->End();
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	}
	//Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
}