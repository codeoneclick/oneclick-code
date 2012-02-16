//
//  CGameUnitHero.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameUnitHero.h"
#include "CSceneMgr.h"
#include "CWorld.h"

CGameUnitHero::CGameUnitHero(void)
{
    
}

CGameUnitHero::~CGameUnitHero(void)
{
    
}

void CGameUnitHero::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("footman.gmesh", false, IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture("footman.pvr");
    m_pModel->Set_Scale(CVector3d(0.01f, 0.01f, 0.01f));
    m_pModel->Set_Shader(IResource::E_SHADER_PHONG);
    m_pModel->Create_BoundingBox();
    m_pModel->Create_ColliderBox();
    CSceneMgr::Instance()->AddEventListener(m_pModel, CEventMgr::E_EVENT_TOUCH);
    m_pModel->Set_SelfDelegate(this);
    m_pModel->Add_DelegateOwner(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_DelegateOwner(this);
}

void CGameUnitHero::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    IDelegate* pDelegate = CWorld::Instance()->Get_Level();
    if(_pDelegateOwner == pDelegate)
    {
        CVector3d vPosition = CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
        m_pModel->Set_Position(vPosition);
        std::cout<<"[CGameUnitHero::OnTouchEvent] >> CLevel\n";
    }

    if(_pDelegateOwner == this)
    {
        std::cout<<"[CGameUnitHero::OnTouchEvent] >> CGameUnitHero\n";
    }
}

void CGameUnitHero::Update(void)
{
    
}