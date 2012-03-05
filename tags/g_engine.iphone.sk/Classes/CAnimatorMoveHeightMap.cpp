//
//  CAnimatorMoveHeightMap.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CAnimatorMoveHeightMap.h"
#include "CSceneMgr.h"

CAnimatorMoveHeightMap::CAnimatorMoveHeightMap(void)
{
    m_pHeightMapSetterRef = NULL;
    m_fStep = 0.0f;
}

CAnimatorMoveHeightMap::~CAnimatorMoveHeightMap(void)
{
    
}

void CAnimatorMoveHeightMap::Init(INode *_pNode, IAnimatorDelegate *_pAnimatorDelegateOwner, CVector2d _vStartPosition, CVector2d _vEndPosition, float _fStep)
{
    m_pNode = _pNode;
    m_fStep = _fStep;
    m_vStartPosition = _vStartPosition;
    m_vEndPosition = _vEndPosition;
    m_pAnimatorDelegateOwner = _pAnimatorDelegateOwner;
    m_pHeightMapSetterRef = CSceneMgr::Instance()->Get_HeightMapSetterRef();
}

void CAnimatorMoveHeightMap::Start(void)
{
    m_bIsAnimated = true;
}

void CAnimatorMoveHeightMap::Stop(void)
{
    m_bIsAnimated = false;
    m_pAnimatorDelegateOwner->OnAnimatorDone(this);
    m_bIsDone = true;
}

void CAnimatorMoveHeightMap::Update(void)
{
    if(m_bIsAnimated == true)
    {
        m_vStartPosition = Lerp(m_vStartPosition, m_vEndPosition, m_fStep);
        CVector3d vPosition;
        vPosition.y = m_pHeightMapSetterRef->Get_HeightValueAtPoint(m_vStartPosition.x, m_vStartPosition.y);
        vPosition.x = m_vStartPosition.x;
        vPosition.z = m_vStartPosition.y;
        m_pNode->Set_Position(vPosition);
        if(IsEqual(m_vStartPosition, m_vEndPosition, m_fStep))
        {
            Stop();
        }
    }
}

void CAnimatorMoveHeightMap::Remove(void)
{
    m_pAnimatorDelegateOwner->OnAnimatorRemove(this);
}