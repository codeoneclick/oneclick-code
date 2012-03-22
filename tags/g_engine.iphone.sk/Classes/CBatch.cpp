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

CBatch::CBatch(void)
{
     m_pSource = new CMesh::SSource();
     m_pSource->m_pIB = new CIndexBuffer(4096 * 8);
     m_pSource->m_pVB = new CVertexBuffer(2048 * 8); 
      
     m_pMesh = new CMesh();
     m_pSource->m_iNumVertexes = 0;
     m_pSource->m_iNumIndexes = 0;
     m_eRenderMode = E_RENDER_MODE_TRIANGLES;
}

CBatch::~CBatch(void)
{
    if(m_pMesh != NULL)
    {
        delete m_pMesh;
        m_pMesh = NULL;
    }
}

void CBatch::Set_Shader(CShader *_pShader)
{
    m_pShader = _pShader;
    if(m_pSource->m_pVB != NULL)
    {
        m_pSource->m_pVB->Set_ShaderRef(m_pShader->Get_ProgramHandle());
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
    unsigned short* pIBData = m_pSource->m_pIB->Get_Data();
    
    std::vector<CBatch::SSource>::iterator itBegin = m_lContainer.begin();
    std::vector<CBatch::SSource>::iterator itEnd = m_lContainer.end();
    
    int iOffset = 0;
    int iIndex = 0;
    while (itBegin != itEnd)
    {
        CMesh* pMesh = (*itBegin).m_pMesh;
        int iNumVertexes = pMesh->Get_NumVertexes();
        glm::mat4x4 mWorld = (*itBegin).m_mWorld;
        
        glm::vec3*   pNodePositionData = NULL;
        glm::vec2*   pNodeTexCoordData = NULL;
        glm::u8vec4* pNodeNormalData   = NULL;
        glm::u8vec4* pNodeTangentData  = NULL;
        glm::u8vec4* pNodeColorData    = NULL;
        
        glm::vec3*   pBatchPositionData = NULL;
        glm::vec2*   pBatchTexCoordData = NULL;
        glm::u8vec4* pBatchNormalData   = NULL;
        glm::u8vec4* pBatchTangentData  = NULL;
        glm::u8vec4* pBatchColorData    = NULL;

        
        if(pMesh->Get_VB()->Get_PositionData())
        {
            pNodePositionData = pMesh->Get_VB()->Get_PositionData();
            pBatchPositionData = m_pSource->m_pVB->CreateOrReUse_PositionData();
        }
        
        if(pMesh->Get_VB()->Get_TexCoordData())
        {
            pNodeTexCoordData = pMesh->Get_VB()->Get_TexCoordData();
            pBatchTexCoordData = m_pSource->m_pVB->CreateOrReUse_TexCoordData();
        }
        
        if(pMesh->Get_VB()->Get_NormalData())
        {
            pNodeNormalData = pMesh->Get_VB()->Get_NormalData();
            pBatchNormalData = m_pSource->m_pVB->CreateOrReUse_NormalData();
        }
        
        if(pMesh->Get_VB()->Get_TangentData())
        {
            pNodeTangentData = pMesh->Get_VB()->Get_TangentData();
            pBatchTangentData = m_pSource->m_pVB->CreateOrReUse_TangentData();
        }
        
        if(pMesh->Get_VB()->Get_ColorData())
        {
            pNodeColorData = pMesh->Get_VB()->Get_ColorData();
            pBatchColorData = m_pSource->m_pVB->CreateOrReUse_ColorData();
        }
        
        for(int i = 0; i < iNumVertexes; ++i)
        {
            if(pBatchPositionData != NULL)
            {
                glm::vec4 vPosition4 = mWorld * glm::vec4(pNodePositionData[i], 1.0f);
                *pBatchPositionData = glm::vec3(vPosition4.x,vPosition4.y,vPosition4.z);
                pBatchPositionData++;
            }
            if(pBatchTexCoordData != NULL)
            {
                *pBatchTexCoordData = pNodeTexCoordData[i];
                pBatchTexCoordData++;
            }
            if(pBatchNormalData != NULL)
            {
                *pBatchNormalData = pNodeNormalData[i];
                pBatchNormalData++;
            }
            if(pBatchTangentData != NULL)
            {
                *pBatchTangentData = pNodeTangentData[i];
                pBatchTangentData++;
            }
            if(pBatchColorData != NULL)
            {
                *pBatchColorData = pNodeColorData[i];
                pBatchColorData++;
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
    
    m_pSource->m_pVB->CommitToRAM();
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
    
    m_pShader->Enable();
    m_pShader->SetMatrix(glm::mat4x4(1.0f), CShader::k_MATRIX_WORLD);
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
    
    m_pMesh->Get_VB()->Enable();
    if(m_eRenderMode == E_RENDER_MODE_LINES)
    {
        glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    }
    else if(m_eRenderMode == E_RENDER_MODE_TRIANGLES)
    {
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    }
    m_pMesh->Get_VB()->Disable();
    m_pShader->Disable();
    
    DestroyBatch();
}




