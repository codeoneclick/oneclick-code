//
//  CRenderMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CRenderMgr_h
#define gEngine_CRenderMgr_h

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
};

#endif
