//
//  CParser_MDL.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_MDL.h"
#include <fstream>
#include <strstream>
#include "CCommon_IOS.h"

CParser_MDL::CParser_MDL()
{
    
}

CParser_MDL::~CParser_MDL()
{
    
}

void CParser_MDL::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;

    std::string sPath = Get_ResourceFileName(_sName); 
    
    FILE *pFile = fopen(sPath.c_str(), "r");
    if (!pFile)
    {
        return;
    }
    
    /*fseek (pFile , 0 , SEEK_END);
    long iFileBufferSize = ftell (pFile);
    rewind (pFile);*/
    
    int iNumVertexes = 0;
    int iNumIndexes = 0;
    
    fread(&iNumVertexes, sizeof(int), 1, pFile);
    fread(&iNumIndexes, sizeof(int), 1, pFile);++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    m_pSource = new CMesh::SSource();
    m_pSource->m_iNumVertexes = iNumVertexes;
    m_pSource->m_iNumIndexes = iNumIndexes;
    m_pSource->m_pIB  = new CIndexBuffer(m_pSource->m_iNumIndexes);
	m_pSource->m_pData = new CMesh::SVertex[m_pSource->m_iNumVertexes];
    
    m_pSource->m_vMaxBound = CVector3d( -4096.0f, -4096.0f, -4096.0f );
    m_pSource->m_vMinBound = CVector3d(  4096.0f,  4096.0f,  4096.0f );
    
    for( unsigned int i = 0; i < m_pSource->m_iNumVertexes; ++i)
    {
        fread(&m_pSource->m_pData[i].m_vPosition,sizeof(struct CVector3d), 1, pFile);
        fread(&m_pSource->m_pData[i].m_vNormal, sizeof(struct CVector3d), 1, pFile);
        fread(&m_pSource->m_pData[i].m_vTexCoord, sizeof(struct CVector2d), 1, pFile);
        
        std::cout<<"Position : "<<m_pSource->m_pData[i].m_vPosition.x<<","<<m_pSource->m_pData[i].m_vPosition.y<<","<<m_pSource->m_pData[i].m_vPosition.z<<"\n";
       
        if(m_pSource->m_pData[i].m_vPosition.x > m_pSource->m_vMaxBound.x)
        {
            m_pSource->m_vMaxBound.x = m_pSource->m_pData[i].m_vPosition.x;
        }
        
        if(m_pSource->m_pData[i].m_vPosition.y > m_pSource->m_vMaxBound.y)
        {
            m_pSource->m_vMaxBound.y = m_pSource->m_pData[i].m_vPosition.y;
        }
        
        if(m_pSource->m_pData[i].m_vPosition.z > m_pSource->m_vMaxBound.z)
        {
            m_pSource->m_vMaxBound.z = m_pSource->m_pData[i].m_vPosition.z;
        }
        
        if(m_pSource->m_pData[i].m_vPosition.x < m_pSource->m_vMinBound.x)
        {
            m_pSource->m_vMinBound.x = m_pSource->m_pData[i].m_vPosition.x;
        }
        
        if(m_pSource->m_pData[i].m_vPosition.y < m_pSource->m_vMinBound.y)
        {
            m_pSource->m_vMinBound.y = m_pSource->m_pData[i].m_vPosition.y;
        }
        
        if(m_pSource->m_pData[i].m_vPosition.z < m_pSource->m_vMinBound.z)
        {
            m_pSource->m_vMinBound.z = m_pSource->m_pData[i].m_vPosition.z;
        }
    }
    /*fseek (pFile , 0 , SEEK_CUR);
    long iFileBufferSizeRead = ftell (pFile);
    long iFileBufferSizeRest = iFileBufferSize - iFileBufferSizeRead;
    
    unsigned int iBlockSize = iFileBufferSizeRest / m_pSource->m_iNumIndexes;
    
    std::cout<<"[CParser_MDL] Index block size: "<<iBlockSize;*/
    
    //int iNum = 0;
    unsigned short* pIBData = m_pSource->m_pIB->Get_Data();
    for(int i = 0; i < m_pSource->m_iNumIndexes; i++)
    {
        fread(&pIBData[i], sizeof(unsigned short),1, pFile);
        //std::cout<<"Index : "<<pIBData[i]<<"  Num : "<<iNum++<<"\n";
    }
    fclose(pFile);
    
    m_eStatus = E_DONE_STATUS;
}

void CParser_MDL::Commit()
{
    m_pSource->m_pVB = new CVertexBuffer(m_pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVTN),CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);
    CVertexBuffer::SVertexVTN* pData = static_cast<CVertexBuffer::SVertexVTN*>(m_pSource->m_pVB->Get_Data());  
    
    for(unsigned int index = 0; index < m_pSource->m_iNumVertexes; index++)
    {
        pData[index].m_vPosition = m_pSource->m_pData[index].m_vPosition;
        pData[index].m_vTexCoord = m_pSource->m_pData[index].m_vTexCoord;
        pData[index].m_vNormal = m_pSource->m_pData[index].m_vNormal;
    }
}


