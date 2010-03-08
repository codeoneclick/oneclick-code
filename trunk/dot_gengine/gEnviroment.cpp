#include "gEnviroment.h"

gMapsService* gEnviroment::_mapsService = NULL;
bool gEnviroment::_mapsServiceSingleFlag = false;

gMapsService* gEnviroment::MapsService()
{
    if(!_mapsServiceSingleFlag)
    {
        _mapsService = new gMapsService();
		_thread = CreateThread(NULL,NULL,mapsLoadThread,NULL,NULL,NULL);
		SetThreadPriority(_thread,THREAD_PRIORITY_NORMAL);
        _mapsServiceSingleFlag = true;
        return _mapsService;
    }
    else
    {
        return _mapsService;
    }
}

/*gMeshService* gEnviroment::_meshService = NULL;
bool gEnviroment::_meshServiceSingleFlag = false;

gMeshService* gEnviroment::MeshService()
{
    if(!_meshServiceSingleFlag)
    {
        _meshService = new gMeshService();
        _meshServiceSingleFlag = true;
        return _meshService;
    }
    else
    {
        return _meshService;
    }
}*/

LPDIRECT3DTEXTURE9 gEnviroment::_models_reflection_texture = NULL;
bool gEnviroment::_models_reflection_textureSingleFlag = false;

LPDIRECT3DTEXTURE9 gEnviroment::_ModelsReflectionTexture()
{
    if(!_models_reflection_textureSingleFlag)
    {
		gDevice::device->CreateTexture(REFLECTION_SIZE, REFLECTION_SIZE, 1, D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_models_reflection_texture, NULL );
        _models_reflection_textureSingleFlag = true;
        return _models_reflection_texture;
    }
    else
    {
        return _models_reflection_texture;
    }
}

/////////////////////////////////////////////////////////////

LPDIRECT3DSURFACE9 gEnviroment::_models_reflection_surface = NULL;
bool gEnviroment::_models_reflection_surfaceSingleFlag = false;

LPDIRECT3DSURFACE9 gEnviroment::_ModelsReflectionSurface()
{
    if(!_models_reflection_surfaceSingleFlag)
    {
		gDevice::device->CreateDepthStencilSurface(REFLECTION_SIZE,REFLECTION_SIZE,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&_models_reflection_surface,NULL);
        _models_reflection_surfaceSingleFlag = true;
        return _models_reflection_surface;
    }
    else
    {
        return _models_reflection_surface;
    }
}

gLevel* gEnviroment::_levelContainer = NULL;
bool    gEnviroment::_levelContainerSingleFlag = false;

gLevel* gEnviroment::LevelContainer()
{
    if(!_levelContainerSingleFlag)
    {
        _levelContainer = new gLevel();
        _levelContainerSingleFlag = true;
        return _levelContainer;
    }
    else
    {
        return _levelContainer;
    }
}

gSkyDome* gEnviroment::_sky = NULL;
bool  gEnviroment::_skySingleFlag = false;

gSkyDome* gEnviroment::Sky()
{
    if(!_skySingleFlag)
    {
        _sky = new gSkyDome();
		_sky->Create(0,NULL,NULL);
        _skySingleFlag = true;
        return _sky;
    }
    else
    {
        return _sky;
    }
}

