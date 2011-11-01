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

CCamera* CCamera::m_camera = NULL;

CCamera::CCamera()
{
    m_fWidth = 1.0f;
    m_fHeight = 1.0f;
    
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
    m_fRotation = 0.0f;
    m_vScale = Vector2d(1.0f, 1.0f);
    
    m_fWidth = CWindow::Instance()->Get_Width();
    m_fHeight = CWindow::Instance()->Get_Height();
    
    m_mProjection = new Matrix4x4();
    m_mView = new Matrix4x4();
    
    (*m_mProjection) = Orthographic(m_fWidth, m_fHeight, -1.0f, 1.0f);
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

void CCamera::Update(float _fTime)
{
    m_mRotation = Rotation(m_fRotation);
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    (*m_mView) = m_mScale * m_mRotation * m_mTranslation;
}