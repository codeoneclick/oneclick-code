//
//  CRenderMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CRenderMgr.h"
#include "CInput.h"
#include "CWindow.h"

CRenderMgr* CRenderMgr::m_pInstance = NULL;

CRenderMgr::CRenderMgr()
{
    glGenRenderbuffers(1, &m_hDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, CWindow::Get_Width(), CWindow::Get_Height());
    
    glGenRenderbuffers(1, &m_hRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hRenderBuffer);
    
    glGenFramebuffers(1, &m_hFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_hRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_hDepthBuffer);
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glViewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
}

CRenderMgr::~CRenderMgr()
{
    
}

CRenderMgr* CRenderMgr::Instance()
{
    if( m_pInstance == NULL)
    {
        m_pInstance = new CRenderMgr();
    }
    
    return m_pInstance;
}

void CRenderMgr::Begin(CSceneMgr::E_RENDER_STATE _eState)
{
    switch (_eState) 
    {
        case CSceneMgr::E_RENDER_STATE_SCREEN:
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_eState = _eState;
            break;
        case CSceneMgr::E_RENDER_STATE_PICKER:
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_eState = _eState;
            break;
        default:
            break;
    }
}

void CRenderMgr::End(CSceneMgr::E_RENDER_STATE _eState)
{
    switch (_eState) 
    {
        case CSceneMgr::E_RENDER_STATE_SCREEN:
        {
            glFlush();
        }
            break;
        case CSceneMgr::E_RENDER_STATE_PICKER:
        {
            if(CInput::Instance()->Get_Click())
            {
                INode::SIntersectorID tIntersectorID;
                Vector2d vMousePosition = CInput::Instance()->Get_Coord();
                glReadPixels(static_cast<int>(vMousePosition.x), static_cast<int>(vMousePosition.y), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &tIntersectorID); 
                CSceneMgr::Instance()->Set_IntersectorID(tIntersectorID);
            }
            glFlush();
        }
            break;
        default:
            break;
    }
}





