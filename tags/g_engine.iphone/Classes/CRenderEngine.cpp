//
//  CRenderEngine.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CRenderEngine.h"
#include "CSceneEngine.h"

CRenderEngine::CRenderEngine(unsigned int _width, unsigned int _height)
{
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);
    glViewport(0, 0, _width, _height);
}

CRenderEngine::~CRenderEngine()
{
    
}

void CRenderEngine::Update(float _fTime)
{
    CSceneEngine::Instance()->Update(_fTime);
}

void CRenderEngine::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    CSceneEngine::Instance()->Render();
}