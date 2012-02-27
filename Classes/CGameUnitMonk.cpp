//
//  CGameUnitMonk.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameUnitMonk.h"
#include "CSceneMgr.h"
#include "CWorld.h"
#include "CPathFinder.h"

CGameUnitMonk::CGameUnitMonk(void)
{
    m_bIsMove = false;
    m_pMoveAnimator = NULL;
    m_pLandscapeRef = NULL;
}

CGameUnitMonk::~CGameUnitMonk(void)
{
    
}

void CGameUnitMonk::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("player.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture("footman.pvr");
    m_pModel->Set_Scale(CVector3d(0.01f, 0.01f, 0.01f));
    m_pModel->Set_Shader(IResource::E_SHADER_PHONG);
    m_pModel->Create_BoundingBox();
    m_pModel->Create_ColliderBox();
    CSceneMgr::Instance()->AddEventListener(m_pModel, CEventMgr::E_EVENT_TOUCH);
    m_pModel->Set_SelfDelegate(this);
    m_pModel->Add_DelegateOwner(this);
    m_pLandscapeRef = ((CLandscape*)CWorld::Instance()->Get_Level()->Get_Model());
}

void CGameUnitMonk::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    if(_pDelegateOwner == this)
    {
        CWorld::Instance()->Set_IsHeroUnderControl(false);
        std::cout<<"[CGameUnitHero::OnTouchEvent] >> CGameUnitHero\n";
    }
}

void CGameUnitMonk::OnAnimatorDone(IAnimator* _pAnimator)
{
    std::cout<<"[CGameUnitHero::OnAnimatorDone] >> CGameUnitHero\n";
    m_pMoveAnimator = NULL;
    if(m_lPath.size() > 0)
    {
        m_lPath.erase(m_lPath.begin());
    }
    if(m_lPath.size() > 0)
    {
        m_pMoveAnimator = CSceneMgr::Instance()->AddHeightMapMoveAnimator(m_pModel, this, m_pLandscapeRef->Get_HeightMapSetter(), CVector2d(m_pModel->Get_Position().x,m_pModel->Get_Position().z), m_lPath[0], 0.01f);
        m_pMoveAnimator->Start();
    }
}

void CGameUnitMonk::OnAnimatorRemove(IAnimator *_pAnimator)
{
    std::cout<<"[CGameUnitHero::OnAnimatorRemove] >> CGameUnitHero\n";
}

void CGameUnitMonk::Update(void)
{
    
}
