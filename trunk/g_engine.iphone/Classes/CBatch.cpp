//
//  CBatch.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBatch.h"
#include "CSceneMgr.h"

CBatch::CBatch()
{
    m_iNumIndexes = 0;
    m_iNumVertexes = 0;
    m_pMesh = NULL;
    m_mWorld = Matrix4x4(Matrix4x4::E_MATRIX_ONE);
    
    m_pSource = new CMesh::SSource();
    m_pSource->m_pIB = new unsigned short[4096];
    m_pSource->m_pVB = new CVertexBuffer(2048, sizeof(CVertexBuffer::SVertex));
    
    m_pMesh = new CMesh();
}

CBatch::~CBatch()
{
    if(m_pMesh != NULL)
    {
        delete m_pMesh;
        m_pMesh = NULL;
    }

}

void CBatch::Clear()
{
    m_iNumIndexes = 0;
    m_iNumVertexes = 0;
    m_lContainer.clear();
}

void CBatch::Push(INode *_pNode)
{
    m_iNumIndexes += _pNode->Get_Mesh()->Get_NumIndexes();
    m_iNumVertexes += _pNode->Get_Mesh()->Get_NumVertexes();
    m_lContainer.push_back(_pNode);
}

void CBatch::Create()
{
    m_pSource->m_iNumVertexes = m_iNumVertexes;
    m_pSource->m_iNumIndexes  = m_iNumIndexes;
    CVertexBuffer::SVertex* pBatchData = static_cast<CVertexBuffer::SVertex*>(m_pSource->m_pVB->Get_Data());
    
    std::vector<INode*>::iterator itBegin = m_lContainer.begin();
    std::vector<INode*>::iterator itEnd = m_lContainer.end();
    
    int iOffset = 0;
    int iIndex = 0;
    while (itBegin != itEnd)
    {
        INode* pNode = (*itBegin);
        int iNumVertexes = pNode->Get_Mesh()->Get_NumVertexes();
        CVertexBuffer::SVertex* pNodeData = static_cast<CVertexBuffer::SVertex*>(pNode->Get_Mesh()->Get_VB()->Get_Data());
        Matrix4x4 mWorld = pNode->Get_WorldMatrix();
        
        for(int i = 0; i < iNumVertexes; ++i)
        {
            pBatchData->m_vPosition = mWorld * pNodeData[i].m_vPosition;
            pBatchData->m_vNormal = mWorld * pNodeData[i].m_vNormal;
            pBatchData->m_vTexCoord = pNodeData[i].m_vTexCoord;
            ++pBatchData;
        }
        int iNumIndexes = pNode->Get_Mesh()->Get_NumIndexes();
        unsigned short *pNodeIB = pNode->Get_Mesh()->Get_IB();
        for(int i = 0; i < iNumIndexes; ++i)
        {
            m_pSource->m_pIB[iIndex] = pNodeIB[i] + iOffset;
            ++iIndex;
        }
        iOffset += iNumVertexes;
        
        m_pTextures = pNode->Get_Textures();
        m_pShader = pNode->Get_Shader();
        ++itBegin;
    }
    
    m_pMesh->Set_Source(m_pSource);
}

void CBatch::Render()
{
    if(m_lContainer.size() == 0)
    {
        return;
    }
    
    Create();
    glCullFace(GL_FRONT);
    m_pShader->Enable();
    m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_pShader->SetMatrix(CCamera::Instance()->Get_Projection(), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix(CCamera::Instance()->Get_View(), CShader::k_MATRIX_VIEW);
    m_pShader->SetVector(CCamera::Instance()->Get_Position(), CShader::k_VECTOR_VIEW);
    m_pShader->SetVector(CSceneMgr::Instance()->Get_Light()->Get_Position(), CShader::k_VECTOR_LIGHT);
    
    if( m_pTextures[0] != NULL)
    {
        m_pShader->SetTexture(m_pTextures[0]->Get_Handle(), CShader::k_TEXTURE_01);
    }
    if( m_pTextures[1] != NULL)
    {
        m_pShader->SetTexture(m_pTextures[1]->Get_Handle(), CShader::k_TEXTURE_02);
    }
    if( m_pTextures[2] != NULL)
    {
        m_pShader->SetTexture(m_pTextures[2]->Get_Handle(), CShader::k_TEXTURE_03);
    }
    if( m_pTextures[3] != NULL)
    {
        m_pShader->SetTexture(m_pTextures[3]->Get_Handle(), CShader::k_TEXTURE_04);
    }
    m_pShader->SetColor(m_vColor);
    
    m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB());
    m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
    m_pShader->Disable();

}




