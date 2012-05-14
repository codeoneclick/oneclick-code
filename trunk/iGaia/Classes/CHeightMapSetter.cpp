//
//  CHeightMapSetter.cpp
//  iGaia
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

    glm::vec3* pPositionData = pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    m_pSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
            /*if(fHeight < -0.2f)
            {
                fHeight = -0.2f;
            }
            else if(fHeight < 0.0f)
            {
                fHeight = 0.0f;
            }
            else if(fHeight < 0.2f)
            {
                fHeight = 0.2f;
            }
            else if(fHeight < 0.4f)
            {
                fHeight = 0.4f;
            }
            else if(fHeight < 0.6f)
            {
                fHeight = 0.6f;
            }
            else
            {
                fHeight = 0.8f;
            }*/
            
            pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y = fHeight;
            m_pSource[i + j * m_iHeight] = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
        }
    }
    
    Create_SplattingTexture();
    
    return pMesh;
}

float CHeightMapSetter::Get_HeightValueAtPoint(float _fX, float _fZ)
{
    int roundPositionX = static_cast<int>(_fX);
    int roundPositionZ = static_cast<int>(_fZ);
    
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
    
    //float height = (1 - remainPositionX) * ((1 - remainPositionZ) * height_11 + remainPositionZ * height_12) + remainPositionX * ((1 - remainPositionZ) * height_21 + remainPositionZ * height_22);
    return mainHeight;
}


void CHeightMapSetter::Calculate_Normals(CVertexBuffer* _pVB,CIndexBuffer* _pIB)
{
    glm::vec3* pPositionData = _pVB->CreateOrReUse_PositionData();
    glm::u8vec4* pNormalData = _pVB->CreateOrReUse_NormalData();
    unsigned short* pIBData = _pIB->Get_Data();
    unsigned int iNumIndexes = _pIB->Get_NumIndexes();
    for(unsigned int index = 0; index < iNumIndexes; index += 3)
    {
        glm::vec3 vPoint_01 = pPositionData[pIBData[index]];
        glm::vec3 vPoint_02 = pPositionData[pIBData[index + 1]];
        glm::vec3 vPoint_03 = pPositionData[pIBData[index + 2]];
            
        glm::vec3 vEdge_01 = vPoint_02 - vPoint_01;
        glm::vec3 vEdge_02 = vPoint_03 - vPoint_01;
        glm::vec3 vNormal = glm::cross(vEdge_01, vEdge_02);
        vNormal = glm::normalize(vNormal);
        glm::u8vec4 vByteNormal = CVertexBuffer::CompressVEC3(vNormal);
        pNormalData[pIBData[index]] = vByteNormal;
        pNormalData[pIBData[index + 1]] = vByteNormal;
        pNormalData[pIBData[index + 2]] = vByteNormal;
    }
    _pVB->CommitToRAM();
}

#define RGB(r,g,b) (unsigned short)(b + (g << 5) + (r << 11))
void CHeightMapSetter::Create_SplattingTexture(void)
{
    glGenTextures(1, &m_hTextureSplatting);
    glBindTexture(GL_TEXTURE_2D, m_hTextureSplatting);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    unsigned short* pTextureData = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            pTextureData[i + j * m_iHeight] = RGB(255, 0, 0);
            if(m_pSource[i + j * m_iHeight] < 1.0f)
            {
                pTextureData[i + j * m_iHeight] = RGB(0, 255, 0);
            }
            if(m_pSource[i + j * m_iHeight] < 0.0f)
            {
                pTextureData[i + j * m_iHeight] = RGB(0, 0, 255);
            }
            
            if( i == 0 || j == 0 || i == (m_iWidth - 1) || j == (m_iHeight - 1))
            {
                 pTextureData[i + j * m_iHeight] = RGB(255, 0, 0);
            }

        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pTextureData);
}