void gEnviroment::Reflection()
{

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
	};

	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl;
	gDevice::device->CreateVertexDeclaration(shader_declaration,&m_pVertexDecl);*/
	gDevice::device->SetVertexDeclaration(gCore::ShaderDeclaration());

	float reflection_surface_heigh_offset = 1.5f;
	float reflection_surface_height = 128.0f + reflection_surface_heigh_offset;
	//LPDIRECT3DSURFACE9 original_surface = NULL;
	//gDevice::device->GetRenderTarget(0, &original_surface);
	//if (NULL == original_surface)
	//	return;

	D3DXPLANE cut_plane;
	D3DXPlaneFromPoints(&cut_plane,&D3DXVECTOR3(0,reflection_surface_height,0),&D3DXVECTOR3(0,reflection_surface_height,1),&D3DXVECTOR3(1,reflection_surface_height,0));
	
	gDevice::device->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0);
	
	gCore::EnableRenderToTexture(_ModelsReflectionTexture(),_ModelsReflectionSurface(),REFLECTION_SIZE,REFLECTION_SIZE,D3DFMT_A8R8G8B8,0xFFFFFFFF);
	//gDevice::device->SetRenderTarget(0, gEnviroment::_ModelsReflectionSurface());
	//gDevice::device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//gDevice::device->BeginScene();

	D3DXVECTOR3 temp_camera_position = gCore::Camera()->Position;
	D3DXVECTOR3 temp_camera_target =  gCore::Camera()->LookAt;

	D3DXVECTOR3 camera_position = gCore::Camera()->Position;
	camera_position.y = -camera_position.y + reflection_surface_height*2;
	D3DXVECTOR3 camera_target = gCore::Camera()->LookAt;
	camera_target.y = -camera_target.y + reflection_surface_height*2;

	gCore::Camera()->Position = camera_position;
	gCore::Camera()->LookAt = camera_target;
	gCore::Camera()->Update();

	D3DXVECTOR4 temp_vector = D3DXVECTOR4(cut_plane.a,cut_plane.b,cut_plane.c,cut_plane.d);

	D3DXMATRIX temp_matrix_projection = gCore::Camera()->view*gCore::Camera()->projection;
	D3DXMatrixTranspose(&temp_matrix_projection,&temp_matrix_projection);
	D3DXMatrixInverse(&temp_matrix_projection,NULL,&temp_matrix_projection);
	D3DXVec4Transform(&temp_vector,&temp_vector,&temp_matrix_projection);

	cut_plane.a = temp_vector.x;
	cut_plane.b = temp_vector.y;
	cut_plane.c = temp_vector.z;
	cut_plane.d = temp_vector.w;

	gDevice::device->SetClipPlane(0, cut_plane);

	for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index)
		if(gEnviroment::MapsService()->Maps()[map_index]->GetRenderFlag() != R_UNLOAD ) {   
			gEnviroment::MapsService()->Maps()[map_index]->Update(true);
			gEnviroment::MapsService()->Maps()[map_index]->Render(GROUND);
			gEnviroment::MapsService()->Maps()[map_index]->Render(GRASS);
	}

	gEnviroment::Sky()->Update();
	gEnviroment::Sky()->Render();

	gEnviroment::LevelContainer()->Render("mesh_effect");
   /*std::map<std::string,gMeshStatic*>::iterator meshIterator = gEnviroment::MeshStaticService()->Begin();
   for(;meshIterator != gEnviroment::MeshStaticService()->End();meshIterator++)
   {
		meshIterator->second->Render();
   }*/

	//gDevice::device->EndScene();
   
    gCore::DisableRenderToTexture();
	gDevice::device->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
	
	gCore::Camera()->Position = temp_camera_position;
	gCore::Camera()->LookAt = temp_camera_target;
	gCore::Camera()->Update();

	
	//gDevice::device->SetRenderTarget(0, original_surface);
	//original_surface->Release();

	if( ::GetAsyncKeyState('T') & 0x8000f )
		D3DXSaveTextureToFile("C:\\temp.png",D3DXIFF_PNG,_ModelsReflectionTexture(),NULL);

	gCore::TexturesService()->Insert("models_reflection_texture",_ModelsReflectionTexture());
}

void gEnviroment::Update()
{
	//gEnviroment::Reflection();
	//gEnviroment::ShadowMap();
}

HANDLE gEnviroment::_thread = NULL;

