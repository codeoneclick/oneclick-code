#include "gGround.h"

gGround::gGround()
{

	this->flag = R_UNLOAD;

	this->_simpleVertexBuffer = NULL;
	this->_simpleIndexBuffer = NULL;
	this->_vertexBuffer = NULL;
	this->_indexBuffer = NULL;
	this->_mapHeightsReference = NULL;
	this->_mapTextureMaskReference = NULL;
	this->_mapDecorationMaskReference = NULL;

	this->_TBNInfo = NULL;

	this->_water_enable = true;
}

gGround::~gGround()
{

}

void gGround::Load(const gResourceData *resource)
{
	std::vector<std::string>::const_iterator iEffectName = resource->effectResources.begin();
	for(;iEffectName != resource->effectResources.end(); ++iEffectName)
		this->effectsList[(*iEffectName)] =  gCore::ShadersService()->Find(*iEffectName);

	this->currentEffectName = resource->currentEffectName;

	std::vector<char*>::const_iterator iTextureName = resource->textureResources.begin();
	for(;iTextureName != resource->textureResources.end(); ++iTextureName)
		this->texturesColorList.push_back(gCore::TexturesService()->Find(*iTextureName));

	int textureIndex = 1;
	char stringIndex[1024];
	std::vector<IDirect3DTexture9*>::const_iterator iTexture = this->texturesColorList.begin();
	for(;iTexture != this->texturesColorList.end(); ++iTexture)
	{
		sprintf_s(stringIndex,"Texture_%i",textureIndex);
		this->effectsList[this->currentEffectName]->SetTexture(stringIndex, *iTexture);
		textureIndex++;
	}
}

void gGround::SetMapHeights(float** mapHeightsReference)
{
	this->_mapHeightsReference = mapHeightsReference;
}

void gGround::SetTextureMask(gMapTileMask **mapTextureMaskReference)
{
	this->_mapTextureMaskReference = mapTextureMaskReference;
}

void gGround::SetDecorationMask(gMapDecoration **mapDecorationMaskReference)
{
	this->_mapDecorationMaskReference = mapDecorationMaskReference;
}

void gGround::SetMapChankIndex(unsigned int indexI, unsigned int indexJ)
{
	this->_mapChankIndexI = indexI;
	this->_mapChankIndexJ = indexJ;
}


void gGround::_CreateSimpleVertexBuffer()
{
	gMeshOptions* options = this->_CalculateLODMeshOptions();

	if(this->_simpleVertexBuffer != NULL)
	{
		delete[] this->_simpleVertexBuffer;
		this->_simpleVertexBuffer = NULL;
	}

	this->_simpleVertexBuffer = new gSimpleVertexFormat[options->nVerteces];

	unsigned int vertex_index_i = 0;
	for(unsigned int  index_i = this->_mapChankIndexI*options->groundChankSize; index_i < (this->_mapChankIndexI*options->groundChankSize + options->incGroundChankSize); ++index_i)
	{
		unsigned int vertex_index_j = 0;
		for(unsigned int index_j = this->_mapChankIndexJ*options->groundChankSize; index_j < (this->_mapChankIndexJ*options->groundChankSize + options->incGroundChankSize); ++index_j)
		{
			this->_simpleVertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.x = (float)index_i*POLYGON_SIZE*options->vertexOffset;
			this->_simpleVertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.y = this->_mapHeightsReference[index_i*options->vertexOffset][index_j*options->vertexOffset];
			this->_simpleVertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.z = (float)index_j*POLYGON_SIZE*options->vertexOffset;
			this->_simpleVertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].textureCoordinates.x = index_i/(16.0f/options->vertexOffset);
			this->_simpleVertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].textureCoordinates.y = index_j/(16.0f/options->vertexOffset);
			vertex_index_j++;
		}
		vertex_index_i++;
	}
	delete options;
}

