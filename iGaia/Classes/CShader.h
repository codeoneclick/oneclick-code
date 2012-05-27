//
//  CShader.h
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CShader_h
#define iGaia_CShader_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "stdlib.h"
#include <string>
#include <glm/glm.hpp>
#include <map>

class CShader
{
public:
    enum E_RENDER_MODE { E_RENDER_MODE_SIMPLE = 0, E_RENDER_MODE_REFLECTION, E_RENDER_MODE_REFRACTION, E_RENDER_MODE_SCREEN_NORMAL_MAP, E_RENDER_MODE_MAX };
protected:
    GLuint m_hProgramHandle;
    std::map<std::string, GLint> m_lUniformHandle;
public:
    CShader(GLuint _hProgramHandle);
    ~CShader();
    
    void Enable();
    void Disable();
    
    inline GLuint Get_ProgramHandle() { return m_hProgramHandle; }
    
    void SetMatrix(const glm::mat4x4& _mValue, const std::string& _sName);
    void SetTexture(GLuint _hTextureHandle, const std::string& _sName);
    void SetTextureCube(GLuint _hTextureHandle, const std::string& _sName);
    void SetVector2(const glm::vec2& _vValue, const std::string& _sName);
    void SetVector3(const glm::vec3& _vValue, const std::string& _sName);
    void SetVector4(const glm::vec4& _vValue, const std::string& _sName);
    void SetFloat(const float _fValue, const std::string& _sName);
    void SetCustomVector3(const glm::vec3& _vValue, const std::string& _sName);
    void SetCustomVector2(const glm::vec2& _vValue, const std::string& _sName);
    void SetCustomFloat(const float _fValue, const std::string& _sName);
public:
    static const std::string k_MATRIX_WORLD;
    static const std::string k_MATRIX_VIEW;
    static const std::string k_MATRIX_PROJECTION;
    static const std::string k_MATRIX_MVP;
    static const std::string k_MATRIX_MVP_INV;
    static const std::string k_VECTOR_VIEW;
    static const std::string k_VECTOR_LIGHT;
    static const std::string k_VECTOR_CLIP_PLANE;
    static const std::string k_TEXTURE_01;
    static const std::string k_TEXTURE_02;
    static const std::string k_TEXTURE_03;
    static const std::string k_TEXTURE_04;
    static const std::string k_TEXTURE_05;
    static const std::string k_TEXTURE_06;
    static const std::string k_TEXTURE_07;
    static const std::string k_TEXTURE_08;
    static const std::string k_TIMER;
    static const std::string k_TEXCOORD_OFFSET;
    static const std::string k_MATRIX_BIAS;
    static const std::string k_TEXTURE_CUBE;
};


#endif
