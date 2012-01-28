//
//  CCamera.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICamera.h"
#include "CWindow.h"
#include "CInput.h"

ICamera::ICamera()
{
	m_vPosition = CVector3d(0.0f, 0.0f, 0.0f); 
    m_vRotation = CVector3d(0.0f, 0.0f, 0.0f);
    m_vUp = CVector3d(0.0f, 1.0f, 0.0f);
}

ICamera::~ICamera()
{

}

void ICamera::Init(int _iScreenWidth, int _iScreenHeight, float _fFovY, float _fFarPlane, float _fNearPlane)
{
    m_fAspectRatio = static_cast<float>(CWindow::Get_Width()) / static_cast<float>(CWindow::Get_Height());
    m_fFovY = _fFovY;
    m_fFarPlane = _fFarPlane;
    m_fNearPlane = _fNearPlane;
    m_mProjection = Projection(m_fFovY, m_fAspectRatio, m_fNearPlane, m_fFarPlane); 
}
