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
    m_bVRAM = false;
}

CIndexBuffer::~CIndexBuffer()
{
    if(m_pData != NULL)
    {
        delete[] m_pData;
        m_pData = NULL;
    }
    
    glDeleteBuffers(1, &m_hIBHandle);
}

void CIndexBuffer::Enable()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIBHandle);
}

void CIndexBuffer::Disable()
{
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void CIndexBuffer::Commit()
{
    glGenBuffers(1, &m_hIBHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIBHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short), m_pData, GL_STATIC_DRAW);
    m_bVRAM = true;
}
