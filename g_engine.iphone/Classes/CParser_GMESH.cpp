//
//  CParser_GMESH.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_GMESH.h"
#include <fstream>
#include <strstream>
#include "CCommon_IOS.h"

CParser_GMESH::CParser_GMESH()
{
    
}

CParser_GMESH::~CParser_GMESH()
{
    
}

void CParser_GMESH::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;

    std::string sFileName = Get_ResourceFileName(_sName); 
    std::ifstream pStream;
    pStream.open(sFileName.c_str(), std::ios::in);
    
    int iNumVertexes;
    int iNumIndexes;
    
    pStream >> iNumVertexes >> iNumIndexes;
    
    m_pSource = new CMesh::SSource();
    m_pSource->m_iNumVertexes = iNumVertexes;
    m_pSource->m_iNumIndexes = iNumIndexes;
    m_pSource->m_pIB  = new unsigned short[m_pSource->m_iNumIndexes];
	m_pSource->m_pData = new CMesh::SVertex[m_pSource->m_iNumVertexes];
    
    for( unsigned int i = 0; i < iNumVertexes; ++i)
    {
        pStream >> m_pSource->m_pData[i].m_vPosition.x >> m_pSource->m_pData[i].m_vPosition.y >> m_pSource->m_pData[i].m_vPosition.z;
        pStream >> m_pSource->m_pData[i].m_vNormal.x >> m_pSource->m_pData[i].m_vNormal.y >> m_pSource->m_pData[i].m_vNormal.z;
        pStream >> m_pSource->m_pData[i].m_vTexCoord.x >> m_pSource->m_pData[i].m_vTexCoord.y;
        pStream >> m_pSource->m_pData[i].m_iNumBones;
        for(unsigned int j = 0; j < m_pSource->m_pData[i].m_iNumBones; ++j)
        {
            pStream >> m_pSource->m_pData[i].m_tBoneWeights[j].m_iBoneID >> m_pSource->m_pData[i].m_tBoneWeights[j].m_fWeight;
        }
    }
    
    for( unsigned int i = 0; i < iNumIndexes; ++i)
    {
        int index = 0;
        pStream >> index;
        m_pSource->m_pIB[i] = static_cast<short>(index);
    }
    
    int iNumBones = 0;
    pStream >> iNumBones;
    
    m_pSource->m_pSkeleton = new CSkeleton(iNumBones);
    std::string sBoneName;
    int iBoneID, iParentBoneID;
    
    for(int i = 0; i < iNumBones; ++i)
    {
        pStream >> sBoneName >> iBoneID >> iParentBoneID;
        m_pSource->m_pSkeleton->AddBone(new CBone(sBoneName, iBoneID, iParentBoneID));
    }
    
    
    pStream.close();
    m_eStatus = E_DONE_STATUS;
}

void CParser_GMESH::Commit()
{
    m_pSource->m_pVB = new CVertexBuffer(m_pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertex));
    CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(m_pSource->m_pVB->Get_Data());  
    
    for(unsigned int index = 0; index < m_pSource->m_iNumVertexes; index++)
    {
        pData[index].m_vPosition = m_pSource->m_pData[index].m_vPosition;
        pData[index].m_vTexCoord = m_pSource->m_pData[index].m_vTexCoord;
        pData[index].m_vNormal = m_pSource->m_pData[index].m_vNormal;
    }
}


