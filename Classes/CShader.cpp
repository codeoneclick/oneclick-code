//
//  CShader.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShader.h"

const std::string CShader::k_MATRIX_WORLD       = "mWorld";
const std::string CShader::k_MATRIX_VIEW        = "mView";
const std::string CShader::k_MATRIX_PROJECTION  = "mProjection";

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
