//
//  CCamera.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCamera.h"
#include "CWindow.h"
#include "CInput.h"

CCamera* CCamera::m_pIntsance = NULL;

CCamera::CCamera()
{
    m_vPosition = Vector3d(0.0f,2.0f,0.0f);
	m_vRotation = Vector3d(0.0f,1.57f,0.0f);
	m_vLookAt   = Vector3d(0.0f,0.0f,2.0f);
	m_vUp       = Vector3d(0.0f,1.0f,0.0f);
    
    m_fFOV = 45.0f;
    m_fNearPlane = 0.1f;
    m_fFarPlane = 1024.0f;
    m_fDistanceToLookAt = 2.5f;
    m_fHeightFromLookAt = 1.5f;
    m_fMoveSpeed = 0.1f;
    
	m_mProjection = Projection(m_fFOV, static_cast<float>(CWindow::Get_Width()) / static_cast<float>(CWindow::Get_Height()), m_fNearPlane, m_fFarPlane);    
}

CCamera::~CCamera()
{

}

CCamera* CCamera::Instance()
{
    if(m_pIntsance == NULL)
    {
        m_pIntsance = new CCamera();
    }
    return m_pIntsance;
}

void CCamera::Update(float _fTime)
{
    m_vPosition.y = m_fHeightFromLookAt;
    m_vPosition.x = m_vLookAt.x + cos(-m_vRotation.y) * -m_fDistanceToLookAt;
    m_vPosition.z = m_vLookAt.z + sin(-m_vRotation.y) * -m_fDistanceToLookAt;
	m_mView = View(m_vPosition,m_vLookAt,m_vUp);
    
    Vector2d vMove = CInput::Instance()->Get_Move();
    if(vMove.x == 0.0f && vMove.y == 0.0f)
    {
        return;
    }
    
    if(vMove.x > 0.0f)
    {
        MoveForward();
       
    }
    if(vMove.x < 0.0f)
    {
        MoveBackward(); 
    }
    if(vMove.y > 0.0f)
    {
        MoveLeft();
    }
    if(vMove.y < 0.0f)
    {
        MoveRight();
    }
}

void CCamera::MoveForward()
{
    m_vLookAt.x += sinf(m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z += cosf(m_vRotation.y) * m_fMoveSpeed;
}
 
void CCamera::MoveBackward()
{
    m_vLookAt.x  -= sinf(m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z  -= cosf(m_vRotation.y) * m_fMoveSpeed;
}
 
void CCamera::MoveRight()
{
    m_vLookAt.x += cosf(-m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z += sinf(-m_vRotation.y) * m_fMoveSpeed;
}
 
void CCamera::MoveLeft()
{
    m_vLookAt.x -= cosf(-m_vRotation.y) * m_fMoveSpeed;
    m_vLookAt.z -= sinf(-m_vRotation.y) * m_fMoveSpeed;
}



