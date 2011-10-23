#include "gEngine.h"

gScene *Scene;
gFps *Performance;
gText2D *FPS_text;
gPostService *post_effect;

class gEngine
{
public :
	static void Load();
	static void Render();
	static void Update();
	static void Shutdown();
	static void Input();
};

void gEngine::Load()
{
	gCore::TexturesService()->Load();
	gCore::ShadersService()->Load();
	gEnviroment::MapsService()->Load();
	
	gResource::MeshStaticService()->Load();
	gResource::MeshDynamicLoadService()->Load();
	gEnviroment::LevelContainer()->SetMapsService(gEnviroment::MapsService());
	gEnviroment::LevelContainer()->Load();

	Scene = new gScene();
	
	Scene->target_point_position =  D3DXVECTOR3(640.0f,0.0f,640.0f);
	Performance = new gFps();

	FPS_text = new gText2D();
	FPS_text->Position.y = 32.0f;
	FPS_text->SetTextAlign(T_HORIZONTAL_CENTER);
	gDevice::device->EvictManagedResources();

	post_effect = new gPostService();
	post_effect->Load(Scene);

	 
}

void gEngine::Update(){
	Performance->CalculateFrameRate();
	post_effect->Update();
}

void gEngine::Render()
{
   gDevice::device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,0x00000000, 1.0f, 0); 
   gDevice::device->BeginScene();
   post_effect->Render();
   FPS_text->SetText((int)Performance->Fps,D3DXVECTOR3(Scene->target_point_position.x,Scene->target_point_position.y,Scene->target_point_position.z));//Scene->theLocationMousePosition);
   FPS_text->Update();
   FPS_text->Render();
   gDevice::device->EndScene(); 
   gDevice::device->Present(NULL, NULL, NULL, NULL);
}

void gEngine::Input(){

	

	if( ::GetAsyncKeyState('W') & 0x8000f )
	{
		Scene->MoveForward();
		//Scene->player->SetAnimation(RUN);
	}
	if( ::GetAsyncKeyState('S') & 0x8000f )
	{
		Scene->MoveBackward();
		
	}

	if(::GetAsyncKeyState('W') & 0x8000f  || ::GetAsyncKeyState('S') & 0x8000f)
		gEnviroment::LevelContainer()->GetPlayerMesh()->SetAnimation(RUN);
		//Scene->player->SetAnimation(RUN);
	else
		gEnviroment::LevelContainer()->GetPlayerMesh()->SetAnimation(STAND);
		//Scene->player->SetAnimation(STAND);

	if( ::GetAsyncKeyState('A') & 0x8000f )
		Scene->MoveLeft();
	if( ::GetAsyncKeyState('D') & 0x8000f )
		Scene->MoveRight();
	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		Scene->RotateLeft();
	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		Scene->RotateRight();

	if( ::GetAsyncKeyState('C') & 0x8000f )
		gCore::editRadius++;
	if( ::GetAsyncKeyState('V') & 0x8000f )
		gCore::editRadius--;

	if( ::GetAsyncKeyState('G') & 0x8000f )
		Scene->EditGrass(10,Scene->target_point_position.x,Scene->target_point_position.z,true);

	if(gInput::mLeftDown)
		gEditService::EditGround(2.0f,gCore::editRadius,Scene->target_point_position.x,Scene->target_point_position.z);
	//if(is_space_down)
	//	gEnviroment::MapsService()->Save();
	if(gInput::mRightDown)
		gEditService::EditGround(-2.0f,gCore::editRadius,Scene->target_point_position.x,Scene->target_point_position.z);
	//Scene->UpdateCameraRotation();//
}

void gEngine::Shutdown()
{

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg; 
	gWindow::Load();
	gDevice::Load();
	gDevice::Init();
	gEngine::Load();
    while(true)
	{
         if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		 {  
			if(msg.message == WM_QUIT)
				 break;
			TranslateMessage(&msg); 
            DispatchMessage(&msg);  
         }
		 else
		 {
			gEngine::Input();
			gEngine::Update();
			gEngine::Render(); 
         }
   }
   gEngine::Shutdown();
   UnregisterClass("gEngine",hInstance);
   return (int)msg.wParam;
}