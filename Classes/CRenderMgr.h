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
public:
    CRenderMgr();
    ~CRenderMgr();
    static CRenderMgr* Instance(void);
    void Begin(void);
    void End(void);
};

#endif
