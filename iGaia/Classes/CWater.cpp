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
    m_fWaterHeight = -0.1f;
}

CWater::~CWater(void)
{
    
}

void CWater::Load(IResource::SResource _tResource)
{     
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
    memset(pPositionData, 0x0, pSource->m_iNumVertexes * sizeof(glm::vec3));
    
    pPositionData[0] = glm::vec3( 0.0f,     m_fWaterHeight,  0.0f );
    pPositionData[1] = glm::vec3( m_iWidth, m_fWaterHeight,  0.0f );
    pPositionData[2] = glm::vec3( m_iWidth, m_fWaterHeight,  m_iHeight );
    pPositionData[3] = glm::vec3( 0.0f,     m_fWaterHeight,  m_iHeight );
    
    pTexCoordData[0] = glm::vec2( 0.0f,  0.0f );
    pTexCoordData[1] = glm::vec2( 0.0f,  1.0f );
    pTexCoordData[2] = glm::vec2( 1.0f,  0.0f );
    pTexCoordData[3] = glm::vec2( 1.0f,  1.0f );
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 0;
    pIBData[4] = 2;
    pIBData[5] = 3;
    
    pSource->m_pVB->CommitToRAM();
    pSource->m_pVB->CommitFromRAMToVRAM();
    pSource->m_pIB->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
}

void CWater::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
{
    switch (_eType)
    {
        case IResourceLoaderDelegate::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<pResource->Get_Name()<<"\n";
            break;
        case IResourceLoaderDelegate::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CWater::OnTouchEvent(void)
{
    
}

void CWater::OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale)
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
            m_pShader->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            if(m_pLight != NULL)
            {
                m_pShader->SetVector3(m_pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
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
            m_pShader->SetTexture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION), CShader::k_TEXTURE_01);
            m_pShader->SetTexture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION), CShader::k_TEXTURE_02);
        }
            break;
        case INode::E_RENDER_MODE_EDGE_DETECT:
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
