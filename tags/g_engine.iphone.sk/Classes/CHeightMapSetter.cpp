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

CHeightMapSetter::CHeightMapSetter(void)
{
    m_pSource = NULL;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    
}

CMesh* CHeightMapSetter::Load_SourceData(const std::string _sName, int _iWidth, int _iHeight)
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

    CVector3d* pPositionData = pMesh->Get_VB()->CreateOrReUse_PositionData();
    m_pSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            m_pSource[i + j * m_iHeight] = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
        }
    }

    return pMesh;
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


void CHeightMapSetter::Calculate_Normals(CVertexBuffer* _pVB,CIndexBuffer* _pIB)
{
    CVector3d* pPositionData = _pVB->CreateOrReUse_PositionData();
    CByteVector3d* pNormalData = _pVB->CreateOrReUse_NormalData();
    unsigned short* pIBData = _pIB->Get_Data();
    unsigned int iNumIndexes = _pIB->Get_NumIndexes();
    for(unsigned int index = 0; index < iNumIndexes; index += 3)
    {
        CVector3d vPoint_01 = pPositionData[pIBData[index]];
        CVector3d vPoint_02 = pPositionData[pIBData[index + 1]];
        CVector3d vPoint_03 = pPositionData[pIBData[index + 2]];
            
        CVector3d vEdge_01 = vPoint_02 - vPoint_01;
        CVector3d vEdge_02 = vPoint_03 - vPoint_01;
        CVector3d vNormal = Cross(vEdge_01, vEdge_02);
        vNormal.Normalize();
        CByteVector3d vByteNormal = CByteVector3d(vNormal);
        pNormalData[pIBData[index]] = vByteNormal;
        pNormalData[pIBData[index + 1]] = vByteNormal;
        pNormalData[pIBData[index + 2]] = vByteNormal;
    }
    _pVB->CommitToRAM();
}




