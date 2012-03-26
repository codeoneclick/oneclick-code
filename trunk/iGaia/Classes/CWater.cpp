//
//  CWater.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWater.h"
#include "CSceneMgr.h"

const int CWater::k_ELEMENT_NUM_INDEXES = 6;
const int CWater::k_ELEMENT_NUM_VERTEXES = 4;

CWater::CWater(void)
{
    m_iWidth = 32;
    m_iHeight = 32;
}

CWater::~CWater(void)
{
    
}

void CWater::Load(IResource::SResource _tResource)
{   
    /*CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = k_ELEMENT_NUM_VERTEXES;
    pSource->m_iNumIndexes  = k_ELEMENT_NUM_INDEXES;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    glm::vec2* pTextCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
    pPositionData = new glm::vec3[k_ELEMENT_NUM_VERTEXES];
    pPositionData[0] = glm::vec3(-m_iWidth, 0.2f, -m_iHeight);
    pPositionData[1] = glm::vec3(-m_iWidth, 0.2f,  m_iHeight);
    pPositionData[2] = glm::vec3( m_iWidth, 0.2f, -m_iHeight);
    pPositionData[3] = glm::vec3( m_iWidth, 0.2f,  m_iHeight);
    
    pTextCoordData[0] = glm::vec2(0.0f,0.0f);
    pTextCoordData[1] = glm::vec2(0.0f,1.0f);
    pTextCoordData[2] = glm::vec2(1.0f,0.0f);
    pTextCoordData[3] = glm::vec2(1.0f,1.0f);
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIndexesBufferData = pSource->m_pIB->Get_Data();
    
    pIndexesBufferData[0] = 0;
    pIndexesBufferData[1] = 1;
    pIndexesBufferData[2] = 2;
    
    pIndexesBufferData[3] = 3;
    pIndexesBufferData[4] = 2;
    pIndexesBufferData[5] = 1;*/
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
    glm::vec3 m_vMax = glm::vec3(m_iWidth, -0.1f, m_iHeight);
    glm::vec3 m_vMin = glm::vec3(0.0f, -0.1f, 0.0f);
    
    memset(pPositionData, 0x0, pSource->m_iNumVertexes * sizeof(glm::vec3));
    
    /*pPositionData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
    pPositionData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
    pPositionData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
    pPositionData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);*/
    // Back
    /*pPositionData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);*/
    // Left
    /*pPositionData[8] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[9] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[10] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[11] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right*/
    pPositionData[12] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z );
    pPositionData[13] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z );
    pPositionData[14] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z );
    pPositionData[15] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z );
    
    pTexCoordData[12] = glm::vec2( 0.0f,  0.0f );
    pTexCoordData[13] = glm::vec2( 0.0f,  1.0f );
    pTexCoordData[14] = glm::vec2( 1.0f,  0.0f );
    pTexCoordData[15] = glm::vec2( 1.0f,  1.0f );

    // Top
    /*pPositionData[16] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[17] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[18] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[19] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pPositionData[20] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[21] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pPositionData[22] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[23] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);*/
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
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
    
    pSource->m_pVB->CommitToRAM();
    pSource->m_pVB->CommitFromRAMToVRAM();
    pSource->m_pIB->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
}

void CWater::OnTouchEvent(void)
{
}

void CWater::Update()
{
    INode::Update();
}

void CWater::Render(INode::E_RENDER_MODE _eMode)
{      
    glDisable(GL_CULL_FACE);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
            m_pShader->Enable();
            m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
            m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            if(m_pLight != NULL)
            {
                m_pShader->SetVector(m_pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            }
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShader->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
            m_pShader->SetTexture(CSceneMgr::Instance()->Get_RenderMgr()->Get_ReflectionTextureHandle(), CShader::k_TEXTURE_01);
        }
            break;
        case INode::E_RENDER_MODE_EDGE_DETECTED:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
    m_pMesh->Get_VB()->Disable();
    
    m_pShader->Disable();
    glEnable(GL_CULL_FACE);
}
