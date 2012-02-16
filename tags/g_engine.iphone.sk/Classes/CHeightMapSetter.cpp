//
//  CHeightMapSetter.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CHeightMapSetter.h"

const float CHeightMapSetter::k_HEIGHT_DIV_FACTOR = 2.0f;

CHeightMapSetter::CHeightMapSetter(void)
{
    m_pSource = NULL;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    
}

void CHeightMapSetter::Load_SourceData(const std::string& _sName, int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
    m_pSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            m_pSource[i + j * m_iHeight] = (sinf(static_cast<float>(i)) + sinf(static_cast<float>(j))) / k_HEIGHT_DIV_FACTOR;
        }
    }
}

void CHeightMapSetter::Calculate_Normals(CVertexBuffer* _pVB,CIndexBuffer* _pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode)
{
    if(_eMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN)
    {
        CVertexBuffer::SVertexVTN* pVBData = static_cast<CVertexBuffer::SVertexVTN*>(_pVB->Get_Data());
        unsigned short* pIBData = _pIB->Get_Data();
        unsigned int iNumIndexes = _pIB->Get_NumIndexes();
        for(unsigned int index = 0; index < iNumIndexes; index += 3)
        {
            CVector3d vPoint_01 = pVBData[pIBData[index]].m_vPosition;
            CVector3d vPoint_02 = pVBData[pIBData[index + 1]].m_vPosition;
            CVector3d vPoint_03 = pVBData[pIBData[index + 2]].m_vPosition;
            
            CVector3d vEdge_01 = vPoint_02 - vPoint_01;
            CVector3d vEdge_02 = vPoint_03 - vPoint_01;
            CVector3d vNormal = Cross(vEdge_01, vEdge_02);
            vNormal.Normalize();
            
            pVBData[pIBData[index]].m_vNormal = vNormal;
            pVBData[pIBData[index + 1]].m_vNormal = vNormal;
            pVBData[pIBData[index + 2]].m_vNormal = vNormal;
        }
    }
    else if(_eMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VNC)
    {
        CVertexBuffer::SVertexVNC* pVBData = static_cast<CVertexBuffer::SVertexVNC*>(_pVB->Get_Data());
        unsigned short* pIBData = _pIB->Get_Data();
        unsigned int iNumIndexes = _pIB->Get_NumIndexes();
        for(unsigned int index = 0; index < iNumIndexes; index += 3)
        {
            CVector3d vPoint_01 = pVBData[pIBData[index]].m_vPosition;
            CVector3d vPoint_02 = pVBData[pIBData[index + 1]].m_vPosition;
            CVector3d vPoint_03 = pVBData[pIBData[index + 2]].m_vPosition;
            
            CVector3d vEdge_01 = vPoint_02 - vPoint_01;
            CVector3d vEdge_02 = vPoint_03 - vPoint_01;
            CVector3d vNormal = Cross(vEdge_01, vEdge_02);
            vNormal.Normalize();
            
            pVBData[pIBData[index]].m_vNormal = vNormal;
            pVBData[pIBData[index + 1]].m_vNormal = vNormal;
            pVBData[pIBData[index + 2]].m_vNormal = vNormal;
        }
    }
}
