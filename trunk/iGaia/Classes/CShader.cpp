//
//  CShader.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShader.h"

const std::string CShader::k_MATRIX_WORLD       = "EXT_MATRIX_World";
const std::string CShader::k_MATRIX_VIEW        = "EXT_MATRIX_View";
const std::string CShader::k_MATRIX_PROJECTION  = "EXT_MATRIX_Projection";
const std::string CShader::k_MATRIX_MVP         = "EXT_MATRIX_MVP";
const std::string CShader::k_MATRIX_MVP_INV     = "EXT_MATRIX_MVP_INV";
const std::string CShader::k_TEXTURE_01         = "EXT_TEXTURE_01";
const std::string CShader::k_TEXTURE_02         = "EXT_TEXTURE_02";
const std::string CShader::k_TEXTURE_03         = "EXT_TEXTURE_03";
const std::string CShader::k_TEXTURE_04         = "EXT_TEXTURE_04";
const std::string CShader::k_TEXTURE_05         = "EXT_TEXTURE_05";
const std::string CShader::k_TEXTURE_06         = "EXT_TEXTURE_06";
const std::string CShader::k_TEXTURE_07         = "EXT_TEXTURE_07";
const std::string CShader::k_TEXTURE_08         = "EXT_TEXTURE_08";
const std::string CShader::k_VECTOR_VIEW        = "EXT_View";
const std::string CShader::k_VECTOR_LIGHT       = "EXT_Light"; 
const std::string CShader::k_VECTOR_CLIP_PLANE  = "EXT_Clip_Plane";
const std::string CShader::k_TIMER              = "EXT_Timer";
const std::string CShader::k_TEXCOORD_OFFSET    = "EXT_Texcoord_Offset";


CShader::CShader(GLuint _hProgramHandle)
{
    m_hProgramHandle = _hProgramHandle;
    m_lUniformHandle[k_MATRIX_WORLD]      = glGetUniformLocation(m_hProgramHandle, k_MATRIX_WORLD.c_str());
    m_lUniformHandle[k_MATRIX_VIEW]       = glGetUniformLocation(m_hProgramHandle, k_MATRIX_VIEW.c_str());
    m_lUniformHandle[k_MATRIX_PROJECTION] = glGetUniformLocation(m_hProgramHandle, k_MATRIX_PROJECTION.c_str());
    m_lUniformHandle[k_TEXTURE_01]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_01.c_str());
    m_lUniformHandle[k_TEXTURE_02]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_02.c_str());
    m_lUniformHandle[k_TEXTURE_03]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_03.c_str());
    m_lUniformHandle[k_TEXTURE_04]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_04.c_str());
    m_lUniformHandle[k_TEXTURE_05]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_05.c_str());
    m_lUniformHandle[k_TEXTURE_06]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_06.c_str());
    m_lUniformHandle[k_TEXTURE_07]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_07.c_str());
    m_lUniformHandle[k_TEXTURE_08]        = glGetUniformLocation(m_hProgramHandle, k_TEXTURE_08.c_str());
    m_lUniformHandle[k_VECTOR_VIEW]       = glGetUniformLocation(m_hProgramHandle, k_VECTOR_VIEW.c_str());
    m_lUniformHandle[k_VECTOR_LIGHT]      = glGetUniformLocation(m_hProgramHandle, k_VECTOR_LIGHT.c_str());
    m_lUniformHandle[k_VECTOR_CLIP_PLANE] = glGetUniformLocation(m_hProgramHandle, k_VECTOR_CLIP_PLANE.c_str());
    m_lUniformHandle[k_TIMER]             = glGetUniformLocation(m_hProgramHandle, k_TIMER.c_str());
    m_lUniformHandle[k_TEXCOORD_OFFSET]   = glGetUniformLocation(m_hProgramHandle, k_TEXCOORD_OFFSET.c_str());
}

CShader::~CShader()
{
    
}

void CShader::SetVector2(const glm::vec2 &_vValue, const std::string &_sName)
{
    GLint hHandle = m_lUniformHandle[_sName];
    glUniform2fv(hHandle, 1, &_vValue[0]);
}

void CShader::SetVector3(const glm::vec3& _vValue, const std::string& _sName)
{
    GLint hHandle = m_lUniformHandle[_sName];
    glUniform3fv(hHandle, 1, &_vValue[0]);
}

void CShader::SetVector4(const glm::vec4& _vValue, const std::string& _sName)
{
    GLint hHandle = m_lUniformHandle[_sName];
    glUniform4fv(hHandle, 1, &_vValue[0]);
}

void CShader::SetFloat(const float _fValue, const std::string& _sName)
{
    GLint hHandle = m_lUniformHandle[_sName];
    glUniform1f(hHandle, _fValue);
}

void CShader::SetMatrix(const glm::mat4x4& _mValue,const std::string& _sName)
{
    glUniformMatrix4fv(m_lUniformHandle[_sName], 1, 0, &_mValue[0][0]);
}

void CShader::SetTexture(GLuint _hTextureHandle, const std::string& _sName)
{ 
    if(_sName == k_TEXTURE_01)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 0);
        return;
    }
    if(_sName == k_TEXTURE_02)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 1);
        return;
    }
    
    if(_sName == k_TEXTURE_03)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 2);
        return;
    }

    if(_sName == k_TEXTURE_04)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 3);
        return;
    }
    
    if(_sName == k_TEXTURE_05)
    {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 4);
        return;
    }
    if(_sName == k_TEXTURE_06)
    {
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 5);
        return;
    }
    
    if(_sName == k_TEXTURE_07)
    {
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 6);
        return;
    }
    
    if(_sName == k_TEXTURE_08)
    {
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, _hTextureHandle);
        glUniform1i(m_lUniformHandle[_sName], 7);
        return;
    }
}

void CShader::Enable(void)
{
    glUseProgram(m_hProgramHandle);
}

void CShader::Disable(void)
{
    glUseProgram(NULL);
}




