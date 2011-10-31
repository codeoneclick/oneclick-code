//
//  CShader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CShader_h
#define gEngine_CShader_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "stdlib.h"
#include <string>
#include "CMatrix.h"

class CShader
{
private:
    GLuint m_pHandle;
    GLuint m_vHandle;
    GLuint m_fHandle;
    bool   m_bDone;
public:
    CShader();
    ~CShader();
    inline GLuint Get_pHandle() { return m_pHandle; }
    inline void   Set_pHandle(GLuint _handle) { m_pHandle = _handle; }
    inline void   Set_vHandle(GLuint _handle) { m_vHandle = _handle; }
    inline void   Set_fHandle(GLuint _handle) { m_fHandle = _handle; }
    inline bool   Get_Done() { return m_bDone;}
    inline void   Set_Done(bool _value) { m_bDone = _value; }
    
    void SetMatrix(const Matrix4x4 &_mValue, const std::string &_sName);
    void SetTexture(GLuint _handle, const std::string &_sName);
    
public:
    static const std::string k_MATRIX_WORLD;
    static const std::string k_MATRIX_VIEW;
    static const std::string k_MATRIX_PROJECTION;
};


#endif
