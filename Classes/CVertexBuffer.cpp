//
//  CVertexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_VERTEX_SLOT   = "IN_SLOT_Position";
const std::string CVertexBuffer::k_TEXCOORD_SLOT = "IN_SLOT_TexCoord";
const std::string CVertexBuffer::k_NORMAL_SLOT   = "IN_SLOT_Normal";

CVertexBuffer::CVertexBuffer(unsigned int _vertexCount,unsigned char _elementSize)
{
    m_pData = new char[_vertexCount * _elementSize];
    m_count = _vertexCount;
    m_stride = _elementSize;
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
    
    GLint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
    GLint hTexcoordSlot = glGetAttribLocation(_handle, k_TEXCOORD_SLOT.c_str());
    GLint hNormalSlot   = glGetAttribLocation(_handle, k_NORMAL_SLOT.c_str());
    
    if(m_vram)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        if(hPositionSlot >= 0)
        {
            glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, 0);
            glEnableVertexAttribArray(hPositionSlot);
        }
        if(hTexcoordSlot >= 0)
        {
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 3));
            glEnableVertexAttribArray(hTexcoordSlot);
        }
        if(hNormalSlot >= 0)
        {
            glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_stride, (GLvoid*) (sizeof(float) * 5));
            glEnableVertexAttribArray(hNormalSlot);
        }
        return; 
    }
    
    SVertex *pData = static_cast<SVertex*>(m_pData);  
    
    const GLvoid *pPositionSource = &pData[0].m_vPosition.v[0];
    const GLvoid *pTexcoordSource = &pData[0].m_vTexCoord.v[0];
    const GLvoid *pNormalSource   = &pData[0].m_vNormal.v[0];
    
    glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_stride, pPositionSource);
    glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_stride, pTexcoordSource); 
    glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_stride, pNormalSource); 
}

void CVertexBuffer::Disable(GLuint _handle)
{
    GLuint hPositionSlot = glGetAttribLocation(_handle, k_VERTEX_SLOT.c_str());
    GLuint hTexcoordSlot = glGetAttribLocation(_handle, k_TEXCOORD_SLOT.c_str());
    GLuint hNormalSlot   = glGetAttribLocation(_handle, k_NORMAL_SLOT.c_str());
    
    glDisableVertexAttribArray(hPositionSlot);
    glDisableVertexAttribArray(hTexcoordSlot);
    glDisableVertexAttribArray(hNormalSlot);
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void CVertexBuffer::Commit()
{
    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, m_stride * m_count, m_pData, GL_STATIC_DRAW);
    m_vram = true;
}


