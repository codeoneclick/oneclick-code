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
#include "CWindow.h"

INode::INode()
{
    m_vScale    = glm::vec3(1.0f, 1.0f, 1.0f);
    m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    m_vTexCoordOffset = glm::vec2(0.0f, 0.0f);
    
    m_pTextures = new CTexture*[TEXTURES_MAX_COUNT];
    m_pTextures[0] = NULL;
    m_pTextures[1] = NULL;
    m_pTextures[2] = NULL;
    m_pTextures[3] = NULL;
    m_pTextures[4] = NULL;
    m_pTextures[5] = NULL;
    m_pTextures[6] = NULL;
    m_pTextures[7] = NULL;
    
    m_pShaders = new CShader*[E_RENDER_MODE_MAX];
    m_pShaders[E_RENDER_MODE_SIMPLE] = NULL;
    m_pShaders[E_RENDER_MODE_REFLECTION] = NULL;
    m_pShaders[E_RENDER_MODE_REFRACTION] = NULL;
    m_pShaders[E_RENDER_MODE_SCREEN_NORMAL_MAP] = NULL;
    
    m_pBoundingBox = NULL;
    
    m_bIsRenderModeReflectionEnable = false;
    m_bIsRenderModeRefractionEnable = false;
    m_bIsRenderModeScreenNormalEnable = false;
    m_bIsRenderModeShadowMapEnable = false;
}

INode::~INode()
{
    
}

void INode::Set_Texture(CTexture *_pTexture, int index, CTexture::E_WRAP_MODE _eWrap)
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

void INode::Set_Texture(const std::string &_sName, int index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread)
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
    std::map<std::string, std::string> lParams;
    if(_eWrap == CTexture::E_WRAP_MODE_REPEAT)
    {
        lParams["WRAP"] = "REPEAT";
    }
    else if(_eWrap == CTexture::E_WRAP_MODE_CLAMP)
    {
        lParams["WRAP"] = "CLAMP";
    }
    m_pTextures[index] = static_cast<CTexture*>(CResourceMgr::Instance()->Load(_sName, IResource::E_MGR_TEXTURE, _eThread, this, &lParams));
}

void INode::Set_Shader(INode::E_RENDER_MODE _eRenderMode, IResource::E_SHADER _eShader)
{
    m_pShaders[_eRenderMode] = CShaderComposite::Instance()->Get_Shader(_eShader);
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

void INode::Add_DelegateOwner(IDelegate *_pDelegateOwner)
{
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index] == _pDelegateOwner)
        {
            return;
        }
    }
    m_lDelegateOwners.push_back(_pDelegateOwner);
}

void INode::Remove_DelegateOwner(IDelegate *_pDelegateOwner)
{
    std::vector<IDelegate*>::iterator pBeginIterator = m_lDelegateOwners.begin();
    std::vector<IDelegate*>::iterator pEndIterator = m_lDelegateOwners.end();
    while (pBeginIterator != pEndIterator)
    {
        if((*pBeginIterator) == _pDelegateOwner)
        {
            m_lDelegateOwners.erase(pBeginIterator);
            return;
        }
        ++pBeginIterator;
    }
}

void INode::Update(void)
{
    m_mRotation = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_mRotation = glm::rotate(m_mRotation, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_mRotation = glm::rotate(m_mRotation, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    
    m_mTranslation = glm::translate(glm::mat4(1.0f), m_vPosition);
    
    m_mScale = glm::scale(glm::mat4(1.0f), m_vScale);
    
    m_mWorld = m_mTranslation * m_mRotation * m_mScale;
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Set_WorldMatrix(m_mWorld);
    }
}

void INode::Render(INode::E_RENDER_MODE _eMode)
{
    CWindow::g_iTrianglesPerFrame += m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes() / 3;
}





