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
    m_pDataSource = NULL;
    m_fXThreshold = 0.5f;
    m_fZThreshold = 0.5f;
    m_pTextureSplattingDataSource = NULL;
    m_pTextureDecalDataSource = NULL;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    
}

CMesh* CHeightMapSetter::Load_DataSource(const std::string _sName, int _iWidth, int _iHeight)
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
    m_pDataSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
            pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y = fHeight;
            m_pDataSource[i + j * m_iHeight] = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
        }
    }
    
    _Create_TextureSplatting();
    
    return pMesh;
}

float CHeightMapSetter::Get_HeightValue(float _x, float _z)
{
    _x -= m_fXThreshold;
    _z -= m_fZThreshold;
    int x = static_cast<int>(floor(_x));
    int z = static_cast<int>(floor(_z));
    float dx = _x - x;
    float dy = _z - z;
    
    if((x <= 0) || (z <= 0) || (x >= (m_iWidth - 1)) || (z >= (m_iHeight - 1)))
        return -1.0f;
    
    float fHeight_00 = m_pDataSource[x + z * m_iWidth];
    float fHeight_01 = m_pDataSource[x + (z + 1) * m_iWidth];
    float fHeight_10 = m_pDataSource[x + 1 + z * m_iWidth];
    float fHeight_11 = m_pDataSource[x + 1 + (z + 1) * m_iWidth];
    
    float fHeight_0 = fHeight_00 * (1 - dy) + fHeight_01 * dy;
    float fHeight_1 = fHeight_10 * (1 - dy) + fHeight_11 * dy;
    
    return fHeight_0 * (1 - dx) + fHeight_1 * dx;
}

#define RGB(r,g,b) (unsigned short)(b + (g << 5) + (r << 11))
void CHeightMapSetter::_Create_TextureSplatting(void)
{
    glGenTextures(1, &m_hTextureSplatting);
    glBindTexture(GL_TEXTURE_2D, m_hTextureSplatting);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_pTextureSplattingDataSource = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(255, 0, 0);
            
            if(Get_HeightValue(i, j) > 1.25f)
            {
                m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(0, 255, 0);
            }
            if(Get_HeightValue(i, j) < 0.05f)
            {
                m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(0, 0, 255);
            }
            
            if( i == 0 || j == 0 || i == (m_iWidth - 1) || j == (m_iHeight - 1))
            {
                 m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(255, 0, 0);
            }

        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, m_pTextureSplattingDataSource);
}

void CHeightMapSetter::_Create_TextureDecal(void)
{
    glGenTextures(1, &m_hTextureDecal);
    glBindTexture(GL_TEXTURE_2D, m_hTextureDecal);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_pTextureDecalDataSource = new unsigned short[m_iWidth * m_iHeight];
    memset(m_pTextureDecalDataSource, 0x0, m_iWidth * m_iHeight);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, m_pTextureDecalDataSource);
}

void CHeightMapSetter::_Update_TextureDecal(void)
{
    glBindTexture(GL_TEXTURE_2D, m_hTextureDecal);
    
    std::vector<glm::vec2>::iterator pBeginDecalShadowContainerIterator = m_lContainerShadowDecal.begin();
    std::vector<glm::vec2>::iterator pEndDecalShadowContainerIterator = m_lContainerShadowDecal.end();
    
    while (pBeginDecalShadowContainerIterator != pEndDecalShadowContainerIterator)
    {
        
    }
}

void CHeightMapSetter::Update(void)
{
    
}










