//
//  CCamera.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCamera.h"

CCamera* CCamera::m_camera = NULL;

CCamera::CCamera()
{
    
}

CCamera::~CCamera()
{
    
}

CCamera* CCamera::Instance()
{
    if(m_camera == NULL)
    {
        m_camera = new CCamera();
    }
    return m_camera;
}

void CCamera::Init(float _fWidth, float _fHeight)
{
    m_fWidth = _fWidth;
    m_fHeight = _fHeight;
    
    m_vPosition = Vector3d(0.0f,0.0f,0.0f);
	m_vRotation = Vector3d(0.0f,0.0f,0.0f);
	m_vLookAt   = Vector3d(0.0f,0.0f,0.0f);
	m_vUp       = Vector3d(0.0f,1.0f,0.0f);
	m_mProjection = Projection(45.0f, m_fWidth / m_fHeight, 0.1f, 1024.0f);    
}

void CCamera::Update(float _fTime)
{
    m_vPosition.x = m_vLookAt.x + cos(-(m_vRotation.y) + 1.57f)* - 3.0f;
    m_vPosition.z = m_vLookAt.z + sin(-(m_vRotation.y) + 1.57f)* - 3.0f;
	m_mView = View(m_vPosition,m_vLookAt,m_vUp);
}