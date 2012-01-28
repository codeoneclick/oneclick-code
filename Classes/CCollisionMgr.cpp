//
//  CCollisionMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCollisionMgr.h"
#include "CBatchMgr.h"
#include "CEventMgr.h"
#include "CInput.h"

CCollisionMgr* CCollisionMgr::m_pInstance = NULL;

CCollisionMgr::CCollisionMgr()
{
    m_tLastColliderID.r = 0;
    m_tLastColliderID.g = 0;
    m_tLastColliderID.b = 0;
    
    m_iHexColliderID = 0;
    
    m_vTouch3DPoint = CVector3d(0.0f, 0.0f, 0.0f);
    
    m_bIsTouch = false;
}

CCollisionMgr::~CCollisionMgr()
{
    
}

CCollisionMgr* CCollisionMgr::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CCollisionMgr();
    }
    return m_pInstance;
}

unsigned int CCollisionMgr::RgbToHex(unsigned char _r, unsigned char _g, unsigned char _b)
{
    unsigned int iHex = ((_r & 255) << 16) + ((_g & 255) << 8) + _b;
    return iHex;
}

void CCollisionMgr::Create_Collider(ICollider* _pCollider)
{   
    if(m_tLastColliderID.r < 255)
    {
        m_tLastColliderID.r++;
    }
    else if(m_tLastColliderID.g < 255)
    {
        m_tLastColliderID.g++;
        m_tLastColliderID.r = 0;
    }
    else if(m_tLastColliderID.b < 255)
    {
        m_tLastColliderID.b++;
        m_tLastColliderID.r = 0;
        m_tLastColliderID.g = 0;
    }
    
    m_tLastColliderID.m_iHex = RgbToHex(m_tLastColliderID.r, m_tLastColliderID.g, m_tLastColliderID.b);
    _pCollider->Set_ColliredID(m_tLastColliderID);
    m_lContainer[m_tLastColliderID.m_iHex] = _pCollider;
}

void CCollisionMgr::Remove_Collider(ICollider* _pCollider)
{
    
}

void CCollisionMgr::Update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    std::map<unsigned int,ICollider*>::iterator pBIterator = m_lContainer.begin();
    std::map<unsigned int,ICollider*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        ICollider* pCollider = (*pBIterator).second;
        pCollider->Render();
        if(m_bIsTouch == true)
        {
            m_iHexColliderID = 0;
            pCollider->Set_TouchCollided(false);
        }
        ++pBIterator;
    }
    
    CBatchMgr::Instance()->RenderColliderBatch();
    
    if(m_bIsTouch == true)
    {
        ICollider::SColliderID tTouchColliderID;
        glReadPixels(static_cast<GLint>(m_vTouch2DPoint.x), static_cast<GLint>(m_vTouch2DPoint.y), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &tTouchColliderID.v);
        unsigned int iHexColliderID = RgbToHex(tTouchColliderID.r, tTouchColliderID.g, tTouchColliderID.b);
        std::map<unsigned int,ICollider*>::iterator pIterator = m_lContainer.find(iHexColliderID);
        if(pIterator != m_lContainer.end())
        {
            ICollider* pCollider = (*pIterator).second;
            pCollider->Set_TouchCollided(true);
            CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);
            m_iHexColliderID = iHexColliderID;
            glFlush();
            return;
        }
        m_bIsTouch = false;
    }
    glFlush();
}








