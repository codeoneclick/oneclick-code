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

CBatch::CBatch(CVertexBuffer::E_VERTEX_BUFFER_MODE _eVertexBufferMode)
{
     m_eVertexBufferMode = _eVertexBufferMode;
    
     m_pSource = new CMesh::SSource();
     m_pSource->m_pIB = new CIndexBuffer(4096 * 8);
    
     if(m_eVertexBufferMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN)
     {
         m_pSource->m_pVB = new CVertexBuffer(2048 * 8, sizeof(CVertexBuffer::SVertexVTN),_eVertexBufferMode); 
     }
     else if(m_eVertexBufferMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VC)
     {
         m_pSource->m_pVB = new CVertexBuffer(2048 * 8, sizeof(CVertexBuffer::SVertexVC),_eVertexBufferMode); 
     }
      
     m_pMesh = new CMesh();
     m_pSource->m_iNumVertexes = 0;
     m_pSource->m_iNumIndexes = 0;
     m_eRenderMode = E_RENDER_MODE_TRIANGLES;
}

CBatch::~CBatch()
{
    if(m_pMesh != NULL)
    {
        delete m_pMesh;
        m_pMesh = NULL;
    }
}

void CBatch::Push(SSource _tSource)
{
    m_pSource->m_iNumIndexes += _tSource.m_pMesh->Get_NumIndexes();
    m_pSource->m_iNumVertexes += _tSource.m_pMesh->Get_NumVertexes();
    m_lContainer.push_back(_tSource);
}

void CBatch::MakeBatch()
{
    void* pBatchData = m_pSource->m_pVB->Get_Data();
    unsigned short* pIBData = m_pSource->m_pIB->Get_Data();
    
    std::vector<CBatch::SSource>::iterator itBegin = m_lContainer.begin();
    std::vector<CBatch::SSource>::iterator itEnd = m_lContainer.end();
    
    int iOffset = 0;
    int iIndex = 0;
    while (itBegin != itEnd)
    {
        CMesh* pMesh = (*itBegin).m_pMesh;
        int iNumVertexes = pMesh->Get_NumVertexes();
        void* pNodeData = pMesh->Get_VB()->Get_Data();
        CMatrix4x4 mWorld = (*itBegin).m_mWorld;
        
        for(int i = 0; i < iNumVertexes; ++i)
        {
            if(m_eVertexBufferMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN)
            {
                CVertexBuffer::SVertexVTN* pRefBatchData = static_cast<CVertexBuffer::SVertexVTN*>(pBatchData);
                CVertexBuffer::SVertexVTN* pRefNodeData = static_cast<CVertexBuffer::SVertexVTN*>(pNodeData);
                pRefBatchData->m_vPosition = mWorld * pRefNodeData[i].m_vPosition;
                pRefBatchData->m_vTexCoord = pRefNodeData[i].m_vTexCoord;
                pRefBatchData->m_vNormal = pRefNodeData[i].m_vNormal;
                ++pRefBatchData;
                pBatchData = pRefBatchData;
            }
            else if(m_eVertexBufferMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VC)
            {
                CVertexBuffer::SVertexVC* pRefBatchData = static_cast<CVertexBuffer::SVertexVC*>(pBatchData);
                CVertexBuffer::SVertexVC* pRefNodeData = static_cast<CVertexBuffer::SVertexVC*>(pNodeData);
                pRefBatchData->m_vPosition = mWorld * pRefNodeData[i].m_vPosition;
                pRefBatchData->m_cColor = pRefNodeData[i].m_cColor;
                ++pRefBatchData;
                pBatchData = pRefBatchData;
            }
        }
        int iNumIndexes = pMesh->Get_NumIndexes();
        unsigned short *pNodeIBData = pMesh->Get_IB()->Get_Data();
        for(int i = 0; i < iNumIndexes; ++i)
        {
            pIBData[iIndex] = pNodeIBData[i] + iOffset;
            ++iIndex;
        }
        iOffset += iNumVertexes;
        ++itBegin;
    }
    
    m_pMesh->Set_Source(m_pSource);
}

void CBatch::DestroyBatch()
{
    m_pSource->m_iNumIndexes = 0;
    m_pSource->m_iNumVertexes = 0;
    m_lContainer.clear();
}

void CBatch::Render()
{
    if(m_pSource->m_iNumVertexes == 0)
    {
        return;
    }
    
    MakeBatch();
    
    glCullFace(GL_FRONT);
    m_pShader->Enable();
    m_pShader->SetMatrix(CMatrix4x4(CMatrix4x4::E_MATRIX_ONE), CShader::k_MATRIX_WORLD);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
    
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
    
    m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
    if(m_eRenderMode == E_RENDER_MODE_LINES)
    {
        glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    }
    else if(m_eRenderMode == E_RENDER_MODE_TRIANGLES)
    {
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    }
    m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
    m_pShader->Disable();
    
    DestroyBatch();
}




