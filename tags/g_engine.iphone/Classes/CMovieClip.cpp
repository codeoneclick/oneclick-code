//
//  CMovieClip.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMovieClip.h"

CMovieClip::CMovieClip()
{
    m_iCurrentFrame = 0;
    m_bStop = false;
    m_pSequence = NULL;
}

CMovieClip::~CMovieClip()
{
    m_pSequence->Release();
    m_pSequence = NULL;
    std::cout<<"[CMovieClip] destructor().";
}

void CMovieClip::Load(INode::SResourceParam &_param)
{
    INode::Load(_param);
    m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE);
    m_pTexture = static_cast<CTexture*>(CResourceMgr::Instance()->Load("Untitled_default.pvr", IResourceMgr::E_TEXTURE_MGR, IResourceMgr::E_PVR_PARSER, IResourceMgr::E_BACKGROUND_THREAD));
    m_pSequence = static_cast<CSequence*>(CResourceMgr::Instance()->Load("Untitled_default.xml", IResourceMgr::E_SEQUENCE_MGR, IResourceMgr::E_SEQ_PARSER, IResourceMgr::E_BACKGROUND_THREAD));
    m_iTotalFrames = m_pSequence->Get_Frames().size();
    NextFrame();
}

void CMovieClip::GotoAndStop(unsigned int _frame)
{
    if((_frame < m_iTotalFrames))
    {
        m_iCurrentFrame = _frame;
    }
    m_bStop = true;
    NextFrame();
}

void CMovieClip::GotoAndPlay(unsigned int _frame)
{
    if((_frame < m_iTotalFrames))
    {
        m_iCurrentFrame = _frame;
    }
    m_bStop = false;
    NextFrame();
}

void CMovieClip::NextFrame()
{
    if(m_iTotalFrames == 0)
    {
        return;
    }
    
    if (m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.x != 0)
    {
        m_vFrameTexcoord[0].x = m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.x / m_pTexture->Get_Width();
    }
    else
    {
        m_vFrameTexcoord[0].x = 0.0f;
    }
    
    if(m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.y != 0)
    {
        m_vFrameTexcoord[0].y = m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.y / m_pTexture->Get_Height();
    }
    else
    {
        m_vFrameTexcoord[0].y = 0.0f;
    }
    
    if ((m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.x + m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vSize.x) != 0)
    {
        m_vFrameTexcoord[1].x = (m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.x + m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vSize.x) / m_pTexture->Get_Width();
    }
    else
    {
        m_vFrameTexcoord[1].x = 0.0f;
    }
    
    if((m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.y + m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vSize.y) != 0)
    {
        m_vFrameTexcoord[1].y = (m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vPosition.y + m_pSequence->Get_Frames()[m_iCurrentFrame]->s_vSize.y) / m_pTexture->Get_Height();
    }
    else
    {
        m_vFrameTexcoord[1].y = 0.0f;
    }
    
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_pVb->Data());    
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

void CMovieClip::Update(float _fTime)
{
    INode::Update(_fTime);
    if(!m_bStop)
    {
        NextFrame();
    }
}

void CMovieClip::Render()
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


