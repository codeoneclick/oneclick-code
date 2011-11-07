//
//  CShape.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShape.h"

CShape::CShape()
{
    
}

CShape::~CShape()
{
    
}

void CShape::Load(INode::SResourceParam &_param)
{
    INode::Load(_param);
    m_pShader = CResource::Instance()->Get_Shader(CShaderController::E_COLOR);
}

void CShape::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CShape::Render()
{
    m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_pShader->SetMatrix((*m_mProjection), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix((*m_mView), CShader::k_MATRIX_VIEW);
    m_pVb->Enable(m_pShader->Get_pHandle());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) m_pIb);
    m_pVb->Disable(m_pShader->Get_pHandle());
    
    INode::Render();
}