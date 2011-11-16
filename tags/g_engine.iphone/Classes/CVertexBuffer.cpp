//
//  CVertexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_VERTEX_SLOT = "u_in_slot_vertex";
const std::string CVertexBuffer::k_TEXCOORD_SLOT = "u_in_slot_textcoord";
const std::string CVertexBuffer::k_COLOR_SLOT = "color_slot";

CVertexBuffer::CVertexBuffer(unsigned int _vertexCount,unsigned char _elementSize, VB_DECLARATION _declaration)
{
    m_pData = new char[_vertexCount * _elementSize];
    m_declaration = _declaration;
    m_count = _vertexCount;
    switch (m_declaration)
    {
        case VBD_V2FC4F:
        {
            m_stride = sizeof(SVertexVC);
        }
            break;
            
        case VBD_V2T2:
        {
            m_stride = sizeof(SVertexVT);
        }
            break;
        case VBD_V2FT2FC4F:
        {
            m_stride = sizeof(SVertexVTC);
        }
            break;
        default:
            std::cout<<"UNKOWN DECLARATION";
            break;
    }
    m_vram = false;
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
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    if(m_vram)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        
        switch (m_declaration)
        {
            case VBD_V2FC4F:
            {
                GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
                GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
                glEnableVertexAttribArray(hPositionSlot);
                glEnableVertexAttribArray(hColorSlot);
                glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, 0);
                glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 3));
            }
                break;     
            case VBD_V2T2:
            {
                GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
                GLuint hTexcoordSlot = glGetAttribLocation(_handle, k_TEXCOORD_SLOT.c_str());
                glEnableVertexAttribArray(hPositionSlot);
                glEnableVertexAttribArray(hTexcoordSlot);
                glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, 0);
                glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 3));
            }
                break;
            case VBD_V2FT2FC4F:
            {
                GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
                GLuint hTexcoordSlot = glGetAttribLocation(_handle,k_TEXCOORD_SLOT.c_str());
                GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
                glEnableVertexAttribArray(hPositionSlot);
                glEnableVertexAttribArray(hTexcoordSlot);
                glEnableVertexAttribArray(hColorSlot);
                glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, 0);
                glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 3));
                glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 5));
            }
                break;
            default:
                std::cout<<"UNKOWN DECLARATION";
                break;
        }
        return; 
    }
    
    switch (m_declaration)
    {
        case VBD_V2FC4F:
        {
            GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
            GLuint hColorSlot = glGetAttribLocation(_handle, k_COLOR_SLOT.c_str());
            
            SVertexVC *pData = static_cast<SVertexVC*>(m_pData);  
            
            const GLvoid *pPositionSource = &pData[0].s_position.v[0];
            const GLvoid *pColorSource = &pData[0].s_color.v[0];
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hColorSlot);
            
            glVertexAttribPointer(hPositionSlot, 2, GL_FLOAT, GL_FALSE, m_stride, pPositionSource);
            glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, m_stride, pColorSource);  
        }
            break;
            
        case VBD_V2T2:
        {
            GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
            GLuint hTexcoordSlot = glGetAttribLocation(_handle, k_TEXCOORD_SLOT.c_str());
            
            SVertexVT *pData = static_cast<SVertexVT*>(m_pData);  
            
            const GLvoid *pPositionSource = &pData[0].s_position.v[0];
            const GLvoid *pTexcoordSource = &pData[0].s_texcoord.v[0];
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hTexcoordSlot);
            
            glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, pPositionSource);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, pTexcoordSource);  
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
            
            glEnableVertexAttribArray(hPositionSlot);
            glEnableVertexAttribArray(hTexcoordSlot);
            glEnableVertexAttribArray(hColorSlot);
            
            glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, pPositionSource);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, pTexcoordSource);
            glVertexAttribPointer(hColorSlot, 4, GL_FLOAT, GL_FALSE, m_stride, pColorSource);  
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
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void CVertexBuffer::Commit()
{
    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, m_stride * m_count, m_pData, GL_STATIC_DRAW);
    m_vram = true;
}


