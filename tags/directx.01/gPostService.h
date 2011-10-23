#define SHADOWMAP_SIZE 512
#define BLOOM_SIZE 256
#pragma once
class gPostService
{
private :
    IDirect3DTexture9* SimpleImageTexture;
	
	IDirect3DTexture9* BlurBloomHRImageTexture;
	IDirect3DTexture9* BlurBloomVRImageTexture;
	IDirect3DTexture9* BloomImageTexture;
	
	IDirect3DTexture9* BlurShadowMapImageTexture;
	IDirect3DTexture9* ShadowMapImageTexture;

	IDirect3DSurface9* SimpleImageDepthStencilSurface;
	IDirect3DSurface9* BloomImageDepthStencilSurface;
	IDirect3DSurface9* ShadowMapImageDepthStencilSurface;

	ID3DXMesh* Mesh;

	ID3DXEffect* Effect;

	gScene* scene;

	DWORD num_vertices, num_primitives;

	void _RenderSimpleImage();
	void _RenderShadowMapImage();
	void _RenderBloomImage();
public :
	
	gPostService();
	~gPostService() ;
	void Load(gScene* scene);
	void Render();
	void Update();
};


gPostService::gPostService()
{
	this->Effect = NULL;
	
	gDevice::device->CreateTexture(gWindow::wndWidth,gWindow::wndHeight,1, D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &SimpleImageTexture, NULL );
	
	gDevice::device->CreateTexture(BLOOM_SIZE,BLOOM_SIZE,1, D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &BlurBloomHRImageTexture, NULL );
	gDevice::device->CreateTexture(BLOOM_SIZE,BLOOM_SIZE,1, D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &BlurBloomVRImageTexture, NULL );
	gDevice::device->CreateTexture(BLOOM_SIZE,BLOOM_SIZE,1, D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &BloomImageTexture, NULL );

	gDevice::device->CreateTexture(SHADOWMAP_SIZE,SHADOWMAP_SIZE,1, D3DUSAGE_RENDERTARGET,D3DFMT_R32F, D3DPOOL_DEFAULT, &BlurShadowMapImageTexture, NULL );
	gDevice::device->CreateTexture(SHADOWMAP_SIZE,SHADOWMAP_SIZE,1, D3DUSAGE_RENDERTARGET,D3DFMT_R32F, D3DPOOL_DEFAULT, &ShadowMapImageTexture, NULL );
	
	gDevice::device->CreateDepthStencilSurface(gWindow::wndWidth,gWindow::wndWidth,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&SimpleImageDepthStencilSurface,NULL);

	gDevice::device->CreateDepthStencilSurface(BLOOM_SIZE,BLOOM_SIZE,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&BloomImageDepthStencilSurface,NULL);

	gDevice::device->CreateDepthStencilSurface(SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&ShadowMapImageDepthStencilSurface,NULL);

}

gPostService::~gPostService()
{

}

