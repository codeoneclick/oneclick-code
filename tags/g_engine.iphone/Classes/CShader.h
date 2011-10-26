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
    GLuint Build(const char* _source, GLenum _shader);
public:
    CShader(const char *_vSource, const char*_fSource);
    ~CShader();
    GLuint Handle() { return m_pHandle; }
    
    void SetMatrix(const Matrix4x4 &_mValue, const std::string &_sName);
    void SetTexture(GLuint _handle, const std::string &_sName);
    
public:
    static const std::string k_MATRIX_WORLD;
    static const std::string k_MATRIX_VIEW;
    static const std::string k_MATRIX_PROJECTION;
};


#endif
