//
//  CVertexBuffer.cpp
//  iGaia
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

glm::u8vec4 CVertexBuffer::CompressVector(const glm::vec3 &_vUncopressed)
{
    glm::vec3 vNormalized = glm::normalize(_vUncopressed);
    glm::u8vec4 vCompressed;
    vCompressed.x = static_cast<unsigned char>((vNormalized.x + 1.0f) * 0.5f * 255.0f);
    vCompressed.y = static_cast<unsigned char>((vNormalized.y + 1.0f) * 0.5f * 255.0f);
    vCompressed.z = static_cast<unsigned char>((vNormalized.z + 1.0f) * 0.5f * 255.0f);
    vCompressed.w = 0;
    
    vNormalized.x = static_cast<float>(vCompressed.x / (255.0f * 0.5f) - 1.0f);
    vNormalized.y = static_cast<float>(vCompressed.y / (255.0f * 0.5f) - 1.0f);
    vNormalized.z = static_cast<float>(vCompressed.z / (255.0f * 0.5f) - 1.0f);
    return vCompressed;
}


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

glm::vec3* CVertexBuffer::CreateOrReUse_PositionData(void)
{
    if(m_pData.m_pPositionData == NULL)
    {
        m_pData.m_pPositionData = new glm::vec3[m_iNumVertexes];
    }
    return m_pData.m_pPositionData;
}

glm::vec2* CVertexBuffer::CreateOrReUse_TexCoordData(void)
{
    if(m_pData.m_pTexCoordData == NULL)
    {
        m_pData.m_pTexCoordData = new glm::vec2[m_iNumVertexes];
    }
    return m_pData.m_pTexCoordData;
}

glm::u8vec4* CVertexBuffer::CreateOrReUse_NormalData(void)
{
    if(m_pData.m_pNormalData == NULL)
    {
        m_pData.m_pNormalData = new glm::u8vec4[m_iNumVertexes];
    }
    return m_pData.m_pNormalData;
}

glm::u8vec4* CVertexBuffer::CreateOrReUse_TangentData(void)
{
    if(m_pData.m_pTangentData == NULL)
    {
        m_pData.m_pTangentData = new glm::u8vec4[m_iNumVertexes];
    }
    return m_pData.m_pTangentData;
}

glm::u8vec4* CVertexBuffer::CreateOrReUse_ColorData(void)
{
    if(m_pData.m_pColorData == NULL)
    {
        m_pData.m_pColorData = new glm::u8vec4[m_iNumVertexes];
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
        iBytesPerVertex += 4;
    }
    if(m_pData.m_pTangentData != NULL)
    {
        iBytesPerVertex += 4;
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
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pPositionData[i][0], sizeof(glm::vec3));
            iPtrOffset += sizeof(glm::vec3);
        }
        if(m_pData.m_pTexCoordData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pTexCoordData[i][0], sizeof(glm::vec2));
            iPtrOffset += sizeof(glm::vec2);
        }
        if(m_pData.m_pNormalData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pNormalData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        if(m_pData.m_pTangentData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pTangentData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        if(m_pData.m_pColorData != NULL)
        {
            memcpy(m_pSource + iPtrOffset, &m_pData.m_pColorData[i][0], sizeof(glm::u8vec4));
            iPtrOffset += sizeof(glm::u8vec4);
        }
        
        iPtrOffset += iPaddingSize;
    }
}

void CVertexBuffer::Enable(void)
{
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
        if(m_iTexcoordSlot >= 0 && m_pData.m_pTexCoordData != NULL)
        {
            glEnableVertexAttribArray(m_iTexcoordSlot);
            glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 8;
        }
        if(m_iNormalSlot >= 0 && m_pData.m_pNormalData != NULL)
        {
            glEnableVertexAttribArray(m_iNormalSlot);
            glVertexAttribPointer(m_iNormalSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, (GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 4;
        }
        if(m_iTangentSlot >= 0 && m_pData.m_pTangentData != NULL)
        {
            glEnableVertexAttribArray(m_iTangentSlot);
            glVertexAttribPointer(m_iTangentSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 4;
        }
        if(m_iColorSlot >= 0 && m_pData.m_pColorData != NULL)
        {
            glEnableVertexAttribArray(m_iColorSlot);
            glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize,(GLvoid*)iBytesPerVertex);
            iBytesPerVertex += 4;
        }
        return; 
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    const GLvoid* pPositionSource = NULL;
    const GLvoid* pTexcoordSource = NULL;
    const GLvoid* pNormalSource   = NULL;
    const GLvoid* pTangentSource  = NULL;
    const GLvoid* pColorSource    = NULL;
    
    unsigned int iBytesPerVertex = 0;
    if(m_pData.m_pPositionData != NULL)
    {
        pPositionSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::vec3);
    }
    if(m_pData.m_pTexCoordData != NULL)
    {
        pTexcoordSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::vec2);
    }
    if(m_pData.m_pNormalData != NULL)
    {
        pNormalSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::u8vec4);
    }
    if(m_pData.m_pTangentData != NULL)
    {
        pTangentSource = m_pSource + iBytesPerVertex;
        iBytesPerVertex += sizeof(glm::u8vec4);
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
        glVertexAttribPointer(m_iNormalSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pNormalSource);
        glEnableVertexAttribArray(m_iNormalSlot);
    }
    if(m_iTangentSlot >= 0 && m_pData.m_pTangentData != NULL)
    {
        glVertexAttribPointer(m_iTangentSlot, 4, GL_UNSIGNED_BYTE, GL_FALSE, m_iSize, pTangentSource);
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


