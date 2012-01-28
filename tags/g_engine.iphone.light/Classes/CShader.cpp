//
//  CShader.cpp
//  gEngine
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
const std::string CShader::k_COLOR              = "u_v_color";
const std::string CShader::k_TEXTURE_01         = "EXT_TEXTURE_01";
const std::string CShader::k_TEXTURE_02         = "EXT_TEXTURE_02";
const std::string CShader::k_TEXTURE_03         = "EXT_TEXTURE_03";
const std::string CShader::k_TEXTURE_04         = "EXT_TEXTURE_04";
const std::string CShader::k_VECTOR_VIEW        = "EXT_View";
const std::string CShader::k_VECTOR_LIGHT       = "EXT_Light";   

CShader::CShader()
{
    m_pHandle = 0;
    m_vHandle = 0;
    m_fHandle = 0;
}

CShader::~CShader()
{
    
}

void CShader::Commit()
{
    m_lUniformHandle[k_MATRIX_WORLD]      = glGetUniformLocation(m_pHandle, k_MATRIX_WORLD.c_str());
    m_lUniformHandle[k_MATRIX_VIEW]       = glGetUniformLocation(m_pHandle, k_MATRIX_VIEW.c_str());
    m_lUniformHandle[k_MATRIX_PROJECTION] = glGetUniformLocation(m_pHandle, k_MATRIX_PROJECTION.c_str());
    m_lUniformHandle[k_MATRIX_MVP]        = glGetUniformLocation(m_pHandle, k_MATRIX_MVP.c_str());
    m_lUniformHandle[k_MATRIX_MVP_INV]    = glGetUniformLocation(m_pHandle, k_MATRIX_MVP_INV.c_str());
    m_lUniformHandle[k_COLOR]             = glGetUniformLocation(m_pHandle, k_COLOR.c_str());
    m_lUniformHandle[k_TEXTURE_01]        = glGetUniformLocation(m_pHandle, k_TEXTURE_01.c_str());
    m_lUniformHandle[k_TEXTURE_02]        = glGetUniformLocation(m_pHandle, k_TEXTURE_02.c_str());
    m_lUniformHandle[k_TEXTURE_03]        = glGetUniformLocation(m_pHandle, k_TEXTURE_03.c_str());
    m_lUniformHandle[k_TEXTURE_04]        = glGetUniformLocation(m_pHandle, k_TEXTURE_04.c_str());
    m_lUniformHandle[k_VECTOR_VIEW]       = glGetUniformLocation(m_pHandle, k_VECTOR_VIEW.c_str());
    m_lUniformHandle[k_VECTOR_LIGHT]      = glGetUniformLocation(m_pHandle, k_VECTOR_LIGHT.c_str());
}

void CShader::SetMatrix(const Matrix4x4 &_mValue,const std::string &_sName)
{
    glUniformMatrix4fv(m_lUniformHandle[_sName], 1, 0, &_mValue.m[0]);
}

void CShader::SetTexture(GLuint _handle, const std::string &_sName)
{ 
    if(_sName == k_TEXTURE_01)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glUniform1i(m_lUniformHandle[_sName], 0);
    }
    if(_sName == k_TEXTURE_02)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glUniform1i(m_lUniformHandle[_sName], 1);
    }
    
    if(_sName == k_TEXTURE_03)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glUniform1i(m_lUniformHandle[_sName], 2);
    }

    if(_sName == k_TEXTURE_04)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _handle);
        glUniform1i(m_lUniformHandle[_sName], 3);
    }

}

void CShader::SetVector(const Vector3d &_vValue, const std::string &_sName)
{
    glUniform3f(m_lUniformHandle[_sName], _vValue.x, _vValue.y, _vValue.z);
}

void CShader::SetColor(const Vector4d &_vValue)
{
    glUniform4f(m_lUniformHandle[k_COLOR], _vValue.x, _vValue.y, _vValue.z, _vValue.w);
}




