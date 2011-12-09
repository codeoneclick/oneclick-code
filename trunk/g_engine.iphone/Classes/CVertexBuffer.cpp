//
//  CVertexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_VERTEX_SLOT   = "u_in_slot_vertex";
const std::string CVertexBuffer::k_TEXCOORD_SLOT = "u_in_slot_textcoord";
const std::string CVertexBuffer::k_NORMAL_SLOT   = "u_in_slot_normal";
const std::string CVertexBuffer::k_TANGENT_SLOT  = "u_in_slot_tangent";
const std::string CVertexBuffer::k_COLOR_SLOT    = "u_in_slot_color";

CVertexBuffer::CVertexBuffer(unsigned int _iNumVertexes,unsigned char _iVertexSize)
{
    m_pData = new char[_iNumVertexes * _iVertexSize];
    m_iNumVertexes = _iNumVertexes;
    m_iStride = _iVertexSize;
    m_bVRAM = false;
}

CVertexBuffer::~CVertexBuffer()
{
    SVertex* pData = static_cast<SVertex*>(m_pData);
    if(pData != NULL)
    {
        delete[] pData;
        m_pData = NULL;
    }
    
    glDeleteBuffers(1, &m_hVBHandle);
}

void CVertexBuffer::Enable(GLuint _hShaderHandle)
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLint hPositionSlot = glGetAttribLocation(_hShaderHandle, k_VERTEX_SLOT.c_str());
    GLint hTexcoordSlot = glGetAttribLocation(_hShaderHandle, k_TEXCOORD_SLOT.c_str());
    GLint hNormalSlot   = glGetAttribLocation(_hShaderHandle, k_NORMAL_SLOT.c_str());
    GLint hTangentSlot  = glGetAttribLocation(_hShaderHandle, k_TANGENT_SLOT.c_str());
    GLint hColorSlot    = glGetAttribLocation(_hShaderHandle, k_COLOR_SLOT.c_str());

    if(m_bVRAM)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_hVBHandle);
        if(hPositionSlot >= 0)
        {
            glEnableVertexAttribArray(hPositionSlot);
            glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iStride, 0);
        }
        if(hTexcoordSlot >= 0)
        {
            glEnableVertexAttribArray(hTexcoordSlot);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 3));
        }
        if(hNormalSlot >= 0)
        {
            glEnableVertexAttribArray(hNormalSlot);
            glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 5));
        }
        if(hTangentSlot >= 0)
        {
            glEnableVertexAttribArray(hTangentSlot);
            glVertexAttribPointer(hTangentSlot,  3, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 8));
        }
        if(hColorSlot >= 0)
        {
            glEnableVertexAttribArray(hColorSlot);
            glVertexAttribPointer(hColorSlot,  4, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 11));
        }
        return; 
    }
    
    SVertex* pData = static_cast<SVertex*>(m_pData);  
    
    const GLvoid* pPositionSource = &pData[0].m_vPosition.v[0];
    const GLvoid* pTexcoordSource = &pData[0].m_vTexCoord.v[0];
    const GLvoid* pNormalSource   = &pData[0].m_vNormal.v[0];
    const GLvoid* pTangentSource  = &pData[0].m_vTangent.v[0];
    const GLvoid* pColorSource    = &pData[0].m_vColor.v[0];
    
    if(hPositionSlot >= 0)
    {
        glEnableVertexAttribArray(hPositionSlot);
        glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iStride, pPositionSource);
    }
    if(hTexcoordSlot >= 0)
    {
        glEnableVertexAttribArray(hTexcoordSlot);
        glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iStride, pTexcoordSource); 
    }
    if(hNormalSlot >= 0)
    {
        glEnableVertexAttribArray(hNormalSlot);
        glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iStride, pNormalSource);
    }
    if(hTangentSlot >= 0)
    {
        glEnableVertexAttribArray(hTangentSlot);
        glVertexAttribPointer(hTangentSlot,  3, GL_FLOAT, GL_FALSE, m_iStride, pTangentSource);
    }
    if(hColorSlot >= 0)
    {
        glEnableVertexAttribArray(hColorSlot);
        glVertexAttribPointer(hColorSlot,  4, GL_FLOAT, GL_FALSE, m_iStride, pColorSource);
    }
}

void CVertexBuffer::Disable(GLuint _hShaderHandle)
{
    GLint hPositionSlot = glGetAttribLocation(_hShaderHandle, k_VERTEX_SLOT.c_str());
    GLint hTexcoordSlot = glGetAttribLocation(_hShaderHandle, k_TEXCOORD_SLOT.c_str());
    GLint hNormalSlot   = glGetAttribLocation(_hShaderHandle, k_NORMAL_SLOT.c_str());
    GLint hTangentSlot  = glGetAttribLocation(_hShaderHandle, k_TANGENT_SLOT.c_str());
    
    if(hPositionSlot >= 0)
    {
        glDisableVertexAttribArray(hPositionSlot);
    }
    if(hTexcoordSlot >= 0)
    {
        glDisableVertexAttribArray(hTexcoordSlot); 
    }
    if(hNormalSlot >= 0)
    {
        glDisableVertexAttribArray(hNormalSlot);
    }
    if(hTangentSlot >= 0)
    {
        glDisableVertexAttribArray(hTangentSlot);
    }
}

void CVertexBuffer::Commit()
{
    glGenBuffers(1, &m_hVBHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_hVBHandle);
    glBufferData(GL_ARRAY_BUFFER, m_iStride * m_iNumVertexes, m_pData, GL_STATIC_DRAW);
    m_bVRAM = true;
}


