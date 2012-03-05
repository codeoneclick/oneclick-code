//
//  CCameraTarget.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCameraTarget.h"

CCameraTarget::CCameraTarget()
{
    
}

CCameraTarget::~CCameraTarget()
{
    
}

void CCameraTarget::Update()
{
    m_vLookAt = m_pTarget->Get_Position();
    m_vPosition.y = m_fHeightFromLookAt;
    m_vPosition.x = m_vLookAt.x + cos(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vPosition.z = m_vLookAt.z + sin(-m_vRotation.y) * -m_fDistanceToLookAt;
	m_mView = View( m_vPosition, m_vLookAt, m_vUp );
}

void CCameraTarget::OnScreenMove(CVector2d _vMoveDirection)
{
    
}
