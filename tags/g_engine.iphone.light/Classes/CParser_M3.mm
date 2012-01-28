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

CParser_M3::SMeshData* CParser_M3::Parse(std::string _sName)
{
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSData* pNSData = [NSData dataWithContentsOfFile:sPath];
    
    char* pData = (char*)[pNSData bytes];
    SM3_Header* pHeader = (SM3_Header*)pData;
    SM3_Tag* pTagsArray =(SM3_Tag*)(pData + pHeader->m_iTagsOffset);
    
    std::string sTagName;
    
    SM3_IndexBlock* pSIndexBlock;
    unsigned short* pIndexBlock;
    SM3_Region* pRegionBlock;
    
    SMeshData* pMeshData = new SMeshData();
    
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
            pMeshData->m_iIndexCount = pSIndexBlock->m_pFaces.m_iEntries;
            pIndexBlock = (unsigned short*)(pData + pTagsArray[pSIndexBlock->m_pFaces.m_iReference].m_iBlockOffset);
            pRegionBlock = (SM3_Region*)(pData + pTagsArray[pSIndexBlock->m_Regions.m_iReference].m_iBlockOffset);
        }
        
        if( sTagName == "__8U" )
        {
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_01);
            pVertexBlock_v01 = (SM3_VertexBlock_01*)(pData + pTagsArray[i].m_iBlockOffset);
            if((iVertexBlockSize == 0) && (pVertexBlock_v01[0].m_iTangent[3] == 255))
            {
                pMeshData->m_iVertexCount = (pTagsArray[i].m_iBlockSize) / sizeof(SM3_VertexBlock_01);
                pVertexBlock_v01 = (SM3_VertexBlock_01*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_01;
            }
            
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_02);
            pVertexBlock_v02 = (SM3_VertexBlock_02*)(pData + pTagsArray[i].m_iBlockOffset);
            if((iVertexBlockSize == 0) && (pVertexBlock_v02[0].m_iTangent[3] == 255))
            {
                pMeshData->m_iVertexCount = (pTagsArray[i].m_iBlockSize) / sizeof(SM3_VertexBlock_02);
                pVertexBlock_v02 = (SM3_VertexBlock_02*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_02;
            }
            
            iVertexBlockSize = pTagsArray[i].m_iBlockSize % sizeof(SM3_VertexBlock_03);
            if(iVertexBlockSize == 0 && eVersion != E_M3_02)
            {
                pMeshData->m_iVertexCount = (pTagsArray[i].m_iBlockSize)/sizeof(SM3_VertexBlock_03);
                pVertexBlock_v03 = (SM3_VertexBlock_03*)(pData + pTagsArray[i].m_iBlockOffset);
                eVersion = E_M3_03;
            }
        }
    }
    
    
    pMeshData->m_pIndeces  = new unsigned short[pMeshData->m_iIndexCount];
	pMeshData->m_vPosition = new Vector3d[pMeshData->m_iVertexCount];
	pMeshData->m_vNormal   = new Vector3d[pMeshData->m_iVertexCount];
	pMeshData->m_vTangent  = new Vector3d[pMeshData->m_iVertexCount];
	pMeshData->m_vTexCoord = new Vector2d[pMeshData->m_iVertexCount];
    
	float wNormal = 0.0f; 
    float wTangent = 0.0f;
	
		switch(eVersion)
		{
			case E_M3_01:
				for(unsigned int i = 0; i < pMeshData->m_iVertexCount; ++i)
                {
                    pMeshData->m_vPosition[i] = pVertexBlock_v01[i].m_vPosition;
                    pMeshData->m_vNormal[i] = Vector3d( 2.0f * (float)pVertexBlock_v01[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                        2.0f * (float)pVertexBlock_v01[i].m_iNormal[1] / 255.0f - 1.0f,
                                                        2.0f * (float)pVertexBlock_v01[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = (float) pVertexBlock_v01[i].m_iNormal[3] / 255.0f;
                    if(wNormal)
                    {
                        pMeshData->m_vNormal[i].x /= wNormal;
                        pMeshData->m_vNormal[i].y /= wNormal; 
                        pMeshData->m_vNormal[i].z /= wNormal;
                    }
                    
                    pMeshData->m_vTangent[i] = Vector3d( 2.0f * (float)pVertexBlock_v01[i].m_iTangent[0] / 255.0f - 1.0f, 
                                                         2.0f * (float)pVertexBlock_v01[i].m_iTangent[1] / 255.0f - 1.0f,
                                                         2.0f * (float)pVertexBlock_v01[i].m_iTangent[2] / 255.0f - 1.0f );
                    wTangent = (float) pVertexBlock_v01[i].m_iTangent[3] / 255.0f;
                    if(wNormal)
                    {
                        pMeshData->m_vTangent[i].x /= wTangent;
                        pMeshData->m_vTangent[i].y /= wTangent; 
                        pMeshData->m_vTangent[i].z /= wTangent;
                    }
                    
                    pMeshData->m_vTexCoord[i] = Vector2d( (float) pVertexBlock_v01[i].m_iTexCoord[0] / 2048.0f, 
                                                          (float) pVertexBlock_v01[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
                
			case E_M3_02:
                for(unsigned int i = 0; i < pMeshData->m_iVertexCount; ++i)
                {
                    pMeshData->m_vPosition[i] = pVertexBlock_v02[i].m_vPosition;
                    pMeshData->m_vNormal[i] = Vector3d( 2.0f * (float)pVertexBlock_v02[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                        2.0f * (float)pVertexBlock_v02[i].m_iNormal[1] / 255.0f - 1.0f,
                                                        2.0f * (float)pVertexBlock_v02[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = (float) pVertexBlock_v02[i].m_iNormal[3] / 255.0f;
                    if(wNormal)
                    {
                        pMeshData->m_vNormal[i].x /= wNormal;
                        pMeshData->m_vNormal[i].y /= wNormal; 
                        pMeshData->m_vNormal[i].z /= wNormal;
                    }
                    pMeshData->m_vTexCoord[i] = Vector2d( (float) pVertexBlock_v02[i].m_iTexCoord[0] / 2048.0f, 
                                                          (float) pVertexBlock_v02[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
                
			case E_M3_03:
                for(unsigned int i = 0; i < pMeshData->m_iVertexCount; ++i)
                {
                    pMeshData->m_vPosition[i] = pVertexBlock_v03[i].m_vPosition;
                    pMeshData->m_vNormal[i] = Vector3d( 2.0f * (float)pVertexBlock_v03[i].m_iNormal[0] / 255.0f - 1.0f, 
                                                        2.0f * (float)pVertexBlock_v03[i].m_iNormal[1] / 255.0f - 1.0f,
                                                        2.0f * (float)pVertexBlock_v03[i].m_iNormal[2] / 255.0f - 1.0f );
                    wNormal = (float) pVertexBlock_v03[i].m_iNormal[3] / 255.0f;
                    if(wNormal)
                    {
                        pMeshData->m_vNormal[i].x /= wNormal;
                        pMeshData->m_vNormal[i].y /= wNormal; 
                        pMeshData->m_vNormal[i].z /= wNormal;
                    }
                    pMeshData->m_vTexCoord[i] = Vector2d( (float) pVertexBlock_v03[i].m_iTexCoord[0] / 2048.0f, 
                                                          (float) pVertexBlock_v03[i].m_iTexCoord[1] / 2048.0f );
                }
                break;
            default:
                break;
		}
    
	for(unsigned int i = 0; i < pMeshData->m_iIndexCount; ++i)
		pMeshData->m_pIndeces[i] = pIndexBlock[i];
    
	return pMeshData;
}
