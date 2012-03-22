//
//  CIndexBuffer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(unsigned int _iNumIndexes)
{
    m_pData = new unsigned short[_iNumIndexes];
    m_iNumIndexes = _iNumIndexes;
    m_bIsInVRAM = false;
}

CIndexBuffer::~CIndexBuffer()
{
    if(m_pData != NULL)
    {
        delete[] m_pData;
        m_pData = NULL;
    }
    
    glDeleteBuffers(1, &m_iHandle);
}

unsigned short* CIndexBuffer::Get_Data(void)
{
    return m_pData;
}

unsigned short* CIndexBuffer::Get_DataFromVRAM(void)
{
    if(m_bIsInVRAM == true)
    {
        return NULL;
    }
    else
    {
        return m_pData;
    }
}

void CIndexBuffer::Enable()
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

void CIndexBuffer::Disable()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void CIndexBuffer::CommitFromRAMToVRAM()
{
    glGenBuffers(1, &m_iHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_iNumIndexes, m_pData, GL_STATIC_DRAW);
    m_bIsInVRAM = true;
}
