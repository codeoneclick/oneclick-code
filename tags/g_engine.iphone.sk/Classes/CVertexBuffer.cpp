//
//  CVertexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBuffer.h"

const std::string CVertexBuffer::k_SLOT_POSITION   = "IN_SLOT_Position";
const std::string CVertexBuffer::k_SLOT_TEXCOORD = "IN_SLOT_TexCoord";
const std::string CVertexBuffer::k_SLOT_NORMAL   = "IN_SLOT_Normal";
const std::string CVertexBuffer::k_SLOT_COLOR   = "IN_SLOT_Color";

CVertexBuffer::CVertexBuffer(unsigned int _iNumVertexes,unsigned char _iVertexSize, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode)
{
    m_pData = new char[_iNumVertexes * _iVertexSize];
    m_iNumVertexes = _iNumVertexes;
    m_iStride = _iVertexSize;
    m_bVRAM = false;
    m_eMode = _eMode;
}

CVertexBuffer::~CVertexBuffer()
{
    if(m_pData != NULL)
    {
        delete[] static_cast<char*>(m_pData);
        m_pData = NULL;
    }
    
    glDeleteBuffers(1, &m_hVBHandle);
}

void CVertexBuffer::Enable(GLuint _hShaderHandle)
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLint hPositionSlot = glGetAttribLocation(_hShaderHandle, k_SLOT_POSITION.c_str());
    GLint hTexcoordSlot = glGetAttribLocation(_hShaderHandle, k_SLOT_TEXCOORD.c_str());
    GLint hNormalSlot   = glGetAttribLocation(_hShaderHandle, k_SLOT_NORMAL.c_str());
    GLint hColorSlot    = glGetAttribLocation(_hShaderHandle, k_SLOT_COLOR.c_str());

    if(m_bVRAM)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_hVBHandle);
        if(hPositionSlot >= 0)
        {
            glEnableVertexAttribArray(hPositionSlot);
            glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iStride, 0);
        }
        if(hTexcoordSlot >= 0 && m_eMode == E_VERTEX_BUFFER_MODE_VTN)
        {
            glEnableVertexAttribArray(hTexcoordSlot);
            glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 3));
        }
        if(hNormalSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VTN || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
        {
            glEnableVertexAttribArray(hNormalSlot);
            glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 5));
        }
        if(hColorSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VC || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
        {
            glEnableVertexAttribArray(hColorSlot);
            glVertexAttribPointer(hColorSlot,  4, GL_FLOAT, GL_FALSE, m_iStride, (GLvoid*) (sizeof(float) * 11));
        }
        return; 
    }
    
    const GLvoid* pPositionSource = NULL;
    const GLvoid* pTexcoordSource = NULL;
    const GLvoid* pNormalSource   = NULL;
    const GLvoid* pColorSource    = NULL;

    if(m_eMode == E_VERTEX_BUFFER_MODE_VTN)
    {
        SVertexVTN* pData = static_cast<SVertexVTN*>(m_pData); 
        pPositionSource = &pData[0].m_vPosition.v[0];
        pTexcoordSource = &pData[0].m_vTexCoord.v[0];
        pNormalSource   = &pData[0].m_vNormal.v[0];
    }
    else if(m_eMode == E_VERTEX_BUFFER_MODE_VC)
    {
        SVertexVC* pData = static_cast<SVertexVC*>(m_pData); 
        pPositionSource = &pData[0].m_vPosition.v[0];
        pColorSource = &pData[0].m_cColor.v[0];
    }
        
    if(hPositionSlot >= 0)
    {
        glVertexAttribPointer(hPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iStride, pPositionSource);
        glEnableVertexAttribArray(hPositionSlot);
    }
    if(hTexcoordSlot >= 0 && m_eMode == E_VERTEX_BUFFER_MODE_VTN)
    {
        glVertexAttribPointer(hTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iStride, pTexcoordSource);
        glEnableVertexAttribArray(hTexcoordSlot); 
    }
    if(hNormalSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VTN || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
    {
        glVertexAttribPointer(hNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iStride, pNormalSource);
        glEnableVertexAttribArray(hNormalSlot);
    }
    if(hColorSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VC || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
    {
        glVertexAttribPointer(hColorSlot,  4, GL_UNSIGNED_BYTE, GL_TRUE, m_iStride, pColorSource);
        glEnableVertexAttribArray(hColorSlot);
    }
}

void CVertexBuffer::Disable(GLuint _hShaderHandle)
{
    GLint hPositionSlot = glGetAttribLocation(_hShaderHandle, k_SLOT_POSITION.c_str());
    GLint hTexcoordSlot = glGetAttribLocation(_hShaderHandle, k_SLOT_TEXCOORD.c_str());
    GLint hNormalSlot   = glGetAttribLocation(_hShaderHandle, k_SLOT_NORMAL.c_str());
    GLint hColorSlot    = glGetAttribLocation(_hShaderHandle, k_SLOT_COLOR.c_str());
    
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
    if(hColorSlot >= 0)
    {
        glDisableVertexAttribArray(hColorSlot);
    }
}

void CVertexBuffer::Commit()
{
    glGenBuffers(1, &m_hVBHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_hVBHandle);
    glBufferData(GL_ARRAY_BUFFER, m_iStride * m_iNumVertexes, m_pData, GL_STATIC_DRAW);
    m_bVRAM = true;
}


