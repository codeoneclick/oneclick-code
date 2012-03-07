//
//  CMeshComposite.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMeshComposite.h"

CMeshComposite* CMeshComposite::m_pInstance = NULL;

CMeshComposite::CMeshComposite()
{
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6;
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 2;
    pIBData[4] = 3;
    pIBData[5] = 0;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    
    CVector3d* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    CVector2d* pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    CByteVector3d* pNormalData = pSource->m_pVB->CreateOrReUse_NormalData();
    
    
    pPositionData[0] = CVector3d(-0.5f, -0.5f, 0.0f);
    pPositionData[1] = CVector3d(-0.5f,  0.5f, 0.0f);
    pPositionData[2] = CVector3d( 0.5f,  0.5f, 0.0f);
    pPositionData[3] = CVector3d( 0.5f, -0.5f, 0.0f);
    
    pNormalData[0] = CByteVector3d(CVector3d(0.0f, 0.0f, 1.0f));
    pNormalData[1] = CByteVector3d(CVector3d(0.0f, 0.0f, 1.0f));
    pNormalData[2] = CByteVector3d(CVector3d(0.0f, 0.0f, 1.0f));
    pNormalData[3] = CByteVector3d(CVector3d(0.0f, 0.0f, 1.0f));
    
    pTexCoordData[0] = CVector2d(0.0f, 0.0f);
    pTexCoordData[1] = CVector2d(0.0f, 1.0f);
    pTexCoordData[2] = CVector2d(1.0f, 1.0f);
    pTexCoordData[3] = CVector2d(1.0f, 0.0f);
    
    pSource->m_pVB->CommitToRAM();
    pSource->m_pVB->CommitFromRAMToVRAM();

    CMesh* pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("plane");
    
    m_lContainer[IResource::E_STANDART_MODEL_PLANE] = pMesh;
    
    pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    
    pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    pNormalData = pSource->m_pVB->CreateOrReUse_NormalData();
    
    CVector3d m_vMin = CVector3d( -0.5f, -0.5f, -0.5f);
    CVector3d m_vMax = CVector3d(  0.5f,  0.5f,  0.5f);
    
    // Front
    pPositionData[0] = CVector3d( m_vMin.x,  m_vMin.y, m_vMax.z);
    pPositionData[1] = CVector3d( m_vMax.x,  m_vMin.y, m_vMax.z);
    pPositionData[2] = CVector3d( m_vMax.x,  m_vMax.y, m_vMax.z);
    pPositionData[3] = CVector3d( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pPositionData[4] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[5] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[6] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[7] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pPositionData[8] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[9] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[10] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[11] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pPositionData[12] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[13] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[14] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pPositionData[15] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pPositionData[16] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[17] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[18] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[19] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pPositionData[20] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[21] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pPositionData[22] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[23] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    // Front
    pTexCoordData[0] = CVector2d(1.0f, 0.0f);
    pTexCoordData[1] = CVector2d(1.0f, 1.0f);
    pTexCoordData[2] = CVector2d(0.0f, 1.0f);
    pTexCoordData[3] = CVector2d(0.0f, 0.0f);
    // Back
    pTexCoordData[4] = CVector2d(1.0f, 0.0f);
    pTexCoordData[5] = CVector2d(1.0f, 1.0f);
    pTexCoordData[6] = CVector2d(0.0f, 1.0f);
    pTexCoordData[7] = CVector2d(0.0f, 0.0f);
    // Left
    pTexCoordData[8] = CVector2d(1.0f, 0.0f);
    pTexCoordData[9] = CVector2d(1.0f, 1.0f);
    pTexCoordData[10] = CVector2d(0.0f, 1.0f);
    pTexCoordData[11] = CVector2d(0.0f, 0.0f);
    // Right
    pTexCoordData[12] = CVector2d(1.0f, 0.0f);
    pTexCoordData[13] = CVector2d(1.0f, 1.0f);
    pTexCoordData[14] = CVector2d(0.0f, 1.0f);
    pTexCoordData[15] = CVector2d(0.0f, 0.0f);
    // Top
    pTexCoordData[16] = CVector2d(1.0f, 0.0f);
    pTexCoordData[17] = CVector2d(1.0f, 1.0f);
    pTexCoordData[18] = CVector2d(0.0f, 1.0f);
    pTexCoordData[19] = CVector2d(0.0f, 0.0f);
    // Bottom
    pTexCoordData[20] = CVector2d(1.0f, 0.0f);
    pTexCoordData[21] = CVector2d(1.0f, 1.0f);
    pTexCoordData[22] = CVector2d(0.0f, 1.0f);
    pTexCoordData[23] = CVector2d(0.0f, 0.0f);
    
    pSource->m_pVB->CommitToRAM();
    pSource->m_pVB->CommitFromRAMToVRAM();
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    pIBData = pSource->m_pIB->Get_Data();
    
    // Front
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 0;
    pIBData[4] = 2;
    pIBData[5] = 3;
    // Back
    pIBData[6] = 4;
    pIBData[7] = 5;
    pIBData[8] = 6;
    pIBData[9] = 4;
    pIBData[10] = 6;
    pIBData[11] = 7;
    // Left
    pIBData[12] = 8;
    pIBData[13] = 9;
    pIBData[14] = 10;
    pIBData[15] = 8;
    pIBData[16] = 10;
    pIBData[17] = 11;
    // Right
    pIBData[18] = 12;
    pIBData[19] = 13;
    pIBData[20] = 14;
    pIBData[21] = 12;
    pIBData[22] = 14;
    pIBData[23] = 15;
    // Top
    pIBData[24] = 16;
    pIBData[25] = 17;
    pIBData[26] = 18;
    pIBData[27] = 16;
    pIBData[28] = 18;
    pIBData[29] = 19;
    // Bottom
    pIBData[30] = 20;
    pIBData[31] = 21;
    pIBData[32] = 22;
    pIBData[33] = 20;
    pIBData[34] = 22;
    pIBData[35] = 23;
    
    pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("cube");
    
    m_lContainer[IResource::E_STANDART_MODEL_CUBE] = pMesh;
}

CMeshComposite::~CMeshComposite()
{
    
}

CMeshComposite* CMeshComposite::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CMeshComposite();
    }
    return m_pInstance;
}

CMesh* CMeshComposite::Get_Mesh(IResource::E_STANDART_MODEL _eMesh)
{
    CMesh* pMesh = NULL;
    if( m_lContainer.find(_eMesh) != m_lContainer.end())
    {
        pMesh = m_lContainer[_eMesh];
        return pMesh;
    }
    else
    {
        return pMesh;
    }
}