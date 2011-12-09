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
    
    pSource->m_pIB = new unsigned short[pSource->m_iNumIndexes];
    pSource->m_pIB[0] = 0;
    pSource->m_pIB[1] = 1;
    pSource->m_pIB[2] = 2;
    pSource->m_pIB[3] = 2;
    pSource->m_pIB[4] = 3;
    pSource->m_pIB[5] = 0;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertex));
    CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(pSource->m_pVB->Get_Data());
    
    pData[0].m_vPosition = Vector3d(-1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
    pData[1].m_vPosition = Vector3d(-1.0f / 2.0f,  1.0f / 2.0f, 0.0f);
    pData[2].m_vPosition = Vector3d( 1.0f / 2.0f,  1.0f / 2.0f, 0.0f);
    pData[3].m_vPosition = Vector3d( 1.0f / 2.0f, -1.0f / 2.0f, 0.0f);
    
    pData[0].m_vNormal = Vector3d(0.0f, 0.0f, 1.0f);
    pData[1].m_vNormal = Vector3d(0.0f, 0.0f, 1.0f);
    pData[2].m_vNormal = Vector3d(0.0f, 0.0f, 1.0f);
    pData[3].m_vNormal = Vector3d(0.0f, 0.0f, 1.0f);
    
    pData[0].m_vTexCoord = Vector2d(0.0f, 0.0f);
    pData[1].m_vTexCoord = Vector2d(0.0f, 1.0f);
    pData[2].m_vTexCoord = Vector2d(1.0f, 1.0f);
    pData[3].m_vTexCoord = Vector2d(1.0f, 0.0f);
    
    pSource->m_pVB->Commit();

    CMesh* pMesh = new CMesh();
    pMesh->Set_Source(pSource);
    pMesh->Set_Name("plane");
    
    m_lContainer[IResource::E_PRIMITIVE_PLANE] = pMesh;
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

CMesh* CMeshComposite::Get_Mesh(IResource::E_PRIMITIVE _eMesh)
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