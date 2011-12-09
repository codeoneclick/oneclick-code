//
//  CLight.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLight.h"

CLight::CLight()
{
    m_vPosition = Vector3d(0.0f, -4.0f, 0.0f);
    m_vLightAt  = Vector3d(0.0f, 0.0f, 2.0f);
    m_vRotation = Vector3d(0.0f, 0.0f, 0.0f);
}

CLight::~CLight()
{
    
}

void CLight::Update()
{
    m_vPosition.x = m_vLightAt.x + cos(-(m_vRotation.y) + 1.57f)* - 5.0f;
    m_vPosition.z = m_vLightAt.z + sin(-(m_vRotation.y) + 1.57f)* - 5.0f;
}