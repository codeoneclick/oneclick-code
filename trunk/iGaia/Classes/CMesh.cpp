//
//  CMesh.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMesh.h"

CMesh::CMesh()
{
    m_pSourceData = NULL;
    m_eResourceType = E_RESOURCE_TYPE_MESH;
}

CMesh::~CMesh()
{
    delete m_pSourceData->m_pIndexBuffer;
    delete m_pSourceData->m_pVertexBuffer;
    delete m_pSourceData;
}

void CMesh::Set_SourceData(void *_pSourceData)
{
    if(m_pSourceData != NULL && m_pSourceData->m_pVertexBuffer != NULL)
    {
        static_cast<SSourceData*>(_pSourceData)->m_pVertexBuffer->Set_ShaderRef(m_pSourceData->m_pVertexBuffer->Get_ShaderRef());
    }
    m_pSourceData = static_cast<SSourceData*>(_pSourceData);
}