void gEnviroment::_mapsLoadThread()
{
	int point_index_i = 0;
	int point_index_j = 0;

	int map_index_i = 0;
	int map_index_j = 0;

	int last_map_index_i = -1;
	int last_map_index_j = -1;

	unsigned map_index = 0;

	while(true)
	{
		unsigned maps_size = gEnviroment::MapsService()->Maps().size();
		Sleep(100);
		
		if(maps_size < NUMBER_OF_MAPS)
			continue;

		point_index_i = gCore::Camera()->Position.x / (64*10);
		point_index_j = gCore::Camera()->Position.z / (64*10);

		if((last_map_index_i == point_index_i) && (last_map_index_j == point_index_j))
			continue;

		for(map_index = 0; map_index < maps_size; ++map_index)
		{
			for(int currentIndex_x = - 3; currentIndex_x <= 3; currentIndex_x++)
				for(int currentIndex_z = - 3; currentIndex_z <= 3; currentIndex_z++)
				{
					if((currentIndex_x < 0) || (currentIndex_z < 0) || (currentIndex_z > 4) || (currentIndex_z > 4))
						continue;
					if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() == currentIndex_x)&&(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() == currentIndex_z))
						gEnviroment::MapsService()->Maps()[map_index]->SetRealTimeLoadFlag(L_LOW);
				}

			for(int currentIndex_x = - 2; currentIndex_x <= 2; currentIndex_x++)
				for(int currentIndex_z = - 2; currentIndex_z <= 2; currentIndex_z++)
				{
					if((currentIndex_x < 0) || (currentIndex_z < 0) || (currentIndex_z > 4) || (currentIndex_z > 4))
						continue;
					if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() == currentIndex_x)&&(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() == currentIndex_z))
						gEnviroment::MapsService()->Maps()[map_index]->SetRealTimeLoadFlag(L_MIDDLE);
				}

			for(int currentIndex_x = - 1; currentIndex_x <= 1; currentIndex_x++)
				for(int currentIndex_z = - 1; currentIndex_z <= 1; currentIndex_z++)
				{
					if((currentIndex_x < 0) || (currentIndex_z < 0) || (currentIndex_z > 4) || (currentIndex_z > 4))
						continue;
					if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() == currentIndex_x)&&(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() == currentIndex_z))
						gEnviroment::MapsService()->Maps()[map_index]->SetRealTimeLoadFlag(L_HIGH);
				}
			
			if(gEnviroment::MapsService()->Maps()[map_index]->GetLoadFlag() != gEnviroment::MapsService()->Maps()[map_index]->GetRealTimeLoadFlag())
			{
				gEnviroment::MapsService()->Maps()[map_index]->SetLoadFlag(gEnviroment::MapsService()->Maps()[map_index]->GetRealTimeLoadFlag());
				gEnviroment::MapsService()->Maps()[map_index]->Load();
			}
			if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() < (point_index_i - 3))||(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() < (point_index_j - 3)) || 
			   (gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() > (point_index_i + 3))||(gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexJ() > (point_index_j + 3)))
					gEnviroment::MapsService()->Maps()[map_index]->Unload();

			last_map_index_i = point_index_i;
			last_map_index_j = point_index_j;
		}
	}
}

LPDIRECT3DTEXTURE9 gEnviroment::_shadowMapTexture = NULL;
bool gEnviroment::_shadowMapTextureSingleFlag = false;

LPDIRECT3DTEXTURE9 gEnviroment::_ShadowMapTexture()
{
    if(!_shadowMapTextureSingleFlag)
    {
		gDevice::device->CreateTexture(SHADOWMAP_SIZE, SHADOWMAP_SIZE, 1, D3DUSAGE_RENDERTARGET,D3DFMT_R32F, D3DPOOL_DEFAULT, &_shadowMapTexture, NULL );
		_shadowMapTextureSingleFlag = true;
        return _shadowMapTexture;
    }
    else
    {
        return _shadowMapTexture;
    }
}

/////////////////////////////////////////////////////////////

LPDIRECT3DSURFACE9 gEnviroment::_shadowDepthStencilSurface = NULL;
bool gEnviroment::_shadowDepthStencilSurfaceSingleFlag = false;

LPDIRECT3DSURFACE9 gEnviroment::_ShadowMapSurface()
{
    if(!_shadowDepthStencilSurfaceSingleFlag)
    {
		gDevice::device->CreateDepthStencilSurface(SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&_shadowDepthStencilSurface,NULL);
        _shadowDepthStencilSurfaceSingleFlag = true;
        return _shadowDepthStencilSurface;
    }
    else
    {
        return _shadowDepthStencilSurface;
    }
}

void gEnviroment::ShadowMap()
{
	gCore::EnableRenderToTexture(_ShadowMapTexture(),_ShadowMapSurface(),SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_R32F,0x00000000);

	D3DXMATRIX mLView,mLProj,mTView,mTProj;
    D3DXMatrixLookAtLH(&mLView, &gCore::Light()->Position, &D3DXVECTOR3(0.0f,0.0f,0.0f), &D3DXVECTOR3(0,1,0));
    D3DXMatrixPerspectiveFovLH(&mLProj, D3DXToRadian(90.0f), gWindow::wndWidth /gWindow::wndHeight, 0.5f, 3000.0f);

	mTView = gCore::Camera()->view;
	mTProj = gCore::Camera()->projection;

	gCore::Camera()->view = mLView;
	gCore::Camera()->projection = mLProj;

	gEnviroment::LevelContainer()->Render("shadow_effect");

	gCore::DisableRenderToTexture();
	gCore::Camera()->view = mTView;
	gCore::Camera()->projection = mTProj;

	gCore::TexturesService()->Insert("hardShadowMapTexture",_ShadowMapTexture());
}


DWORD WINAPI mapsLoadThread(LPVOID data)
{
	gEnviroment::_mapsLoadThread();
	return 0;
}