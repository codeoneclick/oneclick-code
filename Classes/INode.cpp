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
#include "CResourceMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CColliderBox.h"
#include "CColliderQuad.h"

INode::INode()
{
    m_vScale    = CVector3d(1.0f, 1.0f, 1.0f);
    m_vRotation = CVector3d(0.0f, 0.0f, 0.0f);
    m_vPosition = CVector3d(0.0f, 0.0f, 0.0f);
    
    m_pTextures = new CTexture*[TEXTURES_MAX_COUNT];
    m_pTextures[0] = NULL;
    m_pTextures[1] = NULL;
    m_pTextures[2] = NULL;
    m_pTextures[3] = NULL;
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    
    m_pBoundingBox = NULL;
    m_pCollider = NULL;
    
    m_pLight = NULL;
    
    m_bIsBatching = false;
}

INode::~INode()
{
    
}

void INode::Set_Texture(CTexture *_pTexture, int index)
{
    if( index >= TEXTURES_MAX_COUNT )
    {
        std::cout<<"[INode] Critical index for the texture.";
        return;
    }
    if( m_pTextures[index] != NULL )
    {
       // TODO: unload
    }
       
    m_pTextures[index] = _pTexture;
}

void INode::Set_Texture(const std::string &_sName, int index, IResource::E_THREAD _eThread)
{
    if( index >= TEXTURES_MAX_COUNT )
    {
        std::cout<<"[INode] Critical index for the texture.";
        return;
    }
    if( m_pTextures[index] != NULL )
    {
        // TODO: unload
    }
    
    m_pTextures[index] = static_cast<CTexture*>(CResourceMgr::Instance()->Load(_sName, IResource::E_MGR_TEXTURE, _eThread));;  
}

void INode::Set_Shader(IResource::E_SHADER _eShader)
{
    m_pShader = CShaderComposite::Instance()->Get_Shader(_eShader);
}

void INode::Create_BoundingBox()
{
    m_pBoundingBox = new CBoundingBox(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
}

void INode::Remove_BoundingBox()
{
    delete m_pBoundingBox;
    m_pBoundingBox = NULL;
}

void INode::Create_ColliderBox()
{
    if(m_pCollider != NULL)
    {
        delete m_pCollider;
        m_pCollider = NULL;
    }
    
    m_pCollider = new CColliderBox(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
    CCollisionMgr::Instance()->Create_Collider(m_pCollider);
}

void INode::Create_ColliderQuad()
{
    if(m_pCollider != NULL)
    {
        delete m_pCollider;
        m_pCollider = NULL;
    }
    
    m_pCollider = new CColliderQuad(CVector3d(), CVector3d(), CVector3d(), CVector3d());
    CCollisionMgr::Instance()->Create_Collider(m_pCollider);
}

void INode::Remove_Collider()
{
    delete m_pCollider;
    m_pCollider = NULL;
}

void INode::Update()
{
    CMatrix4x4 mRotationX = RotationX(m_vRotation.x);
    CMatrix4x4 mRotationY = RotationY(m_vRotation.y);
    CMatrix4x4 mRotationZ = RotationZ(m_vRotation.z);
    m_mRotation = mRotationX * mRotationY * mRotationZ;
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
        m_pBoundingBox->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
    }
    
    if(m_pCollider != NULL)
    {
        m_pCollider->Set_WorldMatrix(m_mWorld);
        m_pCollider->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
    }
}


