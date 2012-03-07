//
//  ICollider.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICollider.h"
#include "CShaderComposite.h"

ICollider::ICollider()
{
    m_mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
}

ICollider::~ICollider()
{
    if(m_pMesh != NULL)
    {
        delete m_pMesh;
        m_pMesh = NULL;
    }
}

void ICollider::Set_ColliredID(ICollider::SColliderID _tColliderID)
{
    /*m_tColliderID = _tColliderID;
    CVertexBuffer::SVertexVC* pData = static_cast<CVertexBuffer::SVertexVC*>(m_pMesh->Get_VB()->Get_Data());
    for(unsigned int i = 0; i < m_pMesh->Get_NumVertexes(); i++)
    {
        pData[i].m_cColor = CColor4(_tColliderID.r, _tColliderID.g, _tColliderID.b, 255);
    }*/
}