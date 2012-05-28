//
//  CBoundingBox.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBoundingBox.h"
#include "CShaderComposite.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionColor.h"

const float CBoundingBox::k_MAX_VALUE = -4096.0f;
const float CBoundingBox::k_MIN_VALUE = 4096.0f;

CMesh* CBoundingBox::m_pMesh = NULL;

CMesh* CBoundingBox::Get_BoundingBoxMesh(void)
{
    if(m_pMesh == NULL)
    {
        glm::vec3 m_vMin = glm::vec3( -0.5f, -1.0f, -0.5f);
        glm::vec3 m_vMax = glm::vec3(  0.5f,  0.0f,  0.5f);

        CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
        pSourceData->m_iNumVertexes = 8;
        pSourceData->m_iNumIndexes  = 24;
    
        pSourceData->m_pVertexBuffer = new CVertexBufferPositionColor(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
        
        CVertexBufferPositionColor::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionColor::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
        //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
        //glm::u8vec4* pColorData = pSourceData->m_pVertexBuffer->GetOrCreate_ColorSourceData();
    
        pVertexBufferData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
        pVertexBufferData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
        pVertexBufferData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
        pVertexBufferData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    
        pVertexBufferData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
        pVertexBufferData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
        pVertexBufferData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
        pVertexBufferData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    
        for(unsigned int i = 0; i < pSourceData->m_iNumVertexes; i++)
        {
            pColorData[i] = glm::u8vec4(0, 255, 0, 255);
        }
    
        pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
        unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
        pIndexBufferData[0] = 0;
        pIndexBufferData[1] = 1;
        pIndexBufferData[2] = 0;
        pIndexBufferData[3] = 3;
        pIndexBufferData[4] = 3;
        pIndexBufferData[5] = 2;
        pIndexBufferData[6] = 1;
        pIndexBufferData[7] = 2;
    
        pIndexBufferData[8] = 4;
        pIndexBufferData[9] = 5;
        pIndexBufferData[10] = 4;
        pIndexBufferData[11] = 7;
        pIndexBufferData[12] = 7;
        pIndexBufferData[13] = 6;
        pIndexBufferData[14] = 5;
        pIndexBufferData[15] = 6;
    
        pIndexBufferData[16] = 0;
        pIndexBufferData[17] = 4;
        pIndexBufferData[18] = 1;
        pIndexBufferData[19] = 7;
        pIndexBufferData[20] = 2;
        pIndexBufferData[21] = 6;
        pIndexBufferData[22] = 3;
        pIndexBufferData[23] = 5;
    
        m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
        m_pMesh->Set_SourceData(pSourceData);
        m_pMesh->Get_VertexBufferRef()->AppendWorkingSourceData();
        m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
        m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
    }
    return m_pMesh;
}

CBoundingBox::CBoundingBox(const glm::vec3 &_vMax, const glm::vec3 &_vMin)
{
    m_vMax = _vMax;
    m_vMin = _vMin;
    
    m_vScale = m_vMin - m_vMax;
    
    m_mWorld = glm::mat4x4(1.0f);
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    Get_BoundingBoxMesh();
    
    m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
}

CBoundingBox::~CBoundingBox()
{
    
}

void CBoundingBox::Set_WorldMatrix(const glm::mat4x4& _mWorld)
{
    glm::mat4x4 mScale = glm::scale(glm::mat4x4(1.0),m_vScale);
    m_mWorld = _mWorld * mScale;
}

void CBoundingBox::Set_MaxMinPoints(const glm::vec3 &_vMax, const glm::vec3 &_vMin)
{
    m_vMax = _vMax;
    m_vMin = _vMin;
    m_vScale = m_vMin - m_vMax;
}

void CBoundingBox::Render()
{
    m_pShader->Enable();
    m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShader->Disable();
}


