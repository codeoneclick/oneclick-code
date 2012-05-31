//
//  CBillboardEffect.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CBillboardEffect.h"

CBillboardEffect::CBillboardEffect(void)
{
    
}

CBillboardEffect::~CBillboardEffect(void)
{
    
}

void CBillboardEffect::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    
}

void CBillboardEffect::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CBillboardEffect::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CBillboardEffect::Update(void)
{
    INode::Update();
}

void CBillboardEffect::Render(CShader::E_RENDER_MODE _eMode)
{
    
}