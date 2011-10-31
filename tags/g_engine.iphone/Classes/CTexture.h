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

class CTexture
{   
protected:
    GLuint m_handle;
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    bool   m_bDone;
public:
    CTexture();
    ~CTexture();
    inline GLuint Get_Handle() { return m_handle; }
    inline void   Set_Handle(GLuint _handle) { m_handle = _handle; }
    inline bool   Get_Done() { return m_bDone;}
    inline void   Set_Done(bool _value) { m_bDone = _value; }
    inline unsigned int Get_Width() { return m_uiWidth; }
    inline void Set_Width(unsigned int _uiWidth) { m_uiWidth = _uiWidth; }
    inline unsigned int Get_Height() { return m_uiHeight; }
    inline void Set_Height(unsigned int _uiHeight) { m_uiHeight = _uiHeight; }
};

#endif
