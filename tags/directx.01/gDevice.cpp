#include "gDevice.h"

LPDIRECT3D9 gDevice::d3d = NULL;
LPDIRECT3DDEVICE9 gDevice::device = NULL;

bool gDevice::Load()
{       
	D3DDISPLAYMODE d3dMode;
	D3DPRESENT_PARAMETERS d3dpp;
	
	if(d3d != NULL){
		 d3d->Release();
		 d3d = NULL;
	}
	if(device != NULL){
		device->Release();
		device = NULL;
	}

   d3d = Direct3DCreate9(D3D_SDK_VERSION);

   if(d3d == NULL){
         MessageBox(NULL, "DirectX 9.0 не инициализирован...","Ошибка!", MB_OK);
         return false;
      }

   if(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dMode)))
      {
         MessageBox(NULL, "Невозможно получить настройки экрана...", "Ошибка!", MB_OK);
         return false;
      }


   ZeroMemory(&d3dpp, sizeof(d3dpp));

   if(gWindow::fullScreen){
        d3dpp.Windowed = FALSE;              
        d3dpp.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
        d3dpp.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
   }else{
	    d3dpp.Windowed = TRUE;  
		d3dpp.BackBufferWidth  = gWindow::wndWidth;
		d3dpp.BackBufferHeight = gWindow::wndHeight;
   }

    d3dpp.BackBufferFormat           = d3dMode.Format;
	d3dpp.BackBufferCount            = 3;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil     = TRUE;
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24X8;

	if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWindow::hWindow,
                               D3DCREATE_HARDWARE_VERTEXPROCESSING  | D3DCREATE_MULTITHREADED ,
                               &d3dpp, &device)))
   {
      MessageBox(NULL, "Невозможно создать устройство DirectX 9.0","Ошибка!", MB_OK);
      return false;
   }

}

bool gDevice::Init()
{
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); 
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
    device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
    device->SetRenderState(D3DRS_ALPHAREF, (DWORD)128);
	device->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_TWEENING);
	return true;
}