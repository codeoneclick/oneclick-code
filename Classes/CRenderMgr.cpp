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
    glEnable(GL_DEPTH_TEST);
    glClearColor( 0.99f, 0.99f, 0.99f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::EndDrawWorldSpaceScene(void)
{
    m_pScreenSpacePostMgr->DiscardRenderBufferAsTexture();
    glDisable(GL_DEPTH_TEST);
}

void CRenderMgr::DrawResult(void)
{
    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLOOM_EXTRACT);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomExtract();
    m_pScreenSpacePostMgr->DiscardRenderBufferAsTexture();
    
    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLUR);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBlur();
    m_pScreenSpacePostMgr->DiscardRenderBufferAsTexture();

    m_pScreenSpacePostMgr->BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE_BLOOM_COMBINE);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomCombine();
    m_pScreenSpacePostMgr->DiscardRenderBufferAsTexture();
    
    m_pScreenSpacePostMgr->BindRenderBufferAsBuffer();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostSimple();
}





