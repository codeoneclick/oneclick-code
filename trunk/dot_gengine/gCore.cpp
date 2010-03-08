#include "gCore.h"

float gCore::editRadius = 64.0f;

gTexturesService* gCore::_texturesService = NULL;
bool gCore::_texturesServiceSingleFlag = false;

gTexturesService* gCore::TexturesService()
{
    if(!_texturesServiceSingleFlag)
    {
        _texturesService = new gTexturesService();
        _texturesServiceSingleFlag = true;
        return _texturesService;
    }
    else
    {
        return _texturesService;
    }
}

gShadersService* gCore::_shadersService = NULL;
bool gCore::_shadersServiceSingleFlag = false;

gShadersService* gCore::ShadersService()
{
    if(!_shadersServiceSingleFlag)
    {
        _shadersService = new gShadersService();
        _shadersServiceSingleFlag = true;
        return _shadersService;
    }
    else
    {
        return _shadersService;
    }
}

gCamera* gCore::_camera = NULL;
bool     gCore::_cameraSingleFlag = false;

gCamera* gCore::Camera()
{
    if(!_cameraSingleFlag)
    {
        _camera = new gCamera();
		_camera->Position = D3DXVECTOR3(512.0f,256.0f,512.0f);
        _cameraSingleFlag = true;
        return _camera;
    }
    else
    {
        return _camera;
    }
}

gLight* gCore::_global_light = NULL;
bool     gCore::_global_lightSingleFlag = false;

gLight* gCore::Light()
{
    if(!_global_lightSingleFlag)
    {
        _global_light = new gLight();
        _global_lightSingleFlag = true;
        return _global_light;
    }
    else
    {
        return _global_light;
    }
}

void gCore::Update()
{
	gCore::Camera()->Update();
	gCore::Light()->Update();
}

LPDIRECT3DSURFACE9 gCore::oldRenderTarget = NULL;
D3DVIEWPORT9 gCore::oldViewport;

LPDIRECT3DSURFACE9 gCore::currentRenderTarget = NULL;
D3DVIEWPORT9 gCore::currentViewport;

LPDIRECT3DSURFACE9 gCore::oldDepthStencilSurface = NULL;

void gCore::EnableRenderToTexture(IDirect3DTexture9* pOutTexture,LPDIRECT3DSURFACE9 shadowDepthStancilSurface,unsigned int width,unsigned int height,D3DFORMAT textureFormat,DWORD clearColor)
{
  gDevice::device->GetViewport(&oldViewport);
  gDevice::device->GetRenderTarget(0,&oldRenderTarget);
  gDevice::device->GetDepthStencilSurface(&oldDepthStencilSurface);	

  pOutTexture->GetSurfaceLevel(0,&currentRenderTarget);

  currentViewport.X = 0;
  currentViewport.Y = 0;
  currentViewport.Width  = width;
  currentViewport.Height = height;
  currentViewport.MinZ = 0.0f;
  currentViewport.MaxZ = 1.0f;

  gDevice::device->SetViewport(&currentViewport);
  gDevice::device->SetRenderTarget(0,currentRenderTarget);
  gDevice::device->SetDepthStencilSurface(shadowDepthStancilSurface);

  gDevice::device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,clearColor, 1.0f, 0);
  gDevice::device->BeginScene();
}

void gCore::DisableRenderToTexture()
{
  gDevice::device->EndScene();
 
  gDevice::device->SetDepthStencilSurface(oldDepthStencilSurface);

  if(oldDepthStencilSurface!=NULL)
  {
    oldDepthStencilSurface->Release();
    oldDepthStencilSurface=NULL;
  }
  
  if(currentRenderTarget != NULL)
  {
	  currentRenderTarget->Release();
	  currentRenderTarget = NULL;
  }

  gDevice::device->SetRenderTarget(0,oldRenderTarget);
  if(oldRenderTarget != NULL)
  {
    oldRenderTarget->Release();
    oldRenderTarget = NULL;
  }
  gDevice::device->SetViewport(&oldViewport);
}

D3DVERTEXELEMENT9 gCore::shaderVertexElemets[] = 
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

LPDIRECT3DVERTEXDECLARATION9 gCore::_ptrShaderDeclaration = NULL;
bool gCore::_ptrShaderDeclarationSingleFlag = false;

LPDIRECT3DVERTEXDECLARATION9 gCore::ShaderDeclaration()
{
	if(!_ptrShaderDeclarationSingleFlag)
    {
        gDevice::device->CreateVertexDeclaration(shaderVertexElemets,&_ptrShaderDeclaration);
        _ptrShaderDeclarationSingleFlag = true;
        return _ptrShaderDeclaration;
    }
    else
    {
        return _ptrShaderDeclaration;
    }
}


D3DVERTEXELEMENT9 gCore::md2ShaderVertexElemets[] = 
{
	{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};

LPDIRECT3DVERTEXDECLARATION9 gCore::_ptrMd2ShaderDeclaration = NULL;
bool gCore::_ptrMd2ShaderDeclarationSingleFlag = false;

LPDIRECT3DVERTEXDECLARATION9 gCore::Md2ShaderDeclaration()
{
	if(!_ptrMd2ShaderDeclarationSingleFlag)
    {
        gDevice::device->CreateVertexDeclaration(md2ShaderVertexElemets,&_ptrMd2ShaderDeclaration);
        _ptrMd2ShaderDeclarationSingleFlag = true;
        return _ptrMd2ShaderDeclaration;
    }
    else
    {
        return _ptrMd2ShaderDeclaration;
    }
}