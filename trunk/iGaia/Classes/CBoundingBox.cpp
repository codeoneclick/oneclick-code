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

const float CBoundingBox::k_MAX_VALUE = -4096.0f;
const float CBoundingBox::k_MIN_VALUE = 4096.0f;

CMesh* CBoundingBox::m_pMesh = NULL;

CMesh* CBoundingBox::Get_BoundingBoxMesh(void)
{
    if(m_pMesh == NULL)
    {
        glm::vec3 m_vMin = glm::vec3( -0.5f, -1.0f, -0.5f);
        glm::vec3 m_vMax = glm::vec3(  0.5f,  0.0f,  0.5f);

        CMesh::SSource* pSource = new CMesh::SSource();
        pSource->m_iNumVertexes = 8;
        pSource->m_iNumIndexes  = 24;
    
        pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
        
        glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
        glm::u8vec4* pColorData = pSource->m_pVertexBuffer->CreateOrReUse_ColorData();
    
        pPositionData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
        pPositionData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
        pPositionData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
        pPositionData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    
        pPositionData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
        pPositionData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
        pPositionData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
        pPositionData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    
        for(unsigned int i = 0; i < pSource->m_iNumVertexes; i++)
        {
            pColorData[i] = glm::u8vec4(0, 255, 0, 255);
        }
    
        pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
        unsigned short* pIBData = pSource->m_pIndexBuffer->Get_Data();
    
        pIBData[0] = 0;
        pIBData[1] = 1;
        pIBData[2] = 0;
        pIBData[3] = 3;
        pIBData[4] = 3;
        pIBData[5] = 2;
        pIBData[6] = 1;
        pIBData[7] = 2;
    
        pIBData[8] = 4;
        pIBData[9] = 5;
        pIBData[10] = 4;
        pIBData[11] = 7;
        pIBData[12] = 7;
        pIBData[13] = 6;
        pIBData[14] = 5;
        pIBData[15] = 6;
    
        pIBData[16] = 0;
        pIBData[17] = 4;
        pIBData[18] = 1;
        pIBData[19] = 7;
        pIBData[20] = 2;
        pIBData[21] = 6;
        pIBData[22] = 3;
        pIBData[23] = 5;
    
        m_pMesh = new CMesh();
        m_pMesh->Set_Source(pSource);
        m_pMesh->Get_VertexBufferRef()->CommitToRAM();
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

void CBoundingBox::Set_WorldMatrix(const glm::mat4x4& _mWorld)
{
    glm::mat4x4 mScale = glm::scale(glm::mat4x4(1.0),m_vScale);
    m_mWorld = mScale * _mWorld;
}

CBoundingBox::~CBoundingBox()
{
    
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
    glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShader->Disable();
}


