//
//  CCameraFree.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCameraFree.h"
#include "CInput.h"

CCameraFree::CCameraFree()
{
    m_fMoveSpeed = 0.3f;
}

CCameraFree::~CCameraFree()
{
    
}

void CCameraFree::Update()
{
    m_vPosition.y = m_fHeightFromLookAt;
    m_vPosition.x = m_vLookAt.x + cos(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vPosition.z = m_vLookAt.z + sin(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vLookAt.y = 0.0f;
	m_mView = glm::lookAt(m_vPosition, m_vLookAt, m_vUp);
}

void CCameraFree::OnScreenMove(glm::vec2 _vMoveDirection)
{
    if(_vMoveDirection.x == 0.0f && _vMoveDirection.y == 0.0f)
    {
        return;
    }
    
    if(_vMoveDirection.x < 0.0f)
    {
         MoveBackward();
    }
    if(_vMoveDirection.x > 0.0f)
    {
         MoveForward();
    }
    if(_vMoveDirection.y > 0.0f)
    {
        MoveLeft();
    }
    if(_vMoveDirection.y < 0.0f)
    {
        MoveRight();
    }
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




