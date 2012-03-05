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
    m_iSize = _iVertexSize;
    m_bIsInVRAM = false;
    m_eMode = _eMode;
}

CVertexBuffer::~CVertexBuffer()
{
    if(m_pData != NULL)
    {
        delete[] static_cast<char*>(m_pData);
        m_pData = NULL;
    }
    
    glDeleteBuffers(1, &m_iHandle);
}

void CVertexBuffer::Set_ShaderRef(GLuint _iShaderHandler)
{
    m_iShaderHandle = _iShaderHandler;
    m_iPositionSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_POSITION.c_str());
    m_iTexcoordSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_TEXCOORD.c_str());
    m_iNormalSlot   = glGetAttribLocation(m_iShaderHandle, k_SLOT_NORMAL.c_str());
    m_iColorSlot    = glGetAttribLocation(m_iShaderHandle, k_SLOT_COLOR.c_str());
}

void CVertexBuffer::Enable()
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
   
    if(m_bIsInVRAM)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        if(m_iPositionSlot >= 0)
        {
            glEnableVertexAttribArray(m_iPositionSlot);
            glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, 0);
        }
        if(m_iTexcoordSlot >= 0 && m_eMode == E_VERTEX_BUFFER_MODE_VTN)
        {
            glEnableVertexAttribArray(m_iTexcoordSlot);
            glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*) (sizeof(float) * 3));
        }
        if(m_iNormalSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VTN || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
        {
            glEnableVertexAttribArray(m_iNormalSlot);
            glVertexAttribPointer(m_iNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*) (sizeof(float) * 5));
        }
        if(m_iColorSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VC || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
        {
            glEnableVertexAttribArray(m_iColorSlot);
            glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, (GLvoid*) (sizeof(float) * 11));
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
        
    if(m_iPositionSlot >= 0) 
    {
        glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, pPositionSource);
        glEnableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0 && m_eMode == E_VERTEX_BUFFER_MODE_VTN)
    {
        glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, pTexcoordSource);
        glEnableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iNormalSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VTN || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
    {
        glVertexAttribPointer(m_iNormalSlot,   3, GL_FLOAT, GL_FALSE, m_iSize, pNormalSource);
        glEnableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iColorSlot >= 0 && (m_eMode == E_VERTEX_BUFFER_MODE_VC || m_eMode == E_VERTEX_BUFFER_MODE_VNC))
    {
        glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_TRUE, m_iSize, pColorSource);
        glEnableVertexAttribArray(m_iColorSlot);
    }
}

void CVertexBuffer::Disable()
{
    if(m_iPositionSlot >= 0)
    {
        glDisableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0)
    {
        glDisableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iNormalSlot >= 0)
    {
        glDisableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iColorSlot >= 0)
    {
        glDisableVertexAttribArray(m_iColorSlot);
    }
}

void CVertexBuffer::Commit()
{
    glGenBuffers(1, &m_iHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
    glBufferData(GL_ARRAY_BUFFER, m_iSize * m_iNumVertexes, m_pData, GL_STATIC_DRAW);
    m_bIsInVRAM = true;
}


