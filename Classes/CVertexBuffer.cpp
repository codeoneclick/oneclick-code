//
//  CVertexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_VERTEX_SLOT = "vertex_slot";
const std::string CVertexBuffer::k_TEXCOORD_SLOT = "texcoord_slot";
const std::string CVertexBuffer::k_COLOR_SLOT = "color_slot";

CVertexBuffer::CVertexBuffer(unsigned int _vertexCount,unsigned char _elementSize, VB_DECLARATION _declaration)
{
    m_pData = new char[_vertexCount * _elementSize];
    m_declaration = _declaration;
}

CVertexBuffer::~CVertexBuffer()
{
    char *pData = static_cast<char*>(m_pData);
    if(pData != NULL)
    {
        delete[] pData;
        m_pData = NULL;
    }
}

void CVertexBuffer::Enable(GLuint _handle)
{
    glUseProgram(_handle);
    
    switch (m_declaration)
    {
        case VBD_V2FC4F:
        {
            GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
            GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
            
            SVertexVC *pData = static_cast<SVertexVC*>(m_pData);  
            
            const GLvoid *pPositionSource = &pData[0].s_position.v[0];
            const GLvoid *pColorSource = &pData[0].s_color.v[0];
            
            GLsizei stride = sizeof(SVertexVC);
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hColorSlot);
            
            glVertexAttribPointer(hPositionSlot, 2, GL_FLOAT, GL_FALSE, stride, pPositionSource);
            glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColorSource);  
        }
            break;
            
        case VBD_V2T2:
        {
            GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
            GLuint hTexcoordSlot = glGetAttribLocation(_handle, k_TEXCOORD_SLOT.c_str());
            
            SVertexVT *pData = static_cast<SVertexVT*>(m_pData);  
            
            const GLvoid *pPositionSource = &pData[0].s_position.v[0];
            const GLvoid *pTexcoordSource = &pData[0].s_texcoord.v[0];
            
            GLsizei stride = sizeof(SVertexVT);
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hTexcoordSlot);
            
            glVertexAttribPointer(hPositionSlot, 2, GL_FLOAT, GL_FALSE, stride, pPositionSource);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, stride, pTexcoordSource);  
        }
            break;
            
        case VBD_V2FT2FC4F:
        {
            GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
            GLuint hTexcoordSlot = glGetAttribLocation(_handle,k_TEXCOORD_SLOT.c_str());
            GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
            
            SVertexVTC *pData = static_cast<SVertexVTC*>(m_pData);  
            
            const GLvoid *pPositionSource = &pData[0].s_position.v[0];
            const GLvoid *pTexcoordSource = &pData[0].s_texcoord.v[0];
            const GLvoid *pColorSource = &pData[0].s_color.v[0];
            
            GLsizei stride = sizeof(SVertexVTC);
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hTexcoordSlot);
            glEnableVertexAttribArray(hColorSlot);
            
            glVertexAttribPointer(hPositionSlot, 2, GL_FLOAT, GL_FALSE, stride, pPositionSource);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, stride, pTexcoordSource);
            glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColorSource);  
        }
            break;
            
        default:
            std::cout<<"UNKOWN DECLARATION";
            break;
    }
}

void CVertexBuffer::Disable(GLuint _handle)
{
    GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
    GLuint hTexcoordSlot = glGetAttribLocation(_handle,k_TEXCOORD_SLOT.c_str());
    GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
    
    glDisableVertexAttribArray(hPositionSlot);
    glDisableVertexAttribArray(hTexcoordSlot);
    glDisableVertexAttribArray(hColorSlot);
}


