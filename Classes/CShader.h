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
    GLuint m_pHandle;
    GLuint m_vHandle;
    GLuint m_fHandle;
    std::map<std::string, GLuint> m_lUniformHandle;
public:
    CShader();
    ~CShader();
    void Commit();
    
    inline GLuint Get_pHandle() { return m_pHandle; }
    inline void   Set_pHandle(GLuint _handle) { m_pHandle = _handle; }
    inline void   Set_vHandle(GLuint _handle) { m_vHandle = _handle; }
    inline void   Set_fHandle(GLuint _handle) { m_fHandle = _handle; }
    
    void SetMatrix(const Matrix4x4 &_mValue, const std::string &_sName);
    void SetTexture(GLuint _handle, const std::string &_sName);
    void SetVector(const Vector3d &_vValue, const std::string &_sName);
    void SetColor(const Vector4d &_vValue);
public:
    static const std::string k_MATRIX_WORLD;
    static const std::string k_MATRIX_VIEW;
    static const std::string k_MATRIX_PROJECTION;
    static const std::string k_MATRIX_MVP;
    static const std::string k_MATRIX_MVP_INV;
    static const std::string k_VECTOR_VIEW;
    static const std::string k_VECTOR_LIGHT;
    static const std::string k_COLOR;
    static const std::string k_TEXTURE_01;
    static const std::string k_TEXTURE_02;
    static const std::string k_TEXTURE_03;
    static const std::string k_TEXTURE_04;
};


#endif
