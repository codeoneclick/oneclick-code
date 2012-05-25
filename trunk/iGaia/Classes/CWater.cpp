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
    m_iWidth = 64;
    m_iHeight = 64;
    m_fWaterHeight = -0.1f;
}

CWater::~CWater(void)
{
    
}

void CWater::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{     
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 4;
    pSourceData->m_iNumIndexes  = 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBuffer(pSourceData->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
    memset(pPositionData, 0x0, pSourceData->m_iNumVertexes * sizeof(glm::vec3));
    
    pPositionData[0] = glm::vec3( 0.0f,     m_fWaterHeight,  0.0f );
    pPositionData[1] = glm::vec3( m_iWidth, m_fWaterHeight,  0.0f );
    pPositionData[2] = glm::vec3( m_iWidth, m_fWaterHeight,  m_iHeight );
    pPositionData[3] = glm::vec3( 0.0f,     m_fWaterHeight,  m_iHeight );
    
    pTexCoordData[0] = glm::vec2( 0.0f,  0.0f );
    pTexCoordData[1] = glm::vec2( 0.0f,  1.0f );
    pTexCoordData[2] = glm::vec2( 1.0f,  0.0f );
    pTexCoordData[3] = glm::vec2( 1.0f,  1.0f );
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexesBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    pIndexesBufferData[0] = 0;
    pIndexesBufferData[1] = 1;
    pIndexesBufferData[2] = 2;
    pIndexesBufferData[3] = 0;
    pIndexesBufferData[4] = 2;
    pIndexesBufferData[5] = 3;
    
    pSourceData->m_pVertexBuffer->CommitToRAM();
    pSourceData->m_pVertexBuffer->CommitFromRAMToVRAM();
    pSourceData->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_SourceData(pSourceData);
}

void CWater::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CWater::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CWater::Update()
{
    INode::Update();
}

void CWater::Render(INode::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    glDisable(GL_CULL_FACE);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
            m_pShaders[_eMode]->SetTexture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION), CShader::k_TEXTURE_01);
            m_pShaders[_eMode]->SetTexture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION), CShader::k_TEXTURE_02);
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
    
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaders[_eMode]->Disable();
    glEnable(GL_CULL_FACE);
}
