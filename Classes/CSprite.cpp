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
    m_vb = NULL;
    m_ib = NULL;
    m_iCurrentFrame = 0;
    m_bStop = false;
}

CSprite::~CSprite()
{
    if(m_vb != NULL)
    {
        delete m_vb;
        m_vb = NULL;
    }
    if(m_ib != NULL)
    {
        delete m_ib;
        m_ib = NULL;
    }
    std::cout<<"[CSprite] destructor().";
}

void CSprite::Load(CResourceController::SResource &_resource)
{
    m_fWidth  = _resource.s_vSize.x; 
    m_fHeight = _resource.s_vSize.y;
    
    m_vPosition = _resource.s_vPosition;
    
    m_shader = new CShader();
    CResourceController::Instance()->ShaderController()->Get_Shader("basic", m_shader);
    m_texture = new CTexture();
    CResourceController::Instance()->TextureController()->Get_Texture("Untitled_default.pvr", m_texture);
    m_pSequence = new CSequence();
    CResourceController::Instance()->DataController()->Get_Sequence("Untitled_default.xml", m_pSequence);
    m_iTotalFrames = m_pSequence->Get_Sequence().size();
    
    m_vb = new CVertexBuffer(4, sizeof(CVertexBuffer::SVertexVTC), CVertexBuffer::VBD_V2FT2FC4F);
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_vb->Data());  
    data[0].s_position = Vector3d(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
    data[1].s_position = Vector3d(-m_fWidth / 2, m_fHeight  / 2, 0.0f);
    data[2].s_position = Vector3d(m_fWidth  / 2, m_fHeight  / 2, 0.0f);
    data[3].s_position = Vector3d(m_fWidth  / 2, -m_fHeight / 2, 0.0f);
    
    if(m_iTotalFrames == 0)
    {
        data[0].s_texcoord = Vector2d(0.0f, 0.0f);
        data[1].s_texcoord = Vector2d(0.0f, 1.0f);
        data[2].s_texcoord = Vector2d(1.0f, 1.0f);
        data[3].s_texcoord = Vector2d(1.0f, 0.0f);
    }
    
    data[0].s_color = _resource.s_vColor;
    data[1].s_color = _resource.s_vColor;
    data[2].s_color = _resource.s_vColor;
    data[3].s_color = _resource.s_vColor;
    
    NextFrame();
    
    m_ib = new GLubyte[6];
    m_ib[0] = 0;
    m_ib[1] = 1;
    m_ib[2] = 2;
    m_ib[3] = 2;
    m_ib[4] = 3;
    m_ib[5] = 0;
}

void CSprite::GotoAndStop(unsigned int _frame)
{
    if((_frame < m_iTotalFrames))
    {
        m_iCurrentFrame = _frame;
    }
    m_bStop = true;
    NextFrame();
}

void CSprite::GotoAndPlay(unsigned int _frame)
{
    if((_frame < m_iTotalFrames))
    {
        m_iCurrentFrame = _frame;
    }
    m_bStop = false;
    NextFrame();
}

void CSprite::NextFrame()
{
    if(m_iTotalFrames == 0)
    {
        return;
    }
    
    if (m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.x != 0)
    {
        m_vFrameTexcoord[0].x = m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.x / m_texture->Get_Width();
    }
    else
    {
        m_vFrameTexcoord[0].x = 0.0f;
    }
    
    if(m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.y != 0)
    {
        m_vFrameTexcoord[0].y = m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.y / m_texture->Get_Height();
    }
    else
    {
        m_vFrameTexcoord[0].y = 0.0f;
    }
    
    if ((m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.x + m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vSize.x) != 0)
    {
        m_vFrameTexcoord[1].x = (m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.x + m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vSize.x) / m_texture->Get_Width();
    }
    else
    {
        m_vFrameTexcoord[1].x = 0.0f;
    }
    
    if((m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.y + m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vSize.y) != 0)
    {
        m_vFrameTexcoord[1].y = (m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vPosition.y + m_pSequence->Get_Sequence()[m_iCurrentFrame]->s_vSize.y) / m_texture->Get_Height();
    }
    else
    {
        m_vFrameTexcoord[1].y = 0.0f;
    }
    
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_vb->Data());    
    data[0].s_texcoord = Vector2d(m_vFrameTexcoord[0].x, m_vFrameTexcoord[0].y);
    data[1].s_texcoord = Vector2d(m_vFrameTexcoord[0].x, m_vFrameTexcoord[1].y);
    data[2].s_texcoord = Vector2d(m_vFrameTexcoord[1].x, m_vFrameTexcoord[1].y);
    data[3].s_texcoord = Vector2d(m_vFrameTexcoord[1].x, m_vFrameTexcoord[0].y);
    
    m_iCurrentFrame++;
    if(m_iCurrentFrame >= m_iTotalFrames)
    {
        m_iCurrentFrame = 0;
    }
}

void CSprite::Update(float _fTime)
{
    INode::Update(_fTime);
    if(!m_bStop)
    {
        NextFrame();
    }
}

void CSprite::Render()
{
    glEnable(GL_TEXTURE_2D);
    m_shader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_shader->SetMatrix((*m_mProjection), CShader::k_MATRIX_PROJECTION);
    m_shader->SetMatrix((*m_mView), CShader::k_MATRIX_VIEW);
    m_shader->SetTexture(m_texture->Get_Handle(), "Texture");
    m_vb->Enable(m_shader->Get_pHandle());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) m_ib);
    m_vb->Disable(m_shader->Get_pHandle());
}
