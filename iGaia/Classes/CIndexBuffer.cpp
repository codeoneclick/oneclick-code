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
}

CIndexBuffer::~CIndexBuffer(void)
{
    if(m_pSourceData != NULL)
    {
        delete[] m_pSourceData;
        m_pSourceData = NULL;
    }
    
    glDeleteBuffers(1, &m_iHandle);
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

void CIndexBuffer::Set_WorkingSourceData(unsigned short *_pSourceData, unsigned int _iNumIndexes)
{
    if(m_pWorkingSourceData == NULL)
    {
        m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
    }
    m_iNumWorkingIndexes = _iNumIndexes;
    memcpy(m_pWorkingSourceData, _pSourceData, m_iNumWorkingIndexes * sizeof(unsigned short));
}

void CIndexBuffer::CommitFromRAMToVRAM(void)
{
    if(m_bIsInVRAM)
    {
        if(m_pWorkingSourceData == NULL)
        {
            m_pWorkingSourceData = new unsigned short[m_iNumIndexes];
            memcpy(m_pWorkingSourceData, m_pSourceData, sizeof(unsigned short) * m_iNumIndexes);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData, GL_STREAM_DRAW);
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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumWorkingIndexes, NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, NULL, sizeof(unsigned short) * m_iNumWorkingIndexes, m_pWorkingSourceData);
        m_bIsInVRAM = true;
    }
}



