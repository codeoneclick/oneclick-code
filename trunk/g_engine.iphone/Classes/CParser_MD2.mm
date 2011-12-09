//
//  CParser_MD2.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_MD2.h"

const int k_MAX_TRIANGLES   = 4096;
const int k_MAX_VERTS		= 2048;
const int k_MAX_FRAMES	    = 512;
const int k_MAX_MD2SKINS	= 32;
const int k_MAX_SKINNAME	= 64;

CParser_MD2::CParser_MD2()
{
    
}

CParser_MD2::~CParser_MD2()
{
    
}

void CParser_MD2::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSData* pNSData = [NSData dataWithContentsOfFile:sPath];
    
    char* pData = (char*)[pNSData bytes];
    unsigned int iDataPointer = 0;
    SMD2_Header* pHeader = (SMD2_Header*)pData;
    iDataPointer += sizeof(SMD2_Header);
    
    char pSkins[k_MAX_MD2SKINS][64];
    SMD2_VT	pVT[k_MAX_VERTS];
    unsigned char pVData[k_MAX_VERTS * 4 + 128];
    SMD2_VertexRef_01 pTriangle;
    SMD2_Frame* pFrame;
    
    pHeader->framesize = (int)&((SMD2_Frame*)0)->pVertexRef[pHeader->num_xyz];
    
    int iFramesCount = pHeader->num_frames;
    int iTrianglesCount = pHeader->num_tris;
    
    SMD2_IndexList* pIndexList = new SMD2_IndexList[iTrianglesCount];
    SMD2_FrameList* pFrameList = new SMD2_FrameList[iFramesCount];
    
    for( int i = 0; i < pHeader->num_frames; i++)
    {
		pFrameList[i].pV = new SMD2_VertexList[pHeader->num_xyz];
    }
    
    memcpy(pSkins, pData + iDataPointer, pHeader->num_skins * k_MAX_SKINNAME);
    iDataPointer += pHeader->num_skins * k_MAX_SKINNAME;
    memcpy(pVT, pData + iDataPointer, pHeader->num_st * sizeof(pVT[0]));
    iDataPointer += pHeader->num_st * sizeof(pVT[0]);
    
    int	iMaxTecoord_x = 0, iMaxTecoord_y = 0;
    
    for(unsigned int i = 0; i < pHeader->num_tris; i++) 
	{
        memcpy(&pTriangle, pData + iDataPointer, sizeof(SMD2_VertexRef_01));
        iDataPointer += sizeof(SMD2_VertexRef_01);
		
		pIndexList[i].a = pTriangle.pPositionRef[0];
		pIndexList[i].b = pTriangle.pPositionRef[1];
		pIndexList[i].c = pTriangle.pPositionRef[2];
                
		pIndexList[i].a_s = pVT[pTriangle.pTexcoordRef[0]].x;
		pIndexList[i].a_t = pVT[pTriangle.pTexcoordRef[0]].y;
		pIndexList[i].b_s = pVT[pTriangle.pTexcoordRef[1]].x;
		pIndexList[i].b_t = pVT[pTriangle.pTexcoordRef[1]].y;
		pIndexList[i].c_s = pVT[pTriangle.pTexcoordRef[2]].x;
		pIndexList[i].c_t = pVT[pTriangle.pTexcoordRef[2]].y;
        
		iMaxTecoord_x = std::max( iMaxTecoord_x, static_cast<int>(pVT[pTriangle.pTexcoordRef[0]].x) );
		iMaxTecoord_x = std::max( iMaxTecoord_x, static_cast<int>(pVT[pTriangle.pTexcoordRef[1]].x) );
		iMaxTecoord_x = std::max( iMaxTecoord_x, static_cast<int>(pVT[pTriangle.pTexcoordRef[2]].x) );
		iMaxTecoord_y = std::max( iMaxTecoord_y, static_cast<int>(pVT[pTriangle.pTexcoordRef[0]].y) );
		iMaxTecoord_y = std::max( iMaxTecoord_y, static_cast<int>(pVT[pTriangle.pTexcoordRef[1]].y) );
		iMaxTecoord_y = std::max( iMaxTecoord_y, static_cast<int>(pVT[pTriangle.pTexcoordRef[2]].y) );
	}
    
    for (unsigned int i = 0; i < pHeader->num_tris; i++ ) 
	{
		pIndexList[i].a_s /= iMaxTecoord_x;
		pIndexList[i].b_s /= iMaxTecoord_x;
		pIndexList[i].c_s /= iMaxTecoord_x;
		pIndexList[i].a_t /= iMaxTecoord_y;
		pIndexList[i].b_t /= iMaxTecoord_y;
		pIndexList[i].c_t /= iMaxTecoord_y;
	}
    
    m_pSource = new CMesh::SSource();
    m_pSource->m_iNumVertexes = iTrianglesCount * 3;
    m_pSource->m_iNumIndexes = iTrianglesCount * 3;
    m_pSource->m_pIB  = new unsigned short[m_pSource->m_iNumIndexes];
	m_pSource->m_pData = new CMesh::SVertex[m_pSource->m_iNumVertexes];
    
    for(unsigned int i = 0; i < pHeader->num_frames; i++ ) 
	{
		pFrame = (SMD2_Frame*)pVData;
        memcpy(pFrame, pData + iDataPointer, pHeader->framesize);
        iDataPointer += pHeader->framesize;
		for(unsigned int j = 0; j < pHeader->num_xyz; j++ ) 
		{
            pFrameList[i].pV[j].x = pFrame->pVertexRef[j].pV[0] * pFrame->vScale.x + pFrame->vPosition.x;
            pFrameList[i].pV[j].y = pFrame->pVertexRef[j].pV[1] * pFrame->vScale.y + pFrame->vPosition.y;
            pFrameList[i].pV[j].z = pFrame->pVertexRef[j].pV[2] * pFrame->vScale.z + pFrame->vPosition.z;
		}
	}
   
    
    unsigned int i = 0;
    for(unsigned int index = 0; index < iTrianglesCount; index++)
    {
        m_pSource->m_pData[i].m_vPosition = Vector3d(pFrameList[0].pV[pIndexList[index].a].x,pFrameList[0].pV[pIndexList[index].a].y,pFrameList[0].pV[pIndexList[index].a].z);
        m_pSource->m_pData[i].m_vTexCoord = Vector2d(pIndexList[index].a_s,-pIndexList[index].a_t);
        i++;
        
        m_pSource->m_pData[i].m_vPosition = Vector3d(pFrameList[0].pV[pIndexList[index].b].x,pFrameList[0].pV[pIndexList[index].b].y,pFrameList[0].pV[pIndexList[index].b].z);
        m_pSource->m_pData[i].m_vTexCoord = Vector2d(pIndexList[index].b_s,-pIndexList[index].b_t);
        i++;
        
        m_pSource->m_pData[i].m_vPosition = Vector3d(pFrameList[0].pV[pIndexList[index].c].x,pFrameList[0].pV[pIndexList[index].c].y,pFrameList[0].pV[pIndexList[index].c].z);
        m_pSource->m_pData[i].m_vTexCoord = Vector2d(pIndexList[index].c_s,-pIndexList[index].c_t);
        i++;
    }
    
    i = 0;
    for(unsigned short index = 0; index < iTrianglesCount * 3; index += 3)
    {
        m_pSource->m_pIB[i] = index;
        i++;
        m_pSource->m_pIB[i] = index + 1;
        i++;
        m_pSource->m_pIB[i] = index + 2;
        i++;
    }
    
    for(unsigned int i = 0; i < iFramesCount; i++ ) 
	{
        CMesh::SVertex* pSequenceNode = new CMesh::SVertex[m_pSource->m_iNumVertexes];
        unsigned int k = 0;
		for(unsigned int j = 0; j < iTrianglesCount; j++ ) 
		{
            Vector3d vA = Vector3d(pFrameList[i].pV[pIndexList[j].a].x,pFrameList[i].pV[pIndexList[j].a].y,pFrameList[i].pV[pIndexList[j].a].z);
            k++;
            
            Vector3d vB = Vector3d(pFrameList[i].pV[pIndexList[j].b].x,pFrameList[i].pV[pIndexList[j].b].y,pFrameList[i].pV[pIndexList[j].b].z);
            k++;
            
            Vector3d vC = Vector3d(pFrameList[i].pV[pIndexList[j].c].x,pFrameList[i].pV[pIndexList[j].c].y,pFrameList[i].pV[pIndexList[j].c].z);
            k++;
            
            pSequenceNode[k - 1].m_vPosition = vC;
            pSequenceNode[k - 2].m_vPosition = vB;
            pSequenceNode[k - 3].m_vPosition = vA;
            
            Vector3d vD = cross(vC - vA, vB - vA);
            pSequenceNode[k - 1].m_vNormal = vD;
            pSequenceNode[k - 2].m_vNormal = vD;
            pSequenceNode[k - 3].m_vNormal = vD;
		}
        m_pSource->m_pSequence.push_back(pSequenceNode);
	}

    m_eStatus = E_DONE_STATUS;
}

void CParser_MD2::Commit()
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








