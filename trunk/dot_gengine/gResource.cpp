#include "gResource.h"

gMeshStaticService* gResource::_meshStaticService = NULL;
bool gResource::_meshStaticServiceSingleFlag = false;

gMeshStaticService* gResource::MeshStaticService()
{
    if(!_meshStaticServiceSingleFlag)
    {
        _meshStaticService = new gMeshStaticService();
        _meshStaticServiceSingleFlag = true;
        return _meshStaticService;
    }
    else
    {
        return _meshStaticService;
    }
}

gMeshDynamicLoadService* gResource::_meshDynamicLoadService = NULL;
bool gResource::_meshDynamicLoadServiceSingleFlag = false;

gMeshDynamicLoadService* gResource::MeshDynamicLoadService()
{
    if(!_meshDynamicLoadServiceSingleFlag)
    {
        _meshDynamicLoadService = new gMeshDynamicLoadService();
        _meshDynamicLoadServiceSingleFlag = true;
        return _meshDynamicLoadService;
    }
    else
    {
        return _meshDynamicLoadService;
    }
}
