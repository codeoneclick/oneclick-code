//
//  CRenderMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CRenderMgr_h
#define iGaia_CRenderMgr_h

#include "CScreenSpacePostMgr.h"

class CRenderMgr
{
protected:
    CScreenSpacePostMgr* m_pScreenSpacePostMgr;
public:
    CRenderMgr();
    ~CRenderMgr();
    //void BeginDrawWorldSpaceScene(void);
    //void EndDrawWorldSpaceScene(void);
    void DrawResult(void);
    void BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    
    /*void BeginDrawReflectionWorldSpaceScene(void);
    void EndDrawReflectionWorldSpaceScene(void);
    void BeginDrawEdgeDetectWorldSpaceScene(void);
    void EndDrawEdgeDetectWorldSpaceScene(void);
    void BeginDrawNormalDepthWorldSpaceScene(void);
    void EndDrawNormalDepthWorldSpaceScene(void);*/
    GLuint Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode) { return m_pScreenSpacePostMgr->Get_OffScreenTexture(_eMode); }
};

#endif
