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
    void BeginDrawWorldSpaceScene(void);
    void EndDrawWorldSpaceScene(void); 
    void DrawResult(void);
    void BeginDrawReflectionWorldSpaceScene(void);
    void EndDrawReflectionWorldSpaceScene(void);
    GLuint Get_ReflectionTextureHandle(void) { return m_pScreenSpacePostMgr->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION); }
};

#endif
