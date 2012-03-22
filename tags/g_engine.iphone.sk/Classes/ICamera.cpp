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
	m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

ICamera::~ICamera()
{

}

void ICamera::Init(int _iScreenWidth, int _iScreenHeight, float _fFovY, float _fFarPlane, float _fNearPlane)
{
    m_fAspectRatio = static_cast<float>(CWindow::Get_OffScreenWidth()) / static_cast<float>(CWindow::Get_OffScreenHeight());
    m_fFovY = _fFovY;
    m_fFarPlane = _fFarPlane;
    m_fNearPlane = _fNearPlane;
    m_mProjection = glm::perspective(m_fFovY, m_fAspectRatio, m_fNearPlane, m_fFarPlane);; 
}
