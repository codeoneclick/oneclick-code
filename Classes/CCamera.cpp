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
    m_fWidth = 1.0f;
    m_fHeight = 1.0f;
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

void CCamera::Init(float _width, float _height)
{
    m_fWidth = _width;
    m_fHeight = _height;
    m_mProjection = Orthographic(m_fWidth, m_fHeight, -1.0f, 1.0f);
}