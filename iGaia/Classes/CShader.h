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
    enum E_VERTEX_SLOT { E_SLOT_POSITION = 0, E_SLOT_TEXCOORD, E_SLOT_NORMAL, E_SLOT_TANGENT, E_SLOT_COLOR };
    enum E_ATTRIBUTE { E_ATTRIBUTE_MATRIX_WORLD = 0, E_ATTRIBUTE_MATRIX_VIEW, E_ATTRIBUTE_MATRIX_PROJECTION, E_ATTRIBUTE_VECTOR_CAMERA_POSITION, E_ATTRIBUTE_VECTOR_LIGHT_POSITION, E_ATTRIBUTE_VECTOR_CLIP_PLANE, E_ATTRIBUTE_FLOAT_TIMER, E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET };
    enum E_TEXTURE_SLOT { E_TEXTURE_SLOT_01 = 0, E_TEXTURE_SLOT_02, E_TEXTURE_SLOT_03, E_TEXTURE_SLOT_04, E_TEXTURE_SLOT_05, E_TEXTURE_SLOT_06, E_TEXTURE_SLOT_07, E_TEXTURE_SLOT_08 };
protected:
    static const std::string k_VERTEX_SLOT_POSITION;
    static const std::string k_VERTEX_SLOT_TEXCOORD;
    static const std::string k_VERTEX_SLOT_NORMAL;
    static const std::string k_VERTEX_SLOT_TANGENT;
    static const std::string k_VERTEX_SLOT_COLOR;
    
    static const std::string k_ATTRIBUTE_MATRIX_WORLD;
    static const std::string k_ATTRIBUTE_MATRIX_VIEW;
    static const std::string k_ATTRIBUTE_MATRIX_PROJECTION;
    static const std::string k_ATTRIBUTE_VECTOR_CAMERA_POSITION;
    static const std::string k_ATTRIBUTE_VECTOR_LIGHT_POSITION;
    static const std::string k_ATTRIBUTE_VECTOR_CLIP_PLANE;
    static const std::string k_ATTRIBUTE_FLOAT_TIMER;
    static const std::string k_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET;
    
    static const std::string k_TEXTURE_SLOT_01;
    static const std::string k_TEXTURE_SLOT_02;
    static const std::string k_TEXTURE_SLOT_03;
    static const std::string k_TEXTURE_SLOT_04;
    static const std::string k_TEXTURE_SLOT_05;
    static const std::string k_TEXTURE_SLOT_06;
    static const std::string k_TEXTURE_SLOT_07;
    static const std::string k_TEXTURE_SLOT_08;
    
    GLuint m_hHandle;
    
    std::map<E_ATTRIBUTE, GLint>    m_lAttributeContainer;
    std::map<E_VERTEX_SLOT, GLint>  m_lVertexSlotContainer;
    std::map<E_TEXTURE_SLOT, GLint> m_lTextureSlotContainer;
public:
    CShader(GLuint _hHandle);
    ~CShader(void);
    
    void Enable(void);
    void Disable(void);
    
    inline GLuint Get_Handle(void) { return m_hHandle; }
    
    inline GLint Get_VertexSlot(E_VERTEX_SLOT _eSlot) { return m_lVertexSlotContainer[_eSlot]; }
    
    void Set_Matrix(const glm::mat4x4& _mValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomMatrix(const glm::mat4x4& _mValue, const std::string& _sAttribute);
    
    void Set
    
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
};


#endif
