//
//  CIndexBuffer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(unsigned int _iNumIndexes)
{
    m_pSourceData = new unsigned short[_iNumIndexes];
    m_pWorkingSourceData = NULL;
    m_iNumIndexes = _iNumIndexes;
    m_iNumWorkingIndexes = m_iNumIndexes;
    m_bIsInVRAM = false;
    m_eMode = GL_STATIC_DRAW;
}

CIndexBuffer::~CIndexBuffer(void)
{  
    SAFE_DELETE_ARRAY(m_pWorkingSourceData);
    SAFE_DELETE_ARRAY(m_pSourceData);
    
    if(m_bIsInVRAM)
    {
        glDeleteBuffers(1, &m_iHandle);
    }
}

unsigned short* CIndexBuffer::Get_SourceData(void)
{
    return m_pSourceData;
}

unsigned short* CIndexBuffer::Get_SourceDataFromVRAM(void)
{
    if(m_bIsInVRAM == true)
    {
        return NULL;
    }
    else
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        return m_pWorkingSourceData;
    }
}

void CIndexBuffer::Enable(void)
{
    if(m_bIsInVRAM == true)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iHandle);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    }
}

void CIndexBuffer::Disable(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

unsigned short* CIndexBuffer::Get_WorkingSourceDataRef(void)
{
    if(m_pWorkingSourceData == NULL)
    {
        m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
        memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
    }
    return m_pWorkingSourceData;
}

void CIndexBuffer::Commit(void)
{
    if(m_bIsInVRAM)
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData, m_eMode);
    }
    else
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        glGenBuffers(1, &m_iHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, NULL, m_eMode);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, NULL, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData);
        m_bIsInVRAM = true;
    }
}



