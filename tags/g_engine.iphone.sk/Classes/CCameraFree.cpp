//
//  CCameraFree.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCameraFree.h"
#include "CInput.h"

CCameraFree::CCameraFree()
{
    
}

CCameraFree::~CCameraFree()
{
    
}

void CCameraFree::Update()
{
    m_vPosition.y = m_fHeightFromLookAt;
    m_vPosition.x = m_vLookAt.x + cos(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vPosition.z = m_vLookAt.z + sin(-m_vRotation.y) * -m_fDistanceToLookAt;
	m_mView = View( m_vPosition, m_vLookAt, m_vUp );
}

void CCameraFree::MoveForward()
{
    m_vLookAt.x += sinf(m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z += cosf(m_vRotation.y) * m_fMoveSpeed;
}

void CCameraFree::MoveBackward()
{
    m_vLookAt.x  -= sinf(m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z  -= cosf(m_vRotation.y) * m_fMoveSpeed;
}

void CCameraFree::MoveRight()
{
    m_vLookAt.x += cosf(-m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z += sinf(-m_vRotation.y) * m_fMoveSpeed;
}

void CCameraFree::MoveLeft()
{
    m_vLookAt.x -= cosf(-m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z -= sinf(-m_vRotation.y) * m_fMoveSpeed;
}
