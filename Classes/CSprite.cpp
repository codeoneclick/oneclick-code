//
//  CSprite.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSprite.h"

CSprite::CSprite()
{

}

CSprite::~CSprite()
{
    std::cout<<"[CSprite] destructor().";
}

void CSprite::Load(INode::SResourceParam &_param)
{
    INode::Load(_param);
    m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE);
    m_pTexture = static_cast<CTexture*>(CResourceMgr::Instance()->Load("Untitled_default.pvr", IResourceMgr::E_TEXTURE_MGR, IResourceMgr::E_PVR_PARSER, IResourceMgr::E_BACKGROUND_THREAD));
}

void CSprite::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CSprite::Render()
{
    m_pShader->SetTexture(m_pTexture->Get_Handle(), "Texture");
    
    m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_pShader->SetMatrix((*m_mProjection), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix((*m_mView), CShader::k_MATRIX_VIEW);
    m_pVb->Enable(m_pShader->Get_pHandle());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) m_pIb);
    m_pVb->Disable(m_pShader->Get_pHandle());

    INode::Render();
}