void gGround::_CreateIndexBuffer()
{
	gMeshOptions* options = this->_CalculateLODMeshOptions();

	if(this->_simpleIndexBuffer != NULL)
	{
		delete[] this->_simpleIndexBuffer;
		this->_simpleIndexBuffer = NULL;
	}

	this->_simpleIndexBuffer = new unsigned short[options->nIndeces];

	int mainIndex = 0;
	unsigned int vertex_index_i = 0;
	for(unsigned int index_i = this->_mapChankIndexI*options->groundChankSize;index_i < (options->groundChankSize + this->_mapChankIndexI*options->groundChankSize);++index_i)
	{
		unsigned int vertex_index_j = 0;
		for(unsigned int  index_j = this->_mapChankIndexJ*options->groundChankSize;index_j < (options->groundChankSize + this->_mapChankIndexJ*options->groundChankSize);++index_j)
		{
			this->_simpleIndexBuffer[mainIndex] = vertex_index_i + vertex_index_j * options->incGroundChankSize;
			mainIndex++;
			this->_simpleIndexBuffer[mainIndex] = vertex_index_i + 1 + vertex_index_j * options->incGroundChankSize;
			mainIndex++;
			this->_simpleIndexBuffer[mainIndex] = vertex_index_i + 1 + (vertex_index_j + 1) * options->incGroundChankSize;
			mainIndex++;

			this->_simpleIndexBuffer[mainIndex] = vertex_index_i + vertex_index_j * options->incGroundChankSize;
			mainIndex++;
			this->_simpleIndexBuffer[mainIndex] = vertex_index_i + 1 + (vertex_index_j + 1) * options->incGroundChankSize;
			mainIndex++;
		    this->_simpleIndexBuffer[mainIndex] = vertex_index_i + (vertex_index_j + 1) * options->incGroundChankSize;
			mainIndex++;
			vertex_index_j++;
	    }
		vertex_index_i++;
   }

   delete options;
}


gMeshOptions* gGround::_CalculateLODMeshOptions()
{
	gMeshOptions* options = new gMeshOptions();

	switch(this->_mapChankLoadFlag)
	{
		case G_HIGH:
			options->nVerteces = HIGH_VERTECES;
			options->nIndeces = HIGH_MAP_SIZE*HIGH_MAP_SIZE*6;
			options->groundChankSize = HIGH_MAP_SIZE;
			options->incGroundChankSize = (HIGH_MAP_SIZE + 1);
			options->vertexOffset = 1;
			options->nPrimitives = HIGH_PRIMITIVES;
			break;
		case G_MIDDLE:
			options->nVerteces = MIDDLE_VERTECES;
			options->nIndeces = MIDDLE_MAP_SIZE*MIDDLE_MAP_SIZE*6;
			options->groundChankSize = MIDDLE_MAP_SIZE;
			options->incGroundChankSize = (MIDDLE_MAP_SIZE + 1);
			options->vertexOffset = 2;
			options->nPrimitives = MIDDLE_PRIMITIVES;
			break;
		case G_LOW:
			options->nVerteces = LOW_VERTECES;
			options->nIndeces = LOW_MAP_SIZE*LOW_MAP_SIZE*6;
			options->groundChankSize = LOW_MAP_SIZE;
			options->incGroundChankSize = (LOW_MAP_SIZE + 1);
			options->vertexOffset = 4;
			options->nPrimitives = LOW_PRIMITIVES;
			break;
	}

	return options;
}


void gGround::_WriteToDeviceVertexBuffer()
{
	gMeshOptions* options = this->_CalculateLODMeshOptions();

	if(vb != NULL)
	{
		vb->Release();
		vb = NULL;
	}

	gDevice::device->CreateVertexBuffer(options->nVerteces*sizeof(gVertex),D3DUSAGE_WRITEONLY,NULL,D3DPOOL_DEFAULT,&vb,NULL);
	this->vb->Lock(0,options->nVerteces*sizeof(gVertex), (void**)&this->_vertexBuffer,D3DLOCK_NOSYSLOCK);
	if(this->directXResult != S_OK) return;
	
	unsigned int vertex_index_i = 0;
	for(unsigned int index_i = this->_mapChankIndexI*options->groundChankSize; index_i < (this->_mapChankIndexI*options->groundChankSize + options->incGroundChankSize); ++index_i)
	{
		unsigned int vertex_index_j = 0;
		for(unsigned int index_j = this->_mapChankIndexJ*options->groundChankSize; index_j < (this->_mapChankIndexJ*options->groundChankSize + options->incGroundChankSize); ++index_j)
		{
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.x = (float)index_i*POLYGON_SIZE*options->vertexOffset;

			if(this->_mapHeightsReference[index_i][index_j] < 120.0f) this->_water_enable = true;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.y = this->_mapHeightsReference[index_i*options->vertexOffset][index_j*options->vertexOffset];
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].position.z = (float)index_j*POLYGON_SIZE*options->vertexOffset;
 
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].normal = this->_TBNInfo[vertex_index_i + vertex_index_j * options->incGroundChankSize]._normal;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].tangent = this->_TBNInfo[vertex_index_i + vertex_index_j * options->incGroundChankSize]._tangent;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].binormal = this->_TBNInfo[vertex_index_i + vertex_index_j * options->incGroundChankSize]._binormal;
		
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].texture.x = index_i/(32.0f/options->vertexOffset);
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].texture.y = index_j/(32.0f/options->vertexOffset);

			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_0.x  = this->_mapTextureMaskReference[index_i*options->vertexOffset][index_j*options->vertexOffset].grass;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_0.y  = this->_mapTextureMaskReference[index_i*options->vertexOffset][index_j*options->vertexOffset].sand;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_0.z  = this->_mapTextureMaskReference[index_i*options->vertexOffset][index_j*options->vertexOffset].rock;

			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_1.x = this->_mapDecorationMaskReference[index_i*options->vertexOffset][index_j*options->vertexOffset].road;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_1.y = 0.0f;
			this->_vertexBuffer[vertex_index_i + vertex_index_j * options->incGroundChankSize].layer_1.z = 0.0f;

			vertex_index_j++;
		}
		vertex_index_i++;
    }
	delete options;
	this->vb->Unlock();
	if(this->directXResult != S_OK) return;
}

