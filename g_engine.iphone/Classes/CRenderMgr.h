//
//  CRenderMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CRenderMgr_h
#define gEngine_CRenderMgr_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CSceneMgr.h"

class CRenderMgr
{
public:
    
private:
    static CRenderMgr* m_pInstance;
    GLuint m_hFrameBuffer;
    GLuint m_hRenderBuffer;
    GLuint m_hDepthBuffer;
    CSceneMgr::E_RENDER_STATE m_eState;
public:
    CRenderMgr();
    ~CRenderMgr();
    inline CSceneMgr::E_RENDER_STATE Get_State() { return m_eState; }
    static CRenderMgr* Instance();
    void Begin(CSceneMgr::E_RENDER_STATE _eState);
    void End(CSceneMgr::E_RENDER_STATE _eState);
};

#endif
