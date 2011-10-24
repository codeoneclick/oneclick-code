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
    m_mProjection = &CCamera::Instance()->m_mProjection;
    m_mView = &CCamera::Instance()->m_mView;
}

INode::~INode()
{
    
}

void INode::Update(float _fTime)
{
    m_mRotation = Rotation(m_fRotation);
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
    m_shader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_shader->SetMatrix((*m_mProjection), CShader::k_MATRIX_PROJECTION);
}