#pragma once
#include "gMeshDynamic.h"
#include "gConverter.h"

class gScene
{
private :
	float angle;
	int camera_offset;
	D3DXVECTOR2 last_point_position;
	float theSmoothingHeightCash[65536];

    D3DXVECTOR3 vPosition;
    D3DXVECTOR3 vDirection;
    D3DXVECTOR3 vUp;
	D3DXVECTOR3 vRight;
	D3DXVECTOR3 vTempRight;
	D3DXVECTOR2 vRotationAmount;
	D3DXVECTOR3 vVelocity;
    float RotationRate;
	float cameraWheel;

	gVertex *theCircleVertices;

	

	//gModel* wowModel;
	//gM2Converter* wowConv;
	//gMeshStatic *newModel;

	//gStaticMesh *mesh;
public :
	gScene();
	~gScene();
	D3DXVECTOR3 target_point_position;
	float lookAtUp;
	void Render();
	void Update();
	void Morph(float power, float point_position_x, float point_position_z);
	void EditGrass(float radius, float point_position_x, float point_position_z,bool flag);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();
	void UpdateCameraRotation();
	void RenderShadowMap();
	void RenderCircle();
	D3DXVECTOR3* point_position;
	D3DXVECTOR3 theLocationMousePosition;

	//gMeshDynamic *player;
	//gDynamic* player;
};

gScene::gScene(){
	this->point_position = new D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->last_point_position = D3DXVECTOR2(-1.0f,-1.0f);
	camera_offset = 0;
	this->angle = 0.0f;
	this->lookAtUp = 256.0f;
	//this->editRadius = 64.0f;
	theLocationMousePosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//gResource::MeshStaticService()->Find(gResource::MeshStaticService()->Name()[0])->vPosition = D3DXVECTOR3(868,128,324);
	//gEnviroment::MeshStaticService()->Find("model_01")->Position = D3DXVECTOR3(256,128,256);
	//gResource::MeshStaticService()->Find(gResource::MeshStaticService()->Name()[1])->vPosition = D3DXVECTOR3(900,128,760);
	//gResource::MeshStaticService()->Find(gResource::MeshStaticService()->Name()[2])->vPosition = D3DXVECTOR3(350,128,350);
	//gEnviroment::MeshService()->Find("Tower_01")->Position = D3DXVECTOR3(256,128,256);
	//gEnviroment::MeshService()->Find("Defender")->Position = D3DXVECTOR3(700,128,760);
	//gEnviroment::MeshService()->Find("Box")->Position = D3DXVECTOR3(0,256,0);
	this->cameraWheel = 128.0f;

	//this->player = new gMeshDynamic();
	//this->player->Load();
	//this->player->SetAnimation(RUN);

	this->vPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
    this->vDirection = D3DXVECTOR3(0.0f,0.0f,-1.0f);
    this->vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	this->vRight = D3DXVECTOR3(1.0f,0.0f,0.0f);
	this->vTempRight = D3DXVECTOR3(1.0f,0.0f,0.0f);
	this->vRotationAmount = D3DXVECTOR2(0.0f,0.0f);
	this->vVelocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->RotationRate = 1.5f;


	
	//gConverter::ConvertM3("Content\\models\\Armory.m3");
	gConverter::ConvertM3("Content\\models\\Autoturret.m3");
	gConverter::ConvertM2("Content\\models\\westfallchurch.m2");
	////////////////////////////////////////////////////////
	//this->wowModel = new gModel("aaa");
	//this->wowConv = new gM2Converter();
	//this->wowConv->Convert("Content\\models\\burninggiantwheel.m2","Content\\models\\burninggiantwheel00.skin","Content\\models\\model_01");
	//this->wowConv->Convert("Content\\models\\westfallchurch.m2","Content\\models\\westfallchurch00.skin","Content\\models\\model_02");
	//this->wowConv->Convert("Content\\models\\lotharstatue.m2","Content\\models\\lotharstatue00.skin","Content\\models\\model_03");
	//this->wowConv->Convert("Content\\models\\humanfemale.m2","Content\\models\\humanfemale00.skin","Content\\models\\model_04");
	//this->newModel = new gMeshStatic();
	//this->newModel->Load("Content\\models\\westfallchurch.gmv","Content\\models\\westfallchurch.gmt","Content\\models\\westfallchurch.gmi");
}
gScene::~gScene(){

}

