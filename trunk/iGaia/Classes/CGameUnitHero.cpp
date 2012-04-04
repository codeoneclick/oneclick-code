//
//  CGameUnitHero.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameUnitHero.h"
#include "CSceneMgr.h"
#include "CWorld.h"
#include "CPathFinderAstar.h"

CGameUnitHero::CGameUnitHero(void)
{
    m_bIsMove = false;
    m_pMoveAnimator = NULL;
}

CGameUnitHero::~CGameUnitHero(void)
{
    
}

void CGameUnitHero::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("player.mdl", false, IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture("footman.pvr");
    m_pModel->Set_Scale(glm::vec3(0.01f, 0.01f, 0.01f));
    m_pModel->Set_Shader(IResource::E_SHADER_UNIT);
    m_pModel->Create_BoundingBox();
    CSceneMgr::Instance()->AddEventListener(m_pModel, CEventMgr::E_EVENT_TOUCH);
    m_pModel->Set_DelegateTarget(this);
    m_pModel->Add_Delegate(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_Delegate(this);
}

void CGameUnitHero::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    IDelegate* pDelegate = CWorld::Instance()->Get_Level();
    glm::vec3 vPosition = CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
    m_pModel->Set_Position(vPosition);
    
    if(_pDelegateOwner == pDelegate && CWorld::Instance()->Get_IsHeroUnderControl())
    {
        glm::vec3 vPosition = CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
        m_lPath.clear();
       
        if(m_pMoveAnimator != NULL)
        {
            m_pMoveAnimator->Stop();
        }
        m_lPath = CSceneMgr::Instance()->Get_NavigationMeshRef()->FindPath(m_pModel->Get_Position(), vPosition);
        for(size_t index = 0; index < m_lPath.size(); index++)
        {
            std::cout<<"[CGameUnitHero::OnTouchEvent] Path Point :"<<m_lPath[index].x<<","<<m_lPath[index].y<<"\n";
        }
        if(m_lPath.size() > 0)
        {
            glm::vec2 vModelXZPosition = glm::vec2(m_pModel->Get_Position().x,m_pModel->Get_Position().z);
            glm::vec2 vPathPart = vModelXZPosition -  m_lPath.back();
            //float fPathPartLength = vPathPart.Length();
            //float fAngle = AngleFromVectorToVector(vModelXZPosition, m_lPath.back()) + MATH_PI / 2;
            m_pModel->Set_Rotation(glm::vec3(0.0f, 0.0f, 0.0f));
            m_pMoveAnimator = CSceneMgr::Instance()->AddHeightMapMoveAnimator(m_pModel, this, vModelXZPosition, m_lPath.back(), 0.1f);
            std::cout<<"[CGameUnitHero::OnTouchEvent] Move Point :"<<m_lPath.back().x<<","<<m_lPath.back().y<<"\n";
            m_lPath.pop_back();
            m_pMoveAnimator->Start();
        }
        std::cout<<"[CGameUnitHero::OnTouchEvent] >> CLevel\n";
    }

    if(_pDelegateOwner == this)
    {
        CWorld::Instance()->Set_IsHeroUnderControl(true);
        std::cout<<"[CGameUnitHero::OnTouchEvent] >> CGameUnitHero\n";
    }
}

void CGameUnitHero::OnAnimatorDone(IAnimator* _pAnimator)
{
    std::cout<<"[CGameUnitHero::OnAnimatorDone] >> CGameUnitHero\n";
    m_pMoveAnimator = NULL;
    if(m_lPath.size() > 0)
    {
        glm::vec2 vModelXZPosition = glm::vec2(m_pModel->Get_Position().x,m_pModel->Get_Position().z);
        glm::vec2 vPathPart = vModelXZPosition -  m_lPath.back();
        //float fPathPartLength = vPathPart.Length();
        //float fAngle = AngleFromVectorToVector(vModelXZPosition, m_lPath.back()) + MATH_PI / 2;
        m_pModel->Set_Rotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_pMoveAnimator = CSceneMgr::Instance()->AddHeightMapMoveAnimator(m_pModel, this, vModelXZPosition, m_lPath.back(), 0.1f);
        std::cout<<"[CGameUnitHero::OnTouchEvent] Move Point :"<<m_lPath.back().x<<","<<m_lPath.back().y<<"\n";
        m_lPath.pop_back();
        m_pMoveAnimator->Start();
    }
}

void CGameUnitHero::OnAnimatorRemove(IAnimator *_pAnimator)
{
    std::cout<<"[CGameUnitHero::OnAnimatorRemove] >> CGameUnitHero\n";
}

void CGameUnitHero::Update(void)
{

}










