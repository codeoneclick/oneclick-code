//
//  CGame.cpp
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CInput.h"
#include "CCamera.h"
#include "CResourceMgr.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{

}

CGame::~CGame()
{
    
}

CGame* CGame::Instance()
{
    if(m_game == NULL)
    {
        m_game = new CGame();
    }
    return m_game;
}

void CGame::Load(float _fWidth, float _fHeight)
{
    glGenRenderbuffers(1, &m_hDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _fWidth, _fHeight);
    
    glGenRenderbuffers(1, &m_hRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hRenderBuffer);
    
    glGenFramebuffers(1, &m_hFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_hRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_hDepthBuffer);
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glViewport(0, 0, _fWidth, _fHeight);
    
    CCamera::Instance()->Init(_fWidth, _fHeight);
    m_pMesh = new CModel();
    m_pMesh->Load("mesh.m3");
}

void CGame::Set_Effect(unsigned int _iIndex)
{
    m_pMesh->Set_Effect(_iIndex);
}

void CGame::Set_Model(unsigned int _iIndex)
{
    m_pMesh->Set_Model(_iIndex);
}

void CGame::Update(float _fTime)
{
    CCamera::Instance()->Update(_fTime);
    CResourceMgr::Instance()->Update();
    m_pMesh->Update(_fTime);
}

void CGame::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pMesh->Render();
    glFinish();
    //glFlush();
}

