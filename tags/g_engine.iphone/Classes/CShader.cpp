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

CShader::CShader(const char *_vSource, const char *_fSource)
{
    m_vHandle = Build(_vSource, GL_VERTEX_SHADER);
    m_fHandle = Build(_fSource, GL_FRAGMENT_SHADER);
    
    m_pHandle = glCreateProgram();
    glAttachShader(m_pHandle, m_vHandle);
    glAttachShader(m_pHandle, m_fHandle);
    glLinkProgram(m_pHandle);
    
    GLint success;
    glGetProgramiv(m_pHandle, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) 
    {
        GLchar messages[256];
        glGetProgramInfoLog(m_pHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }
}

CShader::~CShader()
{
    
}

GLuint CShader::Build(const char *_source, GLenum _shader)
{
    GLuint handle = glCreateShader(_shader);
    glShaderSource(handle, 1, &_source, 0);
    glCompileShader(handle);
    
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    
    if (success == GL_FALSE) 
    {
        GLchar messages[256];
        glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        handle = 0;
    }
   
    return handle;
}

void CShader::SetMatrix(const Matrix4x4 &_mValue,const std::string &_sName)
{
    GLint handle = glGetUniformLocation(m_pHandle, _sName.c_str());
    glUniformMatrix4fv(handle, 1, 0, &_mValue.m[0]);
}
