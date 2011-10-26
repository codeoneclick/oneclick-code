//
//  CSprite.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSprite.h"

#define STRINGIFY(A)  #A
#include "../Shaders/Basic.vert"
#include "../Shaders/Basic.frag"

CSprite::CSprite()
{
    
}

CSprite::~CSprite()
{
    
}

void CSprite::Load(CResourceController::SResource &_resource)
{
    m_fWidth  = _resource.vSize.x; 
    m_fHeight = _resource.vSize.y;
    
    m_vb = new CVertexBuffer(4, sizeof(CVertexBuffer::SVertexVTC), CVertexBuffer::VBD_V2FT2FC4F);
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_vb->Data());    
    data[0].s_position = Vector2d(0.0f,     0.0f);
    data[1].s_position = Vector2d(0.0f,     m_fHeight);
    data[2].s_position = Vector2d(m_fWidth, m_fHeight);
    data[3].s_position = Vector2d(m_fWidth, 0.0f);
    
    data[0].s_texcoord = Vector2d(0.0f, 0.0f);
    data[1].s_texcoord = Vector2d(0.0f, 1.0f);
    data[2].s_texcoord = Vector2d(1.0f, 1.0f);
    data[3].s_texcoord = Vector2d(1.0f, 0.0f);
    
    data[0].s_color = _resource.vColor;
    data[1].s_color = _resource.vColor;
    data[2].s_color = _resource.vColor;
    data[3].s_color = _resource.vColor;
    
    m_ib = new GLubyte[6];
    m_ib[0] = 0;
    m_ib[1] = 1;
    m_ib[2] = 2;
    m_ib[3] = 2;
    m_ib[4] = 3;
    m_ib[5] = 0;
    
    m_shader = new CShader(BasicVertexShader,BasicFragmentShader);
    m_texture = CResourceController::Instance()->TextureController()->Texture("Test.pvr");
}

void CSprite::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CSprite::Render()
{
    glEnable(GL_TEXTURE_2D);
    m_shader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_shader->SetMatrix((*m_mProjection), CShader::k_MATRIX_PROJECTION);
    m_shader->SetTexture(m_texture->Get_Handle(), "Texture");
    m_vb->Enable(m_shader->Handle());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) m_ib);
    m_vb->Disable(m_shader->Handle());
}
