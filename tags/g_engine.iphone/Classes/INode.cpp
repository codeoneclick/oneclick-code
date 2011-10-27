//
//  INode.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "INode.h"

INode::INode()
{
    m_mProjection = CCamera::Instance()->Projection();
    m_mView = CCamera::Instance()->View();
    
    m_vScale = Vector2d(1.0f,1.0f);
    m_fRotation = 0.0f;
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
}

INode::~INode()
{
    std::cout<<"[INode] destructor().";
}

void INode::Update(float _fTime)
{
    m_mRotation = Rotation(m_fRotation);
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
}