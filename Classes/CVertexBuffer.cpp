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
const std::string CVertexBuffer::k_SLOT_TANGENT = "IN_SLOT_Tangent";
const std::string CVertexBuffer::k_SLOT_COLOR   = "IN_SLOT_Color";


CVertexBuffer::CVertexBuffer(unsigned int _iNumVertexes)
{
    m_iNumVertexes = _iNumVertexes;
    m_iSize = 32;
    m_bIsInVRAM = false;
    
    m_pSource = new char[m_iNumVertexes * m_iSize];
    
    m_pData.m_pPositionData = NULL;
    m_pData.m_pTexCoordData = NULL;
    m_pData.m_pNormalData   = NULL;
    m_pData.m_pTangentData  = NULL;
    m_pData.m_pColorData    = NULL;
}

CVertexBuffer::~CVertexBuffer()
{
    glDeleteBuffers(1, &m_iHandle);
}

void CVertexBuffer::Set_ShaderRef(GLuint _iShaderHandler)
{
    m_iShaderHandle = _iShaderHandler;
    m_iPositionSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_POSITION.c_str());
    m_iTexcoordSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_TEXCOORD.c_str());
    m_iNormalSlot   = glGetAttribLocation(m_iShaderHandle, k_SLOT_NORMAL.c_str());
    m_iTangentSlot  = glGetAttribLocation(m_iShaderHandle, k_SLOT_TANGENT.c_str());
    m_iColorSlot    = glGetAttribLocation(m_iShaderHandle, k_SLOT_COLOR.c_str());
}

CVector3d* CVertexBuffer::CreateOrReUse_PositionData(void)
{
    if(m_pData.m_pPositionData == NULL)
    {
        m_pData.m_pPositionData = new CVector3d[m_iNumVertexes];
    }
    return m_pData.m_pPositionData;
}

CVector2d* CVertexBuffer::CreateOrReUse_TexCoordData(void)
{
    if(m_pData.m_pTexCoordData == NULL)
    {
        m_pData.m_pTexCoordData = new CVector2d[m_iNumVertexes];
    }
    return m_pData.m_pTexCoordData;
}

CByteVector3d* CVertexBuffer::CreateOrReUse_NormalData(void)
{
    if(m_pData.m_pNormalData == NULL)
    {
        m_pData.m_pNormalData = new CByteVector3d[m_iNumVertexes];
    }
    return m_pData.m_pNormalData;
}

CByteVector3d* CVertexBuffer::CreateOrReUse_TangentData(void)
{
    if(m_pData.m_pTangentData == NULL)
    {
        m_pData.m_pTangentData = new CByteVector3d[m_iNumVertexes];
    }
    return m_pData.m_pTangentData;
}

CColor4* CVertexBuffer::CreateOrReUse_ColorData(void)
{
    if(m_pData.m_pColorData == NULL)
    {
        m_pData.m_pColorData = new CColor4[m_iNumVertexes];
    }
    return m_pData.m_pColorData;
}

void CVertexBuffer::CommitToRAM(void)
{
    unsigned char iBytesPerVertex = 0;
    if(m_pData.m_pPositionData != NULL)
    {
        iBytesPerVertex += 12;
    }
    if(m_pData.m_pTexCoordData != NULL)
    {
        iBytesPerVertex += 8;
    }
    if(m_pData.m_pNormalData != NULL)
    {
        iBytesPerVertex += 3;
    }
    if(m_pData.m_pTangentData != NULL)
    {
        iBytesPerVertex += 3;
    }
    if(m_pData.m_pColorData != NULL)
    {
        iBytesPerVertex += 4;
    }
    
    unsigned int iPtrOffset = 0;
    unsigned int iPaddingSize = m_iSize - iBytesPerVertex;

    for(unsigned int i = 0; i < m_iNumVertexes; ++i)
    {
        if(m_pData.m_pPositionData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pPositionData[i].v[0], sizeof(CVector3d));
            iPtrOffset += sizeof(CVector3d);
        }
        if(m_pData.m_pTexCoordData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pTexCoordData[i].v[0], sizeof(CVector2d));
            iPtrOffset += sizeof(CVector2d);
        }
        if(m_pData.m_pNormalData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pNormalData[i].v[0], sizeof(CByteVector3d));
            iPtrOffset += sizeof(CByteVector3d);
        }
        if(m_pData.m_pTangentData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pTangentData[i].v[0], sizeof(CByteVector3d));
            iPtrOffset += sizeof(CByteVector3d);
        }
        if(m_pData.m_pColorData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pColorData[i].v[0], sizeof(CColor4));
            iPtrOffset += sizeof(CColor4);
        }
        
        iPtrOffset += iPaddingSize;
    }
}

