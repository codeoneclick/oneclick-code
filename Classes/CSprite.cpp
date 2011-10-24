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
    
}

void CSprite::Load(std::string _name, float _width, float _height)
{
    m_fWidth  = _width; 
    m_fHeight = _height;
    
    m_vb = new CVertexBuffer(4, sizeof(CVertexBuffer::SVertexVC), CVertexBuffer::VBD_V2FC4F);
    CVertexBuffer::SVertexVC *data = static_cast<CVertexBuffer::SVertexVC*>(m_vb->Source());    
    data[0].s_position = Vector2d(0.0f,     0.0f);
    data[1].s_position = Vector2d(0.0f,     m_fHeight);
    data[2].s_position = Vector2d(m_fWidth, m_fHeight);
    data[3].s_position = Vector2d(m_fWidth, 0.0f);
    
    data[0].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    data[1].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    data[2].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    data[3].s_color = Vector4d(0.0f,1.0f,0.0f,1.0f);
    
    m_ib = new GLubyte[6];
    m_ib[0] = 0;
    m_ib[1] = 1;
    m_ib[2] = 2;
    m_ib[3] = 2;
    m_ib[4] = 3;
    m_ib[5] = 0;
}

void CSprite::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CSprite::Render()
{
    m_vb->Enable(m_shader->Handle());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) m_ib);
    m_vb->Disable(m_shader->Handle());
}
