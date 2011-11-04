//
//  CTexture.h
//  gEngine
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTexture_h
#define gEngine_CTexture_h

#include "CVector.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"
#include "IResource.h"


class CTexture : public IResource
{   
public:
    struct SSource
    {
        GLuint m_uiHanlde;
        unsigned int m_uiWidth;
        unsigned int m_uiHeight;
    }; 
protected:
    GLuint m_uiHandle;
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
public:
    CTexture();
    ~CTexture();
    inline GLuint Get_Handle() { return m_uiHandle; }
    inline unsigned int Get_Width() { return m_uiWidth; }
    inline unsigned int Get_Height() { return m_uiHeight; }
    virtual void Set_Source(void* _pSource);
};

#endif