void gGround::_WriteToDeviceIndexBuffer()
{
	gMeshOptions* options = this->_CalculateLODMeshOptions();

	if(ib != NULL)
	{
		ib->Release();
		ib = NULL;
	}
			
	gDevice::device->CreateIndexBuffer( options->nIndeces*sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&ib,NULL);
	ib->Lock(0, sizeof(WORD)*options->nIndeces, (void**)&this->_indexBuffer, D3DLOCK_NOSYSLOCK);
	if(this->directXResult != S_OK) return;

	unsigned int vertex_index_i = 0;
	for(unsigned int index_i = this->_mapChankIndexI*options->groundChankSize;index_i < (options->groundChankSize + this->_mapChankIndexI*options->groundChankSize);++index_i)
	{
		unsigned int vertex_index_j = 0;
		for(unsigned int index_j = this->_mapChankIndexJ*options->groundChankSize;index_j < (options->groundChankSize + this->_mapChankIndexJ*options->groundChankSize);++index_j)
		{
			*this->_indexBuffer++ = vertex_index_i + vertex_index_j * options->incGroundChankSize;
			*this->_indexBuffer++ = vertex_index_i + 1 + vertex_index_j * options->incGroundChankSize;
			*this->_indexBuffer++ = vertex_index_i + 1 + (vertex_index_j + 1) * options->incGroundChankSize;

			*this->_indexBuffer++ = vertex_index_i + vertex_index_j * options->incGroundChankSize;
			*this->_indexBuffer++ = vertex_index_i + 1 + (vertex_index_j + 1) * options->incGroundChankSize;
		    *this->_indexBuffer++ = vertex_index_i + (vertex_index_j + 1) * options->incGroundChankSize;
			vertex_index_j++;
	    }
		vertex_index_i++;
   }

   delete options;
   this->ib->Unlock();
   if(this->directXResult != S_OK) return;
}

void gGround::SetHighChankMap()
{
	this->_mapChankLoadFlag = G_HIGH;

	this->_CreateSimpleVertexBuffer();
	this->_CreateIndexBuffer();

	gMeshOptions* options = this->_CalculateLODMeshOptions();
	this->_CalculateTBN(options->nVerteces,options->nIndeces);

	this->_WriteToDeviceVertexBuffer();
	this->_WriteToDeviceIndexBuffer();
}

void gGround::SetMiddleChankMap()
{	
	this->_mapChankLoadFlag = G_MIDDLE;

	this->_CreateSimpleVertexBuffer();
	this->_CreateIndexBuffer();

	gMeshOptions* options = this->_CalculateLODMeshOptions();
	this->_CalculateTBN(options->nVerteces,options->nIndeces);

	this->_WriteToDeviceVertexBuffer();
	this->_WriteToDeviceIndexBuffer();
}


void gGround::SetLowChankMap()
{
	this->_mapChankLoadFlag = G_LOW;

	this->_CreateSimpleVertexBuffer();
	this->_CreateIndexBuffer();

	gMeshOptions* options = this->_CalculateLODMeshOptions();
	this->_CalculateTBN(options->nVerteces,options->nIndeces);

	this->_WriteToDeviceVertexBuffer();
	this->_WriteToDeviceIndexBuffer();

}

void gGround::UnloadChankMap()
{
	if(this->vb != NULL){
		this->vb->Release();
		this->vb = NULL;
	}

	if(this->ib != NULL){
		this->ib->Release();
		this->ib = NULL;
	}
}

