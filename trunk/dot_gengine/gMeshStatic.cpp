#include "gMeshStatic.h"

gMeshStatic::gMeshStatic()
{
}

void gMeshStatic::Update(std::string effectName)
{
	D3DXMatrixTranslation(&this->mTranslation, this->vPosition.x,this->vPosition.y, this->vPosition.z);
	D3DXMatrixScaling(&this->mScale,10.0f,10.0f,10.0f);
	this->mWorld = this->mScale*this->mTranslation;
	this->mWorldView = this->mWorld*(*this->mView);
	D3DXMatrixInverse(&this->mWorldViewInverse,NULL,&this->mWorldView);

	this->effectsList[effectName]->SetMatrix("mWorld", &this->mWorld);
	this->effectsList[effectName]->SetMatrix("mView", this->mView);
	this->effectsList[effectName]->SetMatrix("mProjection", this->mProjection);
	if(effectName != "shadow_effect")
	{
		this->effectsList[effectName]->SetMatrix("mWorldView", &this->mWorldView);
		this->effectsList[effectName]->SetMatrix("mWorldViewInverse", &this->mWorldViewInverse);
		this->effectsList[effectName]->SetFloatArray("lightDirection",this->cLight->light_direction,4);
	}
}

void gMeshStatic::Render(std::string effectName)
{
	gDevice::device->SetVertexDeclaration(gCore::ShaderDeclaration());
	for(int i = 0; i < this->nTextures; ++i)
	{
		if(effectName != "shadow_effect")
		{
			this->effectsList[effectName]->SetTexture("textureColor",this->texturesColorList[i]);
			this->effectsList[effectName]->SetTexture("textureNormal",this->texturesNormalList[i]);
		}
		this->effectsList[effectName]->Begin(NULL,NULL);
		this->effectsList[effectName]->BeginPass(NULL);
   
		gDevice::device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->nVertices, this->indexInfo[i].startIndex ,this->indexInfo[i].countPrimitive);
	
		this->effectsList[effectName]->EndPass();
		this->effectsList[effectName]->End();
	}
}

void gMeshStatic::Load(gMeshStaticData _meshData)
{
	this->ib = _meshData.ib;
	this->vb = _meshData.vb;

	this->indexInfo = _meshData.indexInfo;

	this->nIndices = _meshData.nIndices;
	this->nTextures = _meshData.nTextures;
	this->nVertices = _meshData.nVertices;

	this->texturesColorList = _meshData.texturesColorList;
	this->texturesNormalList = _meshData.texturesNormalList;

	this->effectsList = _meshData.effectsList;
}