void gPostService::Load(gScene* scene)
{
	this->scene = scene;

	this->num_vertices = 4;
	this->num_primitives = 2;

	gVertex* p_vertex_data = NULL;
    short* p_index_data = NULL;

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


	D3DXCreateMesh(this->num_primitives,this->num_vertices, D3DXMESH_MANAGED ,gCore::shaderVertexElemets,gDevice::device,&this->Mesh);
	this->Mesh->LockVertexBuffer(D3DLOCK_NOSYSLOCK,(LPVOID*)&p_vertex_data);	
	unsigned index = 0;
		p_vertex_data[index].position = D3DXVECTOR3(-1.0f,-1.0f,0.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR3(-1.0f,1.0f,0.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(0.0f,0.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR3(1.0f,-1.0f,0.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,1.0f);
		index++;
		p_vertex_data[index].position = D3DXVECTOR3(1.0f,1.0f,0.0f);
		p_vertex_data[index].texture = D3DXVECTOR2(1.0f,0.0f);
		index++;
	this->Mesh->UnlockVertexBuffer();

	index = 0;

	this->Mesh->LockIndexBuffer(0,(void**)&p_index_data);
	int a = 0;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a--;

		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
		p_index_data[index++] = a; a++;
	this->Mesh->UnlockIndexBuffer();

	HRESULT error_result;
	char* error_name;
	LPD3DXBUFFER errors = NULL;

	error_result = D3DXCreateEffectFromFile(gDevice::device, "Content\\shaders\\Post.fx", NULL, NULL, 0, NULL, &this->Effect, &errors);

	if(FAILED( error_result ))
        error_name = ( char* )errors->GetBufferPointer();
}

void gPostService::_RenderShadowMapImage()
{
	gEnviroment::ShadowMap();

	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Effect->SetTechnique("GaussianBlurVr");
	Effect->SetFloat("BlurDistance",0.001);
	Effect->SetTexture("renderTargetTexture_01",gCore::TexturesService()->Find("hardShadowMapTexture"));
	gCore::EnableRenderToTexture(this->BlurShadowMapImageTexture,this->ShadowMapImageDepthStencilSurface,SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_R32F,0xFFFFFFFF);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gCore::DisableRenderToTexture();

	Effect->SetTechnique("GaussianBlurVr");
	Effect->SetTexture("renderTargetTexture_01",this->BlurShadowMapImageTexture);

	gCore::EnableRenderToTexture(this->ShadowMapImageTexture,this->ShadowMapImageDepthStencilSurface,SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_R32F,0xFFFFFFFF);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gCore::DisableRenderToTexture();

	gCore::TexturesService()->Insert("softShadowMapTexture",this->ShadowMapImageTexture);
}

void gPostService::_RenderSimpleImage()
{
	gCore::EnableRenderToTexture(this->SimpleImageTexture,this->SimpleImageDepthStencilSurface,gWindow::wndWidth,gWindow::wndHeight,D3DFMT_A32B32G32R32F,0x00000000);
	this->scene->Update();
	this->scene->Render();
	gCore::DisableRenderToTexture();
	//if( ::GetAsyncKeyState('O') & 0x8000f )
	//	D3DXSaveTextureToFile("C:\\temp.png",D3DXIFF_PNG,this->SimpleImageTexture,NULL);
	gEnviroment::Reflection();
}

void gPostService::_RenderBloomImage(){

	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Effect->SetTechnique("BloomExtract");
	Effect->SetTexture("renderTargetTexture_01",this->SimpleImageTexture);
	gCore::EnableRenderToTexture(this->BloomImageTexture,this->BloomImageDepthStencilSurface,BLOOM_SIZE,BLOOM_SIZE,D3DFMT_A32B32G32R32F,0xFFFFFFFF);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gCore::DisableRenderToTexture();

	Effect->SetTechnique("GaussianBlurVr");
	Effect->SetFloat("BlurDistance",0.004);
	Effect->SetTexture("renderTargetTexture_01",this->BloomImageTexture);
	gCore::EnableRenderToTexture(this->BlurBloomVRImageTexture,this->BloomImageDepthStencilSurface,BLOOM_SIZE,BLOOM_SIZE,D3DFMT_A32B32G32R32F,0xFFFFFFFF);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gCore::DisableRenderToTexture();

	Effect->SetTechnique("GaussianBlurVr");
	Effect->SetTexture("renderTargetTexture_01",this->BlurBloomVRImageTexture);
	gCore::EnableRenderToTexture(this->BlurBloomHRImageTexture,this->BloomImageDepthStencilSurface,BLOOM_SIZE,BLOOM_SIZE,D3DFMT_A32B32G32R32F,0xFFFFFFFF);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gCore::DisableRenderToTexture();
}

void gPostService::Update()
{
	this->_RenderShadowMapImage();
	this->_RenderSimpleImage();
	this->_RenderBloomImage();
}

void gPostService::Render()
{
	Effect->SetTechnique("BloomCombine");
	Effect->SetTexture("renderTargetTexture_01",this->BlurBloomHRImageTexture);
	Effect->SetTexture("renderTargetTexture_02",this->SimpleImageTexture);
	Effect->Begin(NULL,NULL);
	Effect->BeginPass(NULL);
	this->Mesh->DrawSubset(NULL);
	Effect->EndPass();
	Effect->End();
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}