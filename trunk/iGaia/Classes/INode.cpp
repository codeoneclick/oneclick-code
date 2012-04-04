//
//  INode.cpp
//  iGaia
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

INode::INode()
{
    m_vScale    = glm::vec3(1.0f, 1.0f, 1.0f);
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_pTextures = new CTexture*[TEXTURES_MAX_COUNT];
    m_pTextures[0] = NULL;
    m_pTextures[1] = NULL;
    m_pTextures[2] = NULL;
    m_pTextures[3] = NULL;
    m_pTextures[4] = NULL;
    m_pTextures[5] = NULL;
    m_pTextures[6] = NULL;
    m_pTextures[7] = NULL;
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    
    m_pBoundingBox = NULL;
    
    m_pLight = NULL;
    
    m_bIsForReflection = false;
    m_bIsForRefraction = false;
    m_bIsEdgeDetect = false;
    m_bIsNormalDepth = false;
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
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
    }
}

void INode::Create_BoundingBox()
{
    if(m_pBoundingBox != NULL)
    {
        delete m_pBoundingBox;
        m_pBoundingBox = NULL;
    }

    m_pBoundingBox = new CBoundingBox(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
}

void INode::Remove_BoundingBox()
{
    delete m_pBoundingBox;
    m_pBoundingBox = NULL;
}

void INode::Add_Delegate(IDelegate *_pDelegate)
{
    for(size_t index = 0; index< m_lDelegates.size(); index++)
    {
        if(m_lDelegates[index] == _pDelegate)
        {
            return;
        }
    }
    m_lDelegates.push_back(_pDelegate);
}

void INode::Remove_Delegate(IDelegate *_pDelegate)
{
    std::vector<IDelegate*>::iterator pBeginIterator = m_lDelegates.begin();
    std::vector<IDelegate*>::iterator pEndIterator = m_lDelegates.end();
    while (pBeginIterator != pEndIterator)
    {
        if((*pBeginIterator) == _pDelegate)
        {
            m_lDelegates.erase(pBeginIterator);
            return;
        }
        ++pBeginIterator;
    }
}

void INode::Update()
{
    glm::mat4x4 mRotationX = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4x4 mRotationY = glm::rotate(mRotationX, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4x4 mRotationZ = glm::rotate(mRotationY, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    m_mRotation = mRotationZ;
    
    m_mTranslation = glm::translate(glm::mat4(1.0f), m_vPosition);
    
    m_mScale = glm::scale(glm::mat4(1.0f), m_vScale);
    
    m_mWorld = m_mTranslation * m_mRotation * m_mScale;
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
        m_pBoundingBox->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
    }
}


