//
//  CParser_M3.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_M3.h"

CParser_M3::CParser_M3()
{

}

CParser_M3::~CParser_M3()
{
    
}

void CParser_M3::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSData* pNSData = [NSData dataWithContentsOfFile:sPath];
    
    char* pData = (char*)[pNSData bytes];
    SM3_Header* pHeader = (SM3_Header*)pData;
    SM3_Tag* pTagsArray = (SM3_Tag*)(pData + pHeader->m_iTagsOffset);
    
    std::string sTagName;
    
    SM3_IndexBlock* pSIndexBlock;
    unsigned short* pIndexBlock;
    SM3_Region* pRegionBlock;
    
    CMesh::SSource* pSource = new CMesh::SSource();
    
    E_M3_VERSION eVersion = E_M3_UNKNOWN;
    
    SM3_VertexBlock_01* pVertexBlock_v01;
	SM3_VertexBlock_02* pVertexBlock_v02;
	SM3_VertexBlock_03* pVertexBlock_v03;
    
    unsigned int iVertexBlockSize = 0;
    
    for(unsigned int i = 0; i < pHeader->m_iTagsCount; ++i)
    {
        sTagName = pTagsArray[i].m_pName;
        sTagName.resize(4);
        
        if( sTagName == "_VID" )
        {
            pSIndexBlock = (SM3_IndexBlock*)(pData + pTagsArray[i].m_iBlockOffset);
            pSource->m_iNumIndexes = pSIndexBlock->m_pFaces.m_iEntries;
            pIndexBlock = (unsigned short*)(pData + pTagsArray[pSIndexBlock->m_pFaces.m_iReference].m_iBlockOffset);
            pRegionBlock = (SM3_Region*)(pData + pTagsArray[pSIndexBlock->m_Regions.m_iReference].m_iBlockOffset);
        }
        
        if( sTagName == "__8U" )
        {
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_01);
            pVertexBlock_v01 = (SM3_VertexBlock_01*)(pData + pTagsArray[i].m_iBlockOffset);
            if((iVertexBlockSize == 0) && (pVertexBlock_v01[0].m_iTangent[3] == 255))
            {
                pSource->m_iNumVertexes = (pTagsArray[i].m_iBlockSize) / sizeof(SM3_VertexBlock_01);
                pVertexBlock_v01 = (SM3_VertexBlock_01*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_01;
            }
            
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_02);
            pVertexBlock_v02 = (SM3_VertexBlock_02*)(pData + pTagsArray[i].m_iBlockOffset);
            if((iVertexBlockSize == 0) && (pVertexBlock_v02[0].m_iTangent[3] == 255))
            {
                pSource->m_iNumVertexes = (pTagsArray[i].m_iBlockSize) / sizeof(SM3_VertexBlock_02);
                pVertexBlock_v02 = (SM3_VertexBlock_02*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_02;
            }
            
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_03);
            if(iVertexBlockSize == 0 && eVersion != E_M3_02)
            {
                pSource->m_iNumVertexes = (pTagsArray[i].m_iBlockSize)/sizeof(SM3_VertexBlock_03);
                pVertexBlock_v03 = (SM3_VertexBlock_03*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_03;
            }
        }
    }
    
    
    pSource->m_pIB  = new unsigned short[pSource->m_iNumIndexes];
	pSource->m_pData = new CMesh::SVertex[pSource->m_iNumVertexes];
    
	float wNormal = 0.0f; 
    float wTangent = 0.0f;
	
		switch(eVersion)
		{
			case E_M3_01:
				for(unsigned int i = 0; i < pSource->m_iNumVertexes; ++i)
                {
                    pSource->m_pData[i].m_vPosition = pVertexBlock_v01[i].m_vPosition;
                    pSource->m_pData[i].m_vNormal = Vector3d( 2.0f * (float)pVertexBlock_v01[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                              2.0f * (float)pVertexBlock_v01[i].m_iNormal[1] / 255.0f - 1.0f,
                                                              2.0f * (float)pVertexBlock_v01[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = -1.0f;
                    if(wNormal)
                    {
                        pSource->m_pData[i].m_vNormal.x /= wNormal;
                        pSource->m_pData[i].m_vNormal.y /= wNormal; 
                        pSource->m_pData[i].m_vNormal.z /= wNormal;
                    }
                    
                    pSource->m_pData[i].m_vTangent = Vector3d( 2.0f * (float)pVertexBlock_v01[i].m_iTangent[0] / 255.0f - 1.0f, 
                                                         2.0f * (float)pVertexBlock_v01[i].m_iTangent[1] / 255.0f - 1.0f,
                                                         2.0f * (float)pVertexBlock_v01[i].m_iTangent[2] / 255.0f - 1.0f );
                    wTangent = -1.0f;
                    if(wNormal)
                    {
                        pSource->m_pData[i].m_vTangent.x /= wTangent;
                        pSource->m_pData[i].m_vTangent.y /= wTangent; 
                        pSource->m_pData[i].m_vTangent.z /= wTangent;
                    }
                    
                    pSource->m_pData[i].m_vTexCoord = Vector2d( (float) pVertexBlock_v01[i].m_iTexCoord[0] / 2048.0f, 
                                                          -(float) pVertexBlock_v01[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
                
			case E_M3_02:
                for(unsigned int i = 0; i < pSource->m_iNumVertexes; ++i)
                {
                    pSource->m_pData[i].m_vPosition = pVertexBlock_v02[i].m_vPosition;
                    pSource->m_pData[i].m_vNormal = Vector3d( 2.0f * (float)pVertexBlock_v02[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                        2.0f * (float)pVertexBlock_v02[i].m_iNormal[1] / 255.0f - 1.0f,
                                                        2.0f * (float)pVertexBlock_v02[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = (float) pVertexBlock_v02[i].m_iNormal[3] / 255.0f;
                    if(wNormal)
                    {
                        pSource->m_pData[i].m_vNormal.x /= wNormal;
                        pSource->m_pData[i].m_vNormal.y /= wNormal; 
                        pSource->m_pData[i].m_vNormal.z /= wNormal;
                    }
                    pSource->m_pData[i].m_vTexCoord = Vector2d( (float) pVertexBlock_v02[i].m_iTexCoord[0] / 2048.0f, 
                                                          (float) pVertexBlock_v02[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
                
			case E_M3_03:
                for(unsigned int i = 0; i < pSource->m_iNumVertexes; ++i)
                {
                    pSource->m_pData[i].m_vPosition = pVertexBlock_v03[i].m_vPosition;
                    pSource->m_pData[i].m_vNormal = Vector3d( 2.0f * (float)pVertexBlock_v03[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                        2.0f * (float)pVertexBlock_v03[i].m_iNormal[1] / 255.0f - 1.0f,
                                                        2.0f * (float)pVertexBlock_v03[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = (float) pVertexBlock_v03[i].m_iNormal[3] / 255.0f;
                    if(wNormal)
                    {
                        pSource->m_pData[i].m_vNormal.x /= wNormal;
                        pSource->m_pData[i].m_vNormal.y /= wNormal; 
                        pSource->m_pData[i].m_vNormal.z /= wNormal;
                    }
                    pSource->m_pData[i].m_vTexCoord = Vector2d( (float) pVertexBlock_v03[i].m_iTexCoord[0] / 2048.0f, 
                                                          (float) pVertexBlock_v03[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
            default:
                break;
		}
    
	for(unsigned int i = 0; i < pSource->m_iNumIndexes; ++i)
		pSource->m_pIB[i] = pIndexBlock[i];
    
	m_pSource = pSource;
    m_eStatus = E_DONE_STATUS;
}

void CParser_M3::Commit()
{
    m_pSource->m_pVB = new CVertexBuffer(m_pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertex));
    CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(m_pSource->m_pVB->Get_Data());  
    
    for(unsigned int index = 0; index < m_pSource->m_iNumVertexes; index++)
    {
        pData[index].m_vPosition = m_pSource->m_pData[index].m_vPosition;
        pData[index].m_vTexCoord = m_pSource->m_pData[index].m_vTexCoord;
        pData[index].m_vNormal   = m_pSource->m_pData[index].m_vNormal;
    }
    m_pSource->m_pVB->Commit();
}