void CVertexBuffer::Enable(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    if(m_bIsInVRAM)
    {
        unsigned char iBytesPerVertex = 0;
        glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
        if(m_iPositionSlot >= 0 && m_pData.m_pPositionData != NULL)
        {
            glEnableVertexAttribArray(m_iPositionSlot);
            glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 12;
        }
        if(m_iTexcoordSlot >= 0 && m_pData.m_pTexCoordData != NULL /*m_eMode == E_VERTEX_BUFFER_MODE_VTN*/)
        {
            glEnableVertexAttribArray(m_iTexcoordSlot);
            glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 8;
        }
        if(m_iNormalSlot >= 0 && m_pData.m_pNormalData != NULL/*m_eMode == E_VERTEX_BUFFER_MODE_VTN*/)
        {
            glEnableVertexAttribArray(m_iNormalSlot);
            glVertexAttribPointer(m_iNormalSlot,   3, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 3;
        }
        if(m_iTangentSlot >= 0 && m_pData.m_pTangentData != NULL /*m_eMode == E_VERTEX_BUFFER_MODE_VTN*/)
        {
            glEnableVertexAttribArray(m_iTangentSlot);
            glVertexAttribPointer(m_iTangentSlot,   3, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 3;
        }
        if(m_iColorSlot >= 0 && m_pData.m_pColorData != NULL /*m_eMode == E_VERTEX_BUFFER_MODE_VC*/)
        {
            glEnableVertexAttribArray(m_iColorSlot);
            glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 4;
        }
        return; 
    }
    
    const GLvoid* pPositionSource = NULL;
    const GLvoid* pTexcoordSource = NULL;
    const GLvoid* pNormalSource   = NULL;
    const GLvoid* pTangentSource  = NULL;
    const GLvoid* pColorSource    = NULL;
    
    unsigned int iBytesPerVertex = 0;
    if(m_pData.m_pPositionData != NULL)
    {
        pPositionSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(CVector3d);
    }
    if(m_pData.m_pTexCoordData != NULL)
    {
        pTexcoordSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(CVector2d);
    }
    if(m_pData.m_pNormalData != NULL)
    {
        pNormalSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(CByteVector3d);
    }
    if(m_pData.m_pTangentData != NULL)
    {
        pTangentSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(CByteVector3d);
    }
    if(m_pData.m_pColorData != NULL)
    {
        pColorSource = m_pSource + iBytesPerVertex;
    }

    if(m_iPositionSlot >= 0 && m_pData.m_pPositionData != NULL) 
    {
        glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, pPositionSource);
        glEnableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0 && m_pData.m_pTexCoordData != NULL)
    {
        glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, pTexcoordSource);
        glEnableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iNormalSlot >= 0 && m_pData.m_pNormalData != NULL)
    {
        glVertexAttribPointer(m_iNormalSlot,   3, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pNormalSource);
        glEnableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iTangentSlot >= 0 && m_pData.m_pTangentData != NULL)
    {
        glVertexAttribPointer(m_iTangentSlot,   3, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pTangentSource);
        glEnableVertexAttribArray(m_iTangentSlot);
    }
    if(m_iColorSlot >= 0 && m_pData.m_pColorData != NULL)
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
    if(m_iTangentSlot >= 0)
    {
        glDisableVertexAttribArray(m_iTangentSlot);
    }
    if(m_iColorSlot >= 0)
    {
        glDisableVertexAttribArray(m_iColorSlot);
    }
}

void CVertexBuffer::CommitFromRAMToVRAM(void)
{
    glGenBuffers(1, &m_iHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_iHandle);
    glBufferData(GL_ARRAY_BUFFER, m_iSize * m_iNumVertexes, m_pSource, GL_STATIC_DRAW);
    m_bIsInVRAM = true;
}


