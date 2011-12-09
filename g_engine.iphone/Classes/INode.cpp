//
//  INode.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "INode.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

INode::INode()
{
    m_vScale    = Vector3d(1.0f, 1.0f, 1.0f);
    m_vRotation = Vector3d(0.0f, 0.0f, 0.0f);
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
    
    m_pTextures = new CTexture*[4];
    m_pTextures[0] = NULL;
    m_pTextures[1] = NULL;
    m_pTextures[2] = NULL;
    m_pTextures[3] = NULL;
    
    m_bIntersected = false;
    
    m_pIntersectorShader = CShaderComposite::Instance()->Get_Shader(IResource::E_COLOR);
}

INode::~INode()
{
    
}

void INode::Update(float _fTime)
{
    Matrix4x4 mRotationX = RotationX(m_vRotation.x);
    Matrix4x4 mRotationY = RotationY(m_vRotation.y);
    Matrix4x4 mRotationZ = RotationZ(m_vRotation.z);
    m_mRotation = mRotationX * mRotationY * mRotationZ;
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
}

Vector3d INode::Get_Position() 
{ 
    return m_vPosition;
}

Vector3d INode::Get_Rotation() 
{ 
    return m_vRotation;
}

Vector3d INode::Get_Scale() 
{ 
    return m_vScale; 
}

CShader* INode::Get_Shader() const
{
    if(CRenderMgr::Instance()->Get_State() == CSceneMgr::E_RENDER_STATE_PICKER)
    {
        return m_pIntersectorShader;
    }
    else
    {
        return m_pShader;
    }
}

void INode::Set_IntersectorID(INode::SIntersectorID _tIntersectorID)
{
    int iNumVertexes = m_pMesh->Get_NumVertexes();
    CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(m_pMesh->Get_VB()->Get_Data());
    
    for(int i = 0; i < iNumVertexes; ++i)
    {
        pData[i].m_vColor = Vector4d(static_cast<float>(m_tIntersectorID.r) / 255.0f, static_cast<float>(m_tIntersectorID.g) / 255.0f, static_cast<float>(m_tIntersectorID.b) / 255.0f, 1.0f);
    }
}


