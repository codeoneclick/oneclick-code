//
//  CVertexBufferPositionColor.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CVertexBufferPositionColor.h"

CVertexBufferPositionColor::CVertexBufferPositionColor(unsigned int _iNumVertexes, unsigned int _eMode)
{
    m_iNumVertexes = _iNumVertexes;
    m_eMode = _eMode;
    m_pData = new char[m_iNumVertexes * k_STRIDE_SIZE];
}

CVertexBufferPositionColor::~CVertexBufferPositionColor(void)
{
    
}

void CVertexBufferPositionColor::Enable(CShader::E_RENDER_MODE _eRenderMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_hHandle);
    CShader* pShader = m_lShaderRefContainer[_eRenderMode];
    unsigned char iBytesPerVertex = 0;
    glEnableVertexAttribArray(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION));
    glVertexAttribPointer(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION), 3, GL_FLOAT, GL_FALSE, k_STRIDE_SIZE, (GLvoid*)iBytesPerVertex);
    iBytesPerVertex += sizeof(glm::vec3);
    
    glEnableVertexAttribArray(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR));
    glVertexAttribPointer(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR),  4, GL_UNSIGNED_BYTE, GL_FALSE, k_STRIDE_SIZE,(GLvoid*)iBytesPerVertex);
    iBytesPerVertex += 4;
}

void CVertexBufferPositionColor::Disable(CShader::E_RENDER_MODE _eRenderMode)
{
    CShader* pShader = m_lShaderRefContainer[_eRenderMode];
    glDisableVertexAttribArray(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_POSITION));
    glDisableVertexAttribArray(pShader->Get_VertexSlot(CShader::E_VERTEX_SLOT_COLOR));
}