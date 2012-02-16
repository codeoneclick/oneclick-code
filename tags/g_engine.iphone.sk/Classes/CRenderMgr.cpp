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
    glEnable( GL_CULL_FACE );
    glViewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
    CWindow::Set_Viewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
}

CRenderMgr::~CRenderMgr()
{
    
}

void CRenderMgr::Begin()
{
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::End()
{
    glFlush();
}





