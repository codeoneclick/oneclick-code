//
//  CEditMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CEditMgr.h"

const float CEditMgr::k_HEIGHT_DIV_FACTOR = 2.0f;

CEditMgr* CEditMgr::m_pInstance = NULL;

CEditMgr::CEditMgr()
{
    
}

CEditMgr::~CEditMgr()
{
    
}

CEditMgr* CEditMgr::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CEditMgr();
    }
    return m_pInstance;
}

float** CEditMgr::LoadHeightmapData(const std::string& _sName, unsigned int _iWidth, unsigned int _iHeight)
{
    float** pData = new float*[_iWidth];
    for(unsigned int i = 0; i < _iWidth; ++i)
    {
        pData[i] = new float[_iHeight];
        for(unsigned int j = 0; j < _iHeight; ++j)
        {
            pData[i][j] = (sinf(static_cast<float>(i)) + sinf(static_cast<float>(j))) / k_HEIGHT_DIV_FACTOR;
        }
    }
    return pData;
}

unsigned char* CEditMgr::LoadTilesetData(const std::string &_sName, unsigned int _iWidth, unsigned int _iHeight)
{
    unsigned char* pData = new unsigned char[_iWidth * _iHeight]; 
    for(unsigned int i = 0; i < _iWidth; ++i)
    {
        for(unsigned int j = 0; j < _iHeight; ++j)
        {
            pData[i + j * _iHeight] = 0;
        }
    }
    return pData;
}

CTileSetterMgr::STileTexCoords* CEditMgr::Get_TilesetData(const std::string& _sName, unsigned int _iWidth, unsigned int _iHeight, unsigned char* _pSource)
{
    CTileSetterMgr::Instance()->Set_Data(_pSource, _iWidth, _iHeight);
    CTileSetterMgr::STileTexCoords* pTilesetData = CTileSetterMgr::Instance()->Get_Data();
    return pTilesetData;
}

void CEditMgr::CalculateNormals(CVertexBuffer* _pVB,CIndexBuffer* _pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode)
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

void CEditMgr::EditTilesetData(const std::string& _sName, int _iX, int _iY, unsigned int _iWidth, unsigned int _iHeight, CTileSetterMgr::E_TILE_LEVEL _eLevel, CVertexBuffer* _pVB, CTileSetterMgr::STileTexCoords* _pData, unsigned char* _pSource)
{
    _pSource[_iX + _iY * _iHeight] = static_cast<unsigned char>(_eLevel);
    _pData = Get_TilesetData(_sName, _iWidth, _iHeight, _pSource); 
    CVertexBuffer::SVertexVTN* pVBData = static_cast<CVertexBuffer::SVertexVTN*>(_pVB->Get_Data());
    
    unsigned int iVBIndex = 0; 
    
    for(int i = 0; i < _iWidth; ++i)
    {
        for(int j = 0; j < _iHeight; ++j)
        {          
            pVBData[iVBIndex].m_vTexCoord = _pData[i + j * _iHeight].m_vTexCoord[2];
            pVBData[iVBIndex + 1].m_vTexCoord = _pData[i + j * _iHeight].m_vTexCoord[3];
            pVBData[iVBIndex + 2].m_vTexCoord = _pData[i + j * _iHeight].m_vTexCoord[0];
            pVBData[iVBIndex + 3].m_vTexCoord = _pData[i + j * _iHeight].m_vTexCoord[1];
            iVBIndex += 4;
        }
    }
}


















