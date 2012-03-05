//
//  CHeightMapSetter.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CHeightMapSetter.h"
#include "CSceneMgr.h"

const float CHeightMapSetter::k_HEIGHT_DIV_FACTOR = 1.0f;

CHeightMapSetter::CHeightMapSetter(void)
{
    m_pSource = NULL;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    
}

CMesh* CHeightMapSetter::Load_SourceData(const std::string _sName, int _iWidth, int _iHeight, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
    
    CParser_MDL* pParser = new CParser_MDL();
    pParser->Load(_sName);
    pParser->Commit();
    CMesh* pMesh = new CMesh();
    if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
    {
        pMesh->Set_Source(pParser->Get_Source());
    }
    CVertexBuffer::SVertexVTN* pVertexesData = static_cast<CVertexBuffer::SVertexVTN*>(pMesh->Get_VB()->Get_Data());
    m_pSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            //pVertexesData[i + ((m_iWidth - 1) - j) * m_iWidth].m_vPosition.y = 0.0f;
            //pVertexesData[i + ((m_iWidth - 1) - j) * m_iWidth].m_vNormal = CVector3d(0.0f,1.0f,0.0f);
            m_pSource[i + j * m_iHeight] = pVertexesData[i + ((m_iWidth - 1) - j) * m_iWidth].m_vPosition.y;
        }
    }

    return pMesh;
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
    
    m_pPathFindSource = new int*[m_iWidth];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        m_pPathFindSource[i] = new int[m_iHeight];
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            m_pPathFindSource[i][j] = 0;
        }
    }
}


float CHeightMapSetter::Get_HeightValueAtPoint(float _fX, float _fZ)
{
    int roundPositionX = (int) _fX;
    int roundPositionZ = (int) _fZ;
    
    float remainPositionX = _fX - roundPositionX;
    float remainPositionZ = _fZ - roundPositionZ;
    
    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (m_iWidth - 1)) || (roundPositionZ > (m_iHeight - 1)))
        return 0.0f;
    
    float height_11 = m_pSource[roundPositionX + roundPositionZ * m_iWidth];
    float height_12 = m_pSource[roundPositionX + (roundPositionZ + 1) * m_iWidth];
    float height_21 = m_pSource[roundPositionX + 1 + roundPositionZ * m_iWidth];
    float height_22 = m_pSource[roundPositionX + 1 + (roundPositionZ + 1) * m_iWidth];
    float mainHeight;
    
    if( remainPositionX > remainPositionZ )
    {
        mainHeight = height_11 + (height_22 - height_21)*remainPositionZ + (height_21 - height_11)*remainPositionX;
    }
    else
    {
        mainHeight = height_11 + (height_22 - height_12)*remainPositionX + (height_12 - height_11)*remainPositionZ;
    }
    
    float height = (1 - remainPositionX) * ((1 - remainPositionZ) * height_11 + remainPositionZ * height_12) + remainPositionX * ((1 - remainPositionZ) * height_21 + remainPositionZ * height_22);
    return height;
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
            vNormal = CVector3d(0.0f, 1.0f, 0.0f);
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




