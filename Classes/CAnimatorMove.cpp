//
//  CAnimatorMove.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CAnimatorMove.h"

CAnimatorMove::CAnimatorMove(void)
{
    
}

CAnimatorMove::~CAnimatorMove(void)
{
    
}

void CAnimatorMove::Init(INode *_pNode, IAnimatorDelegate *_pAnimatorDelegateOwner, const CVector3d &_vStartPosition, const CVector3d &_vEndPosition, float _fStep)
{
    m_pNode = _pNode;
    m_pAnimatorDelegateOwner = _pAnimatorDelegateOwner;
    m_vStartPosition = _vStartPosition;
    m_vEndPosition = _vEndPosition;
}

void CAnimatorMove::Start(void)
{
    m_bIsAnimated = true;
}

void CAnimatorMove::Stop(void)
{
    m_bIsAnimated = false;
}

void CAnimatorMove::Update(void)
{
    if(m_bIsAnimated == true)
    {
        
    }
}