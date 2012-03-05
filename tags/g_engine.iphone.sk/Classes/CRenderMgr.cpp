//
//  CRenderMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CRenderMgr.h"

CRenderMgr::CRenderMgr(void)
{
    m_pScreenSpacePostMgr = new CScreenSpacePostMgr();
}

CRenderMgr::~CRenderMgr(void)
{
    
}

void CRenderMgr::BeginDrawWorldSpaceScene(void)
{
    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_SIMPLE);
    glClearColor( 0.99f, 0.99f, 0.99f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::EndDrawWorldSpaceScene(void)
{
    glFlush();
}

void CRenderMgr::DrawResult(void)
{
    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLOOM_EXTRACT);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomExtract();
    glFlush();
    
    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLUR);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBlur();
    glFlush();

    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLOOM_COMBINE);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomCombine();
    glFlush();
    
    m_pScreenSpacePostMgr->BindRenderBufferAsBuffer();
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostSimple();
    glFlush();
}





