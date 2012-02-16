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
#include <map>

class CShader
{
protected:
    GLuint m_hProgramHandle;
    std::map<std::string, GLint> m_lUniformHandle;
public:
    CShader(GLuint _hProgramHandle);
    ~CShader();
    
    void Enable();
    void Disable();
    
    inline GLuint Get_ProgramHandle() { return m_hProgramHandle; }
    
    void SetMatrix(const CMatrix4x4& _mValue, const std::string &_sName);
    void SetTexture(GLuint _hTextureHandle,  const std::string &_sName);
    void SetVector(const CVector3d& _vValue,  const std::string &_sName);
public:
    static const std::string k_MATRIX_WORLD;
    static const std::string k_MATRIX_VIEW;
    static const std::string k_MATRIX_PROJECTION;
    static const std::string k_MATRIX_MVP;
    static const std::string k_MATRIX_MVP_INV;
    static const std::string k_VECTOR_VIEW;
    static const std::string k_VECTOR_LIGHT;
    static const std::string k_TEXTURE_01;
    static const std::string k_TEXTURE_02;
    static const std::string k_TEXTURE_03;
    static const std::string k_TEXTURE_04;
};


#endif
