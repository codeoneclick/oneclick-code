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
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVTN), CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);
    CVertexBuffer::SVertexVTN* pVBData = static_cast<CVertexBuffer::SVertexVTN*>(pSource->m_pVB->Get_Data());
    
    pVBData[0].m_vPosition = CVector3d(-1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
    pVBData[1].m_vPosition = CVector3d(-1.0f / 2.0f,  1.0f / 2.0f, 0.0f);
    pVBData[2].m_vPosition = CVector3d( 1.0f / 2.0f,  1.0f / 2.0f, 0.0f);
    pVBData[3].m_vPosition = CVector3d( 1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
    
    pVBData[0].m_vNormal = CVector3d(0.0f, 0.0f, 1.0f);
    pVBData[1].m_vNormal = CVector3d(0.0f, 0.0f, 1.0f);
    pVBData[2].m_vNormal = CVector3d(0.0f, 0.0f, 1.0f);
    pVBData[3].m_vNormal = CVector3d(0.0f, 0.0f, 1.0f);
    
    pVBData[0].m_vTexCoord = CVector2d(0.0f, 0.0f);
    pVBData[1].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[2].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[3].m_vTexCoord = CVector2d(1.0f, 0.0f);
    
    pSource->m_pVB->Commit();

    CMesh* pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("plane");
    
    m_lContainer[IResource::E_STANDART_MODEL_PLANE] = pMesh;
    
    pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVTN), CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);
    pVBData = static_cast<CVertexBuffer::SVertexVTN*>(pSource->m_pVB->Get_Data());
    
    CVector3d m_vMin = CVector3d( -0.5f, -0.5f, -0.5f);
    CVector3d m_vMax = CVector3d(  0.5f,  0.5f,  0.5f);
    
    // Front
    pVBData[0].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y, m_vMax.z);
    pVBData[1].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y, m_vMax.z);
    pVBData[2].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y, m_vMax.z);
    pVBData[3].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pVBData[4].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVBData[5].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVBData[6].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVBData[7].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pVBData[8].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pVBData[9].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pVBData[10].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pVBData[11].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pVBData[12].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVBData[13].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pVBData[14].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pVBData[15].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pVBData[16].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pVBData[17].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pVBData[18].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pVBData[19].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pVBData[20].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pVBData[21].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pVBData[22].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pVBData[23].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    // Front
    pVBData[0].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[1].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[2].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[3].m_vTexCoord = CVector2d(0.0f, 0.0f);
    // Back
    pVBData[4].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[5].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[6].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[7].m_vTexCoord = CVector2d(0.0f, 0.0f);
    // Left
    pVBData[8].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[9].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[10].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[11].m_vTexCoord = CVector2d(0.0f, 0.0f);
    // Right
    pVBData[12].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[13].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[14].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[15].m_vTexCoord = CVector2d(0.0f, 0.0f);
    // Top
    pVBData[16].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[17].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[18].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[19].m_vTexCoord = CVector2d(0.0f, 0.0f);
    // Bottom
    pVBData[20].m_vTexCoord = CVector2d(1.0f, 0.0f);
    pVBData[21].m_vTexCoord = CVector2d(1.0f, 1.0f);
    pVBData[22].m_vTexCoord = CVector2d(0.0f, 1.0f);
    pVBData[23].m_vTexCoord = CVector2d(0.0f, 0.0f);
    
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