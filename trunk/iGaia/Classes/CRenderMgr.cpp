//
//  CRenderMgr.cpp
//  iGaia
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
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    glEnable(GL_DEPTH_TEST);
    glClearColor( 0.0f, 1.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::EndDrawWorldSpaceScene(void)
{
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    glDisable(GL_DEPTH_TEST);
}

void CRenderMgr::BeginDrawReflectionWorldSpaceScene(void)
{
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
    glEnable(GL_DEPTH_TEST);
    glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderMgr::EndDrawReflectionWorldSpaceScene(void)
{
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
    glDisable(GL_DEPTH_TEST);
}

void CRenderMgr::DrawResult(void)
{
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_EXTRACT);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomExtract();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_EXTRACT);
    
    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLUR);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBlur();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLUR);

    m_pScreenSpacePostMgr->EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_COMBINE);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostBloomCombine();
    m_pScreenSpacePostMgr->DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_BLOOM_COMBINE);
    
    m_pScreenSpacePostMgr->EnableScreenMode();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pScreenSpacePostMgr->Render_PostSimple();
}





