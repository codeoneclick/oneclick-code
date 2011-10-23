#include "gLevel.h"

gLevel::gLevel()
{
	this->_playerPtr = NULL;
}

void gLevel::Load()
{
	this->AddStaticMesh("model_02")->vPosition = D3DXVECTOR3(340,165,1220);
	this->AddStaticMesh("model_02")->vPosition = D3DXVECTOR3(1620,165,985);
	this->AddStaticMesh("model_02")->vPosition = D3DXVECTOR3(1380,180,1540);
	this->AddStaticMesh("model_03")->vPosition = D3DXVECTOR3(859,170,718);
	this->AddStaticMesh("model_03")->vPosition = D3DXVECTOR3(859,170,718);
	this->AddStaticMesh("model_01")->vPosition = D3DXVECTOR3(295,110,632);
	this->AddStaticMesh("model_02")->vPosition = D3DXVECTOR3(1540,170,2240);

	this->AddDynamicMesh("knight",true);

	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			this->AddDynamicMesh("zombi",false)->vPosition = D3DXVECTOR3(i*300 + 200,this->_mapsService->Height(i*300.0f + 200.0f,j*300.0f + 200.0f),j*300 +200);
}

gMeshStatic* gLevel::AddStaticMesh(std::string meshName)
{
	std::vector<gMeshStatic*> *_meshList = this->_FindMeshStaticResourcePtr(meshName);
	if(_meshList == NULL) _meshList = new std::vector<gMeshStatic*>;
	(*_meshList).push_back(new gMeshStatic());
	(*_meshList)[_meshList->size() - 1]->Load(gResource::MeshStaticService()->Find(meshName)->GetMeshData()); 
	this->_meshStaticList[meshName] = (*_meshList);
	return (*_meshList)[_meshList->size() - 1];
}

std::vector<gMeshStatic*> *gLevel::_FindMeshStaticResourcePtr(std::string value)
{
	std::map<std::string,std::vector<gMeshStatic*>>::iterator meshListIterator;
	meshListIterator = this->_meshStaticList.find(value);
	if(meshListIterator != this->_meshStaticList.end())
		return &meshListIterator->second;
	else
		return NULL;
}

gMeshDynamic* gLevel::AddDynamicMesh(std::string meshName, bool isPlayer)
{
	std::vector<gMeshDynamic*> *_meshList = this->_FindMeshDynamicResourcePtr(meshName);
	if(_meshList == NULL) _meshList = new std::vector<gMeshDynamic*>;
	(*_meshList).push_back(new gMeshDynamic());
	(*_meshList)[_meshList->size() - 1]->Load(gResource::MeshDynamicLoadService()->Find(meshName)->GetMeshData()); 
	this->_meshDynamicList[meshName] = (*_meshList);
	if(isPlayer)
		this->_playerPtr = (*_meshList)[_meshList->size() - 1];
	return (*_meshList)[_meshList->size() - 1];
}


std::vector<gMeshDynamic*> *gLevel::_FindMeshDynamicResourcePtr(std::string value)
{
	std::map<std::string,std::vector<gMeshDynamic*>>::iterator meshListIterator;
	meshListIterator = this->_meshDynamicList.find(value);
	if(meshListIterator != this->_meshDynamicList.end())
		return &meshListIterator->second;
	else
		return NULL;
}

void gLevel::Update()
{
}

void gLevel::Render(std::string effectName)
{
	std::map<std::string,std::vector<gMeshStatic*>>::iterator meshListIterator = this->_meshStaticList.begin();
	std::vector<gMeshStatic*>::iterator meshIterator;
	while(meshListIterator != this->_meshStaticList.end())
	{
		gDevice::device->SetStreamSource( 0,gResource::MeshStaticService()->Find(meshListIterator->first)->GetMeshData().vb, 0, sizeof(gVertex) );
		gDevice::device->SetIndices(gResource::MeshStaticService()->Find(meshListIterator->first)->GetMeshData().ib);
		meshIterator = meshListIterator->second.begin();
		while(meshIterator != meshListIterator->second.end())
		{
			(*meshIterator)->Update(effectName);
			(*meshIterator)->Render(effectName);
			++meshIterator;
		}
		++meshListIterator;
	}

	if(effectName == "shadow_effect") return;

	std::map<std::string,std::vector<gMeshDynamic*>>::iterator meshDynamicListIterator = this->_meshDynamicList.begin();
	std::vector<gMeshDynamic*>::iterator meshDynamicIterator;
	while(meshDynamicListIterator != this->_meshDynamicList.end())
	{
		meshDynamicIterator = meshDynamicListIterator->second.begin();
		while(meshDynamicIterator != meshDynamicListIterator->second.end())
		{
			(*meshDynamicIterator)->Update(effectName);
			(*meshDynamicIterator)->Render(effectName);
			++meshDynamicIterator;
		}
		++meshDynamicListIterator;
	}

	//if(this->_playerPtr != NULL)
	//{
	//	this->_playerPtr->Update(effectName);
	//	this->_playerPtr->Render(effectName);
	//}
}