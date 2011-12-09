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
        GLuint m_hTextureHanlde;
        int m_iWidth;
        int m_iHeight;
    }; 
protected:
    SSource* m_pSource;
public:
    CTexture();
    ~CTexture();
    inline GLuint Get_Handle() { return m_pSource->m_hTextureHanlde; }
    inline unsigned int Get_Width() { return m_pSource->m_iWidth; }
    inline unsigned int Get_Height() { return m_pSource->m_iHeight; }
    virtual void Set_Source(void* _pSource);
};

#endif