void gGround::EditGround()
{
	this->_CreateSimpleVertexBuffer();

	gMeshOptions* options = this->_CalculateLODMeshOptions();
	this->_CalculateTBN(options->nVerteces,options->nIndeces);
	  
	this->vb->Lock(0,options->nVerteces*sizeof(gVertex), (void**)&this->_vertexBuffer,D3DLOCK_NOOVERWRITE);

	for(int index_i = 0; index_i < options->incGroundChankSize; ++index_i)
		for(int index_j = 0;index_j < options->incGroundChankSize; ++index_j)
		{
			this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].position.y = this->_mapHeightsReference[(int)(this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].position.x/POLYGON_SIZE)][(int)(this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].position.z/POLYGON_SIZE)];
			this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].normal = this->_TBNInfo[index_i + index_j * options->incGroundChankSize]._normal;
			this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].tangent = this->_TBNInfo[index_i + index_j * options->incGroundChankSize]._tangent;
			this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].binormal = this->_TBNInfo[index_i + index_j * options->incGroundChankSize]._binormal;
			if((this->_vertexBuffer[index_i + index_j * options->incGroundChankSize].position.y < 120.0f))
				this->_water_enable = true;
		}
	 this->vb->Unlock();
	 delete options;
}

void gGround::Update()
{
	//if(!this->cCamera->SphereInFrustum(this->_mapChankIndexI*640 + 320,128,this->_mapChankIndexJ*640 + 320,320)) return;
	
	this->mWorldView = this->mWorld*(*this->mView);
	D3DXMatrixInverse(&this->mWorldViewInverse,NULL,&this->mWorldView);

	float fTexOffset=0.5f+(0.5f/512.0f);
	
	D3DXMATRIX mTexScale(   0.5f,               0.0f,      0.0f,   0.0f,
                            0.0f,              -0.5f,      0.0f,   0.0f,
                            0.0f,               0.0f,      1.0f,   0.0f,
                            fTexOffset,    fTexOffset,     0.0f,   1.0f );

	D3DXMATRIX mLView,mLProj;
	D3DXMatrixLookAtLH(&mLView, &gCore::Light()->Position, &D3DXVECTOR3(0.0f,0.0f,0.0f), &D3DXVECTOR3(0,1,0));
    D3DXMatrixPerspectiveFovLH(&mLProj, D3DXToRadian(90.0f), gWindow::wndWidth /gWindow::wndHeight, 0.5f, 3000.0f);
	D3DXMATRIX mShadowMap = mLView * mLProj * mTexScale;

	this->effectsList[this->currentEffectName]->SetMatrix("mShadowMap", &mShadowMap);
	this->effectsList[this->currentEffectName]->SetTexture("ShadowMapTexture",gCore::TexturesService()->Find("softShadowMapTexture"));

	this->effectsList[this->currentEffectName]->SetMatrix("mWorld", &mWorld);
	this->effectsList[this->currentEffectName]->SetMatrix("mView", this->mView);
	this->effectsList[this->currentEffectName]->SetMatrix("mProjection", this->mProjection);
	
	this->effectsList[this->currentEffectName]->SetMatrix("mWorldView", &mWorldView);
	this->effectsList[this->currentEffectName]->SetMatrix("mWorldViewInverse", &mWorldViewInverse);

	this->effectsList[this->currentEffectName]->SetFloatArray("light_direction", this->cLight->light_direction,4);
}

void gGround::Render()
{
	gDevice::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	this->flag = flag;
			this->effectsList[this->currentEffectName]->Begin(NULL, 0);
			this->effectsList[this->currentEffectName]->BeginPass(0);
			switch(flag){
				case R_HIGH:
					gDevice::device->SetStreamSource( 0,vb, 0, sizeof(gVertex) );
					gDevice::device->SetIndices(ib);
					gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, HIGH_VERTECES, 0,HIGH_PRIMITIVES);
					break;
				case R_MIDDLE:
					gDevice::device->SetStreamSource( 0,vb, 0, sizeof(gVertex) );
					gDevice::device->SetIndices(ib);
					gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MIDDLE_VERTECES, 0, MIDDLE_PRIMITIVES);
				break;
				case R_LOW:
					gDevice::device->SetStreamSource( 0,vb, 0, sizeof(gVertex) );
					gDevice::device->SetIndices(ib);
					gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, LOW_VERTECES, 0, LOW_PRIMITIVES);
				break;
			}
			this->effectsList[this->currentEffectName]->EndPass();
			this->effectsList[this->currentEffectName]->End();
}
