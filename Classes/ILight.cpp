//
//  ILight.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ILight.h"
#include "CMatrix.h"

ILight::ILight(void)
{
    m_vPosition = CVector3d(0.0f, 0.0f, 0.0f);
    m_vLightAt  = CVector3d(0.0f, 0.0f, 0.0f);
    m_vRotation = CVector3d(0.0f, 0.0f, 0.0f);
}

ILight::~ILight(void)
{
    
}

void ILight::Update(void)
{
    CMatrix4x4 mRotationX = RotationX(m_vRotation.x);
    CMatrix4x4 mRotationY = RotationY(m_vRotation.y);
    CMatrix4x4 mRotationZ = RotationZ(m_vRotation.z);
    CMatrix4x4 mRotation = mRotationX * mRotationY * mRotationZ;
    CMatrix4x4 mTranslation = Translation(m_vPosition);
    m_mWorld = mRotation * mTranslation;
}

void ILight::Render(void)
{
    
}