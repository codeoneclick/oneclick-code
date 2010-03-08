#include "gMeshDynamic.h"

#define D3DFVF_MODELVERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

gMeshDynamic::gMeshDynamic()
{
	this->animationSpeed = 60;
	this->currentFrame = 0;
	this->startFrame = 0;
	this->endFrame = 0;
    this->timerLastTime = 0;
	this->vPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->vRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->SetAnimation(STAND);
}

gMd2Animation gMeshDynamic::_animationList[21] = 
{
	{   0,  39,  9 },	// STAND
	{  40,  45, 10 },	// RUN
	{  46,  53, 10 },	// ATTACK
	{  54,  57,  7 },	// PAIN_A
	{  58,  61,  7 },	// PAIN_B
	{  62,  65,  7 },	// PAIN_C
	{  66,  71,  7 },	// JUMP
	{  72,  83,  7 },	// FLIP
	{  84,  94,  7 },	// SALUTE
	{  95, 111, 10 },	// FALLBACK
	{ 112, 122,  7 },	// WAVE
	{ 123, 134,  6 },	// POINT
	{ 135, 153, 10 },	// CROUCH_STAND
	{ 154, 159,  7 },	// CROUCH_WALK
	{ 160, 168, 10 },	// CROUCH_ATTACK
	{ 196, 172,  7 },	// CROUCH_PAIN
	{ 173, 177,  5 },	// CROUCH_DEATH
	{ 178, 183,  7 },	// DEATH_FALLBACK
	{ 184, 189,  7 },	// DEATH_FALLFORWARD
	{ 190, 197,  7 },	// DEATH_FALLBACKSLOW
	{ 198, 198,  5 },	// BOOM
};

void gMeshDynamic::SetAnimation(Md2Animation value)
{
	if(this->currentAnimation == value) return;
	this->currentAnimation = value;
	this->startFrame = this->_animationList[value].startFrameIndex;
	this->endFrame = this->_animationList[value].lastFrameIndex;
	this->currentFrame = this->_animationList[value].startFrameIndex;
	this->timerLastTime = 0;
}

void gMeshDynamic::Update(std::string effectName){
	
	DWORD timer_current_time = GetTickCount();	
    if((timer_current_time - this->timerLastTime) > this->animationSpeed){
	   this->timerLastTime = timer_current_time;
	   this->currentFrame++;
    }

	if(this->currentFrame > this->endFrame)
	   this->currentFrame = this->startFrame;

	D3DXMATRIX world_view_projection_matrix;
	D3DXMatrixIdentity(&world_view_projection_matrix);

	//this->vRotation.y = this->cCamera->Rotation.y; //+ 1.57f;

	D3DXMatrixScaling(&this->mScale,10.0f,10.0f,10.0f);
	D3DXMatrixTranslation(&this->mTranslation, this->vPosition.x,this->vPosition.y + 12.0f, this->vPosition.z);
	D3DXMatrixRotationX(&this->mRotationX,this->vRotation.x - 1.57f);
	D3DXMatrixRotationY(&this->mRotationY,this->vRotation.y);
	D3DXMatrixRotationZ(&this->mRotationZ,this->vRotation.z);
	this->mRotation = this->mRotationX*this->mRotationZ*this->mRotationY;
	this->mWorld = this->mScale*this->mRotation*this->mTranslation;
	this->mWorldView = this->mWorld*(*this->mView);
	D3DXMatrixInverse(&this->mWorldViewInverse,NULL,&this->mWorldView);

	//world_view_projection_matrix = this->mWorld * (*this->mView)*(*this->mProjection);

	if(effectName != "shadow_effect")
	{
		this->effectsList[effectName]->SetMatrix("mWorldView", &this->mWorldView);
		this->effectsList[effectName]->SetMatrix("mWorldViewInverse", &this->mWorldViewInverse);
		this->effectsList[effectName]->SetFloatArray("lightDirection",this->cLight->light_direction,4);
		//this->effectsList[effectName]->SetMatrix("matrix_world_view_projection", &world_view_projection_matrix);
	    this->effectsList[effectName]->SetTexture("texture_color",this->Texture);
	}

	this->effectsList[effectName]->SetMatrix("mWorld", &this->mWorld);
	this->effectsList[effectName]->SetMatrix("mView", this->mView);
	this->effectsList[effectName]->SetMatrix("mProjection", this->mProjection);
}

void gMeshDynamic::Load(gMeshDynamicData _meshData)
{
	this->_framesVertexData = _meshData.ptrFrameVertexData;
	this->_nTriangles = _meshData.nTriangles;
	this->_nVerteces = _meshData.nVerteces;

	this->effectsList = _meshData.effectsList;
	//this->Texture = _meshData.texturesColorList[0];

	D3DXCreateTextureFromFile(gDevice::device, "Content\\textures\\autoturret_diffuse.dds", &this->Texture);

	this->mvb = _meshData.vb;
	this->ib = _meshData.ib;

	this->tvb = _meshData.tvb;

	std::ifstream inStream;
	inStream.open("Content\\models\\Autoturret.gsm",std::ios::in | std::ios::binary);
	inStream.seekg(0, std::ios::end);
	int fileSize = inStream.tellg();
    inStream.seekg (0, std::ios::beg);
	char *fileData = new char[fileSize];
	inStream.read(fileData,fileSize);
	inStream.close();

	gStaticModelHeader *header = (gStaticModelHeader*)fileData;
	gStaticModelVertexBlock *vertexBlockData = (gStaticModelVertexBlock*)(fileData + header->vertexData.dataBlockOffset);
	short *indexBlockData = (short*)(fileData + header->indexData.dataBlockOffset);

	//memcpy(&header, fileData, sizeof(gM3Header));
	//gM3Tag *tags;
	//tags = (gM3Tag*)(fileData + header.tagsOffset);
	
	
	//FILE *file = NULL;
	//file = fopen("Content\\models\\Barracks.gsm","rb");
	//gStaticModelHeader gsmHeader;
	//fread(&gsmHeader,sizeof(gStaticModelHeader),1,file);
	//gStaticModelVertexBlock *vertexBlockData;
	//fread(&vertexBlockData
	
	//this->points = new gMd2Vertex[nVertecesM3];
	//float f_valueUV = 0.0f;
	//short s_valueUV = 0;
	//for(int i = 0; i < nVertecesM3; ++i)
	//{
	//	fread(&this->points[i].position,sizeof(D3DXVECTOR3),1,file);
		
	//	fread(&s_valueUV,sizeof(short),1,file);
	//	f_valueUV = (float)s_valueUV/2046.0f;
	//	this->points[i].textureCoordinates.x = f_valueUV;

	//	fread(&s_valueUV,sizeof(short),1,file);
	//	f_valueUV = (float)s_valueUV/2046.0f;
	//	this->points[i].textureCoordinates.y = f_valueUV;
	//}
	//fread(&nIndicesM3,sizeof(unsigned int),1,file);
	//this->indices = new short[nIndicesM3];
	//for(int i = 0; i < nIndicesM3; ++i)
	//{
	//	fread(&this->indices[i],sizeof(short),1,file);
	//}
	//fclose(file);

	this->nIndicesM3 = header->indexData.dataBlockSize;
	this->nVertecesM3 = header->vertexData.dataBlockSize;

	this->points = new gMd2Vertex[nVertecesM3];

	for( int i = 0; i < nIndicesM3; i += 3 )
	{
		D3DXVECTOR3 p1 = vertexBlockData[indexBlockData[i+0]].position;
		D3DXVECTOR3 p2 = vertexBlockData[indexBlockData[i+1]].position;
		D3DXVECTOR3 p3 = vertexBlockData[indexBlockData[i+2]].position;

		D3DXVECTOR3 v1 = p2 - p1;
	    D3DXVECTOR3 v2 = p3 - p1;
		D3DXVECTOR3 normal;
		D3DXVec3Cross(&normal,&v1,&v2);
		D3DXVec3Normalize(&normal,&normal);

		this->points[indexBlockData[i+0]].normal = normal;
		this->points[indexBlockData[i+1]].normal = normal;
		this->points[indexBlockData[i+2]].normal = normal;

		D3DXVECTOR3 tangent;

		D3DXVec3Cross(&tangent,&normal,&v2);
		D3DXVec3Normalize(&tangent,&tangent);

		this->points[indexBlockData[i+0]].tangent = tangent;
		this->points[indexBlockData[i+1]].tangent = tangent;
		this->points[indexBlockData[i+2]].tangent = tangent;

		D3DXVECTOR3 binormal;

		D3DXVec3Cross(&binormal,&tangent,&normal);
		D3DXVec3Normalize(&binormal,&binormal);

		this->points[indexBlockData[i+0]].binormal = binormal;
		this->points[indexBlockData[i+1]].binormal = binormal;
		this->points[indexBlockData[i+2]].binormal = binormal;
	}

	gDevice::device->CreateVertexBuffer(this->nVertecesM3*sizeof(gMd2Vertex),D3DUSAGE_WRITEONLY, NULL,D3DPOOL_DEFAULT,&this->m3vb,NULL);
	this->m3vb->Lock(0,this->nVertecesM3*sizeof(gMd2Vertex), (void**)&this->_m3vertexBuffer,D3DLOCK_NOSYSLOCK);
	for(int i = 0; i < this->nVertecesM3; i++)
	{
		_m3vertexBuffer[i].position = vertexBlockData[i].position;
		_m3vertexBuffer[i].textureCoordinates  = vertexBlockData[i].textCoords;
		_m3vertexBuffer[i].normal   = this->points[i].normal;
		_m3vertexBuffer[i].tangent  = this->points[i].tangent;
		_m3vertexBuffer[i].binormal = this->points[i].binormal;
	}
	this->m3vb->Unlock();

	gDevice::device->CreateIndexBuffer( this->nIndicesM3*sizeof(short),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&m3ib,NULL);
	m3ib->Lock(0, sizeof(short)*nIndicesM3, (void**)&this->_m3indexBuffer, D3DLOCK_NOSYSLOCK);
    for (int i = 0; i<nIndicesM3; i++)
		this->_m3indexBuffer[i] = indexBlockData[i];
	this->m3ib->Unlock();
}


void gMeshDynamic::Render(std::string effectName) 
{	
	//gDevice::device->SetVertexDeclaration(gCore::Md2ShaderDeclaration());
	//gDevice::device->SetIndices(this->ib);
	//gDevice::device->SetStreamSource(0,this->mvb[this->currentFrame],0,sizeof(MD2_POSITION_VERTEX));
	//d3d_device->SetStreamSource(1,md2_model->GetModelVB(frame_2),0,sizeof(MD2_POSITION_VERTEX));
	//gDevice::device->SetStreamSource(1,this->tvb,0,sizeof(MD2_TEXTURE_VERTEX));

	// draw the tweened model!
	gDevice::device->SetStreamSource( 0,this->m3vb, 0, sizeof(gMd2Vertex) );
	gDevice::device->SetIndices(this->m3ib);	
	//gDevice::device->SetRenderState( D3DRS_ZENABLE, FALSE);	
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	this->effectsList[effectName]->Begin(NULL,NULL);
    this->effectsList[effectName]->BeginPass(NULL);
	gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->nVertecesM3, 0 ,nIndicesM3/3);
	//gDevice::device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, nVertecesM3/3,&this->points[0],sizeof(gMd2Vertex));
	//gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->_nVerteces, 0, this->_nTriangles);
	//gDevice::device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, this->_nTriangles,&this->_framesVertexData[this->currentFrame].verteces[0],sizeof(gMd2Vertex));
	this->effectsList[effectName]->EndPass();
    this->effectsList[effectName]->End();
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	//gDevice::device->SetRenderState( D3DRS_ZENABLE, TRUE);	
}