void gScene::MoveForward()
{
	if(((this->target_point_position.x - (float)sin(angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.x - (float)sin(angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.x -= (float)sin(angle*0.0174532925f) * 5.0f;
	if(((this->target_point_position.z - (float)cos(angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.z - (float)cos(angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.z -= (float)cos(angle*0.0174532925f) * 5.0f;
}

void gScene::MoveBackward()
{
	if(((this->target_point_position.x + (float)sin(angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.x + (float)sin(angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.x  += (float)sin(angle*0.0174532925f) * 5.0f;
	if(((this->target_point_position.z + (float)cos(angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.z + (float)cos(angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.z  += (float)cos(angle*0.0174532925f) * 5.0f;
}


void gScene::MoveRight()
{
	if(((this->target_point_position.x - (float)cos(-angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.x - (float)cos(-angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.x -= (float)cos(-angle*0.0174532925f) * 5.0f;
	if(((this->target_point_position.z - (float)sin(-angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.z - (float)sin(-angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.z -= (float)sin(-angle*0.0174532925f) * 5.0f;
}

void gScene::MoveLeft()
{
	if(((this->target_point_position.x + (float)cos(-angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.x + (float)cos(-angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.x  += (float)cos(-angle*0.0174532925f) * 5.0f;
	if(((this->target_point_position.z + (float)sin(-angle*0.0174532925f) * 5.0f) > 10) &&
	   ((this->target_point_position.z + (float)sin(-angle*0.0174532925f) * 5.0f) < (4*MAP_SIZE*10 - 10)))
		this->target_point_position.z  += (float)sin(-angle*0.0174532925f) * 5.0f;
}

void gScene::RotateLeft(){
	angle -= 2.0f;
	gCore::Camera()->lookAtAngle = angle;
	//gCore::Camera()->MoveRight(-10.0f);//angle = angle;
}

void gScene::RotateRight(){
	//gCore::Camera()->MoveRight(10.0f);
	angle += 2.0f;
	gCore::Camera()->lookAtAngle = angle;
}

void gScene::EditGrass(float radius, float point_position_x, float point_position_z,bool flag)
{
	float around_angle = 0.0f;
	float temp_point_position_x = point_position_x;
	float temp_point_position_z = point_position_z;

	temp_point_position_x += cos(around_angle)*45.0f;
	temp_point_position_z += sin(around_angle)*45.0f;
	int index_x = (int)(temp_point_position_x / (640));
	int index_z = (int)(temp_point_position_z / (640));

	radius = 100.0f;

	int minIndX = (int)floor(target_point_position.x - radius)/10.0f;
	int minIndZ = (int)floor(target_point_position.z - radius)/10.0f;
	int maxIndX = (int)floor(target_point_position.x + radius)/10.0f;
	int maxIndZ = (int)floor(target_point_position.z + radius)/10.0f;

	//for (int x = minIndX; x < maxIndX; x++)
	//	for (int z = minIndZ; z < maxIndZ; z++) 
	//	{
	//		if((x < 0) || (z < 0)) continue;
	//		gEnviroment::MapsService()->GetMapDecorationMask()[x][z].r = 1.0f;
	//	}

	//for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index){
	//	if((gEnviroment::MapsService()->Maps()[map_index]->GetMapChankIndexI() == index_x)&&(gEnviroment::MapsService()->Maps()[map_index]->map_index_j == index_z))
	//			gEnviroment::MapsService()->Maps()[map_index]->EditGrass(gEnviroment::MapsService()->GetMapHeightMap(),gEnviroment::MapsService()->GetMapDecorationMask());
	//	}
}


void gScene::Morph(float incHeight, float point_position_x, float point_position_z){
	
	
}

void gScene::UpdateCameraRotation()
{
	//, GetSystemMetrics(SM_CYSCREEN)
	//GetCursorPos(&mousePosition);
	//if((GetSystemMetrics(SM_CXSCREEN)/2 - mousePosition.x)  > 0)
	//	angle -= 2.0f;
	//else
	//angle +=(window_width/2 - mousePosition.x)/-10.0f;

	//lookAtUp +=(window_height/2 - mousePosition.y)/10.0f;

	//if(lookAtUp < -512.0f)
	//	lookAtUp = -512.0f;
	//if(lookAtUp > 512.0f)
	//	lookAtUp = 512.0f;

	//if(mousePosition.x < (gWindow::wndWidth/2 - 1))
	//	gCore::Camera()->Yaw(-0.05f);
	//if(mousePosition.x > (gWindow::wndWidth/2 + 1))
	//	gCore::Camera()->Yaw(0.05f);
	//gWindow::wndHeight
	//if(mousePosition.y < (window_height/2 - 1))
	//	gCore::Camera()->Pitch(-0.05f);
	//if(mousePosition.y > (window_height/2 + 1))
	//	gCore::Camera()->Pitch(0.05f);

	//SetCursorPos(window_width/2,window_height/2);

	//gCore::Camera()->angle = angle;
}

void gScene::Update()
{
		 /// float elapsed = 0.01f;


            // Determine rotation amount from input
         //   D3DXVECTOR2 rotationAmount = D3DXVECTOR2(0.0f,0.0f);
         //   if (::GetAsyncKeyState('A') & 0x8000f)
         //       rotationAmount.x = 1.0f;
         //   if (::GetAsyncKeyState('D') & 0x8000f)
         //       rotationAmount.x = -1.0f;
         //   if (::GetAsyncKeyState('W') & 0x8000f)
        //        rotationAmount.y = -1.0f;
         //   if (::GetAsyncKeyState('S') & 0x8000f)
         //       rotationAmount.y = 1.0f;

            // Scale rotation amount to radians per second
         //   rotationAmount = rotationAmount * RotationRate * elapsed;

            // Correct the X axis steering when the ship is upside down
         //   if (vUp.y < 0)
          //      rotationAmount.x = -rotationAmount.x;


            // Create rotation matrix from rotation amount
         //   D3DXMATRIX rotationMatrix,rotationMatrixAxis,rotationMatrixY;
		//	D3DXMatrixRotationAxis(&rotationMatrixAxis,&vRight,rotationAmount.y);
		//	D3DXMatrixRotationY(&rotationMatrixY,rotationAmount.x);
		//	rotationMatrix = rotationMatrixAxis*rotationMatrixY;
             //   Matrix.CreateFromAxisAngle(Right, rotationAmount.Y) *
             //   Matrix.CreateRotationY(rotationAmount.X);

            // Rotate orientation vectors
		//	D3DXVec3TransformNormal(&vDirection,&vDirection,&rotationMatrix);
		//	D3DXVec3TransformNormal(&vUp,&vUp,&rotationMatrix);
			
			//Direction = Vector3.TransformNormal(Direction, rotationMatrix);
           // Up = Vector3.TransformNormal(Up, rotationMatrix);

            // Re-normalize orientation vectors
            // Without this, the matrix transformations may introduce small rounding
            // errors which add up over time and could destabilize the ship.
			//D3DXVec3Normalize(&vDirection,&vDirection);
		//	D3DXVec3Normalize(&vUp,&vUp);
			//Direction.Normalize();
           // Up.Normalize();

		//	D3DXVec3Cross(&vRight,&vDirection,&vUp);

            // Re-calculate Right
          //  right = Vector3.Cross(Direction, Up);

            // The same instability may cause the 3 orientation vectors may
            // also diverge. Either the Up or Direction vector needs to be
            // re-computed with a cross product to ensure orthagonality
			//vUp = 
			//D3DXVec3Cross(&vUp,&vRight,&vDirection);
			//Up = Vector3.Cross(Right, Direction);


            // Determine thrust amount from input
           // float thrustAmount = gamePadState.Triggers.Right;
		//	float thrustAmount;
        //    if (::GetAsyncKeyState('E') & 0x8000f)
        //        thrustAmount = 1.0f;

            // Calculate force from thrust amount
		//	D3DXVECTOR3 force = vDirection * thrustAmount * 24000.0f;


            // Apply acceleration
        //    D3DXVECTOR3 acceleration = force / 1.0f;
        //    vVelocity += acceleration * elapsed;

            // Apply psuedo drag
        //    vVelocity *= 0.97f;

            // Apply velocity
        //    vPosition += vVelocity * elapsed;

		//	gCore::Camera()->ChasePosition = vPosition;
		//	gCore::Camera()->ChaseDirection = vDirection;
		//	gCore::Camera()->vvUp = vUp;
			//  camera.ChasePosition = ship.Position;
            //camera.ChaseDirection = ship.Direction;
           // camera.Up = ship.Up;
            // Prevent ship from flying under the ground
            //vPosition.Y = Position.Y;//Math.Max(Position.Y, MinimumAltitude);


//	GetCursorPos(&mousePosition);
//	ScreenToClient(hwnd, &mousePosition);

	this->target_point_position.y = gEnviroment::MapsService()->Height(this->target_point_position.x,this->target_point_position.z);
	//gEnviroment::MeshService()->Find("Box")->Rotation.x = gEnviroment::MapsService()->Height(this->target_point_position.x,this->target_point_position.z).y;
	//gEnviroment::MeshService()->Find("Box")->Rotation.z = gEnviroment::MapsService()->Height(this->target_point_position.x,this->target_point_position.z).z;
    //gEnviroment::MeshService()->Find("Box")->Rotation.y = gCore::Camera()->Rotation.y;
	
	//gEnviroment::LevelContainer()->GetPlayerMesh()->vRotation.x = gEnviroment::MapsService()->Normal(this->target_point_position.x,this->target_point_position.z).x;
	//gEnviroment::LevelContainer()->GetPlayerMesh()->vRotation.z = gEnviroment::MapsService()->Normal(this->target_point_position.x,this->target_point_position.z).y;

	

	gEnviroment::Sky()->Position.y = this->target_point_position.y + 64.0f; 
	this->point_position = &gEnviroment::Sky()->Position;
	gCore::Light()->Update();

	gEnviroment::Sky()->Position.x = this->target_point_position.x;
	gEnviroment::Sky()->Position.z = this->target_point_position.z;


	//gEnviroment::MeshService()->Find("Box")->Position = target_point_position;//D3DXVECTOR3(0,256,0);
	gEnviroment::LevelContainer()->GetPlayerMesh()->vPosition = target_point_position;
	
	gCore::Camera()->Rotation.y = gCore::Camera()->lookAtAngle*0.0174532925f;
	
	gCore::Camera()->Position.x = target_point_position.x + cos(-(gCore::Camera()->Rotation.y) + 1.57f)*gCore::Camera()->XZDistance;
    gCore::Camera()->Position.z = target_point_position.z + sin(-(gCore::Camera()->Rotation.y) + 1.57f)*gCore::Camera()->XZDistance;
	
	if(((target_point_position.x + cos(-(gCore::Camera()->Rotation.y) + 1.57f)*cameraWheel) > 10) &&
	   ((target_point_position.x + cos(-(gCore::Camera()->Rotation.y) + 1.57f)*cameraWheel) < (4*MAP_SIZE*10 - 10)) &&			
	   ((target_point_position.z + sin(-(gCore::Camera()->Rotation.y) + 1.57f)*cameraWheel) > 10) &&
	   ((target_point_position.z + sin(-(gCore::Camera()->Rotation.y) + 1.57f)*cameraWheel) < (4*MAP_SIZE*10 - 10)))			
		gCore::Camera()->Position.y = gEnviroment::MapsService()->Height(gCore::Camera()->Position.x,gCore::Camera()->Position.z) + gCore::Camera()->YDistance;
	else
		gCore::Camera()->Position.y = target_point_position.y + gCore::Camera()->YDistance;
	
	gCore::Camera()->LookAt = target_point_position;
	gCore::Camera()->LookAt.y = target_point_position.y + 32.0f;
	//gCore::Camera()->LookAt = target_point_position;
	//gCore::Camera()->Update();

  for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index)
	  if(gEnviroment::MapsService()->Maps()[map_index]->GetRenderFlag() != R_UNLOAD ){
		//gEnviroment::MapsService()->Maps()[map_index]->Update(false);
		D3DXVECTOR3 VecDir;
		D3DXVECTOR3 VecPos;
		D3DXVECTOR3 CursorPos;
		D3DXMATRIX mWorld;
		D3DVIEWPORT9 g_ViewportFB;	
		POINT mousePosition;
		GetCursorPos(&mousePosition);
		CursorPos = D3DXVECTOR3(mousePosition.x,mousePosition.y,0.0f);
		D3DXVECTOR3 CameraPos= gCore::Camera()->Position;
		D3DXMATRIX View=gCore::Camera()->view;
		D3DXMATRIX Projection=gCore::Camera()->projection;
		D3DXMatrixIdentity(&mWorld);

		gDevice::device->GetViewport(&g_ViewportFB);
		g_ViewportFB.Height = gWindow::wndHeight;
		g_ViewportFB.Width = gWindow::wndWidth;
		D3DXVec3Unproject(&VecPos,&CursorPos,&g_ViewportFB,&Projection,&View,&mWorld);
		D3DXVec3Normalize(&VecDir,&(VecPos-CameraPos));
		float floorDistPoint = 0;
		//gEnviroment::MapsService()->Maps()[map_index]->IntersectRay(&CameraPos, &VecDir, &floorDistPoint, &theLocationMousePosition);
	}
}


void gScene::RenderShadowMap()
{
	//std::map<std::string,gMeshStatic*>::iterator meshIterator = gEnviroment::MeshStaticService()->Begin();
   //for(;meshIterator != gEnviroment::MeshStaticService()->End();meshIterator++)
  // {
	   
	//   meshIterator->second->Render();	
  // }
}

void gScene::Render()
{
  for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index)
  {
	    gEnviroment::MapsService()->Maps()[map_index]->Update(false);
		gEnviroment::MapsService()->Maps()[map_index]->Render(GROUND);
		gEnviroment::MapsService()->Maps()[map_index]->Render(GRASS);
  }	
  for(unsigned map_index = 0; map_index < gEnviroment::MapsService()->Maps().size(); ++map_index)
  {
		gEnviroment::MapsService()->Maps()[map_index]->Render(WATER);	
  }	

  gEnviroment::Sky()->Update();
  gEnviroment::Sky()->Render();

   //gEnviroment::Ocean()->Scale = D3DXVECTOR3(100.0f,0.0f,100.0f);
   //gEnviroment::Ocean()->Position = D3DXVECTOR3(-1000.0f,0.0f,-1000.0f);
   //gEnviroment::Ocean()->Update();
   //gEnviroment::Ocean()->Render();

  gEnviroment::LevelContainer()->Render("mesh_effect");

   /*std::map<std::string,gMeshStatic*>::iterator meshIterator = gEnviroment::MeshStaticService()->Begin();
   for(;meshIterator != gEnviroment::MeshStaticService()->End();meshIterator++)
   {
	    meshIterator->second->currentEffectName = "mesh_effect";
		meshIterator->second->Render();
   }*/

   /*std::map<char*,gStaticMesh*>::iterator meshIterator = gEnviroment::MeshService()->Begin();
   for(;meshIterator != gEnviroment::MeshService()->End();meshIterator++)
   {
		meshIterator->second->Update();
		meshIterator->second->Render();
   }*/
	
    //this->wowModel->Render();
  //this->newModel->Render();


   //this->player->PlayAnimation();
   //this->player->Update("none");
   //this->player->Render("none");

   this->RenderCircle();
}

void gScene::RenderCircle() 
{
	//float radius = 100;
	int theCircleNumVertices = 16;
	static bool createVIBuffer = true;
	int vertNumber = 0;
	float step = 360.0f / theCircleNumVertices;
	DWORD FrontColor = 0xffffff00;
	DWORD BackColor = 0xffbd7a10;
	if (createVIBuffer) {
		theCircleVertices = new gVertex[theCircleNumVertices+1];
		createVIBuffer = false;
		for (int x = 0; x < (int)theCircleNumVertices; x++) {
			theCircleVertices[vertNumber].position.x=cos(D3DXToRadian(step * x));
			theCircleVertices[vertNumber].position.z=sin(D3DXToRadian(step * x));
			theCircleVertices[vertNumber].position.y=1.0f;
			vertNumber++;
		}
		theCircleVertices[vertNumber].position.x=theCircleVertices[0].position.x;
		theCircleVertices[vertNumber].position.z=theCircleVertices[0].position.z;
		theCircleVertices[vertNumber].position.y=theCircleVertices[0].position.y;
	}

	float height = 0;
	vertNumber = 0;
	for (int x = 0; x < (int)theCircleNumVertices; x++) {
		//GetFloorHeight(theCircleVertices[vertNumber].position.x * radius + theLocationMousePosition.x, theCircleVertices[vertNumber].position.z  * radius + theLocationMousePosition.z, height);
		theCircleVertices[vertNumber].position.y = gEnviroment::MapsService()->Height(theCircleVertices[vertNumber].position.x * gCore::editRadius + this->target_point_position.x, theCircleVertices[vertNumber].position.z  * gCore::editRadius + this->target_point_position.z) + 0.3f;
		vertNumber++;
	}
	theCircleVertices[vertNumber].position.y=theCircleVertices[0].position.y;

	//GetFloorHeight(theLocationMousePosition.x, theLocationMousePosition.z, height);
	//for (int i=0;i<4;i++)
	//	theCenterPointVertices[i].pos.y=height+0.3f;

	//LPDIRECT3DDEVICE9 pDevice=NGECore::GetDevice();
	D3DXMATRIX TranslateMatrix, ScaleMatrix;
	D3DXMatrixScaling(&ScaleMatrix, gCore::editRadius, 1, gCore::editRadius);
	D3DXMatrixTranslation(&TranslateMatrix,target_point_position.x, 0,target_point_position.z);
	TranslateMatrix = ScaleMatrix * TranslateMatrix;

	gCore::ShadersService()->Find("shadow_effect")->SetMatrix("mWorld", &TranslateMatrix);
	gCore::ShadersService()->Find("shadow_effect")->SetMatrix("mView", &gCore::Camera()->view);
	gCore::ShadersService()->Find("shadow_effect")->SetMatrix("mProjection", &gCore::Camera()->projection);
	//this->effectsList[this->currentEffectName]->SetMatrix("mShadowMap", &mShadowMap);
	///this->effectsList[this->currentEffectName]->SetTexture("ShadowMapTexture",gCore::TexturesService()->Find("softShadowMapTexture"));

	//this->effectsList[this->currentEffectName]->SetMatrix("mWorld", &mWorld);
	//this->effectsList[this->currentEffectName]->SetMatrix("mView", this->mView);
	//this->effectsList[this->currentEffectName]->SetMatrix("mProjection", this->mProjection);
	//gDevice::device->SetTexture(0, NULL);			
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	//pDevice->SetRenderState( D3DRS_LIGHTING, FALSE);
	//pDevice->SetTransform(D3DTS_WORLD, &TranslateMatrix);
	//pDevice->SetFVF(EDITOR_CIRCLE_VERTEX_BUFFER_FVF);
	gDevice::device->SetRenderState( D3DRS_ZENABLE, FALSE);	

	gCore::ShadersService()->Find("shadow_effect")->Begin(NULL, 0);
	gCore::ShadersService()->Find("shadow_effect")->BeginPass(0);
	
	gDevice::device->DrawPrimitiveUP(D3DPT_LINESTRIP, theCircleNumVertices, theCircleVertices, sizeof(gVertex));

	gDevice::device->SetRenderState( D3DRS_ZENABLE, TRUE);

	gCore::ShadersService()->Find("shadow_effect")->EndPass();
	gCore::ShadersService()->Find("shadow_effect")->End();
	/*for (int i=0;i<4;i++) theCenterPointVertices[i].color=BackColor;
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, theCenterPointVertices,sizeof(CircleLineVertex));
	

	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE);	
	for (int x = 0; x < (int)theCircleNumVertices+1; x++) 
		theCircleVertices[x].color = FrontColor;
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, theCircleNumVertices, theCircleVertices, sizeof(CircleLineVertex));
	
	for (int i=0;i<4;i++) theCenterPointVertices[i].color=FrontColor;
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, theCenterPointVertices,sizeof(CircleLineVertex));
	*/
}