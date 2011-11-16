//
//  CShader.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShader.h"

const std::string CShader::k_MATRIX_WORLD       = "u_m_world";
const std::string CShader::k_MATRIX_VIEW        = "u_m_view";
const std::string CShader::k_MATRIX_PROJECTION  = "u_m_projection";
const std::string CShader::k_COLOR              = "u_v_color";
const std::string CShader::k_TEXTURE_01         = "u_s_texture_01";
const std::string CShader::k_TEXTURE_02         = "u_s_texture_02";
const std::string CShader::k_TEXTURE_03         = "u_s_texture_03";
const std::string CShader::k_TEXTURE_04         = "u_s_texture_04";


CShader::CShader()
{
    m_bDone = false;
}

CShader::~CShader()
{
    
}

void CShader::SetMatrix(const Matrix4x4 &_mValue,const std::string &_sName)
{
    GLint handle = glGetUniformLocation(m_pHandle, _sName.c_str());
    glUniformMatrix4fv(handle, 1, 0, &_mValue.m[0]);
}

void CShader::SetTexture(GLuint _handle, const std::string &_sName)
{ 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _handle);
    GLint handle = glGetUniformLocation(m_pHandle, _sName.c_str());
    glUniform1i(handle, 0);
}

void CShader::SetColor(const Vector4d &_vValue)
{
    GLint handle = glGetUniformLocation(m_pHandle, k_COLOR.c_str());
    glUniform4f(handle, _vValue.x, _vValue.y, _vValue.z, _vValue.w);
}
