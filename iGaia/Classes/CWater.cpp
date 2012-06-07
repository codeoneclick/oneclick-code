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
#include "CVertexBufferPositionTexcoord.h"

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
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    //memset(pPositionData, 0x0, pSourceData->m_iNumVertexes * sizeof(glm::vec3));
    
    pVertexBufferData[0].m_vPosition = glm::vec3( 0.0f,     m_fWaterHeight,  0.0f );
    pVertexBufferData[1].m_vPosition = glm::vec3( m_iWidth, m_fWaterHeight,  0.0f );
    pVertexBufferData[2].m_vPosition = glm::vec3( m_iWidth, m_fWaterHeight,  m_iHeight );
    pVertexBufferData[3].m_vPosition = glm::vec3( 0.0f,     m_fWaterHeight,  m_iHeight );
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2( 0.0f,  0.0f );
    pVertexBufferData[1].m_vTexcoord = glm::vec2( 0.0f,  1.0f );
    pVertexBufferData[2].m_vTexcoord = glm::vec2( 1.0f,  0.0f );
    pVertexBufferData[3].m_vTexcoord = glm::vec2( 1.0f,  1.0f );
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexesBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    pIndexesBufferData[0] = 0;
    pIndexesBufferData[1] = 1;
    pIndexesBufferData[2] = 2;
    pIndexesBufferData[3] = 0;
    pIndexesBufferData[4] = 2;
    pIndexesBufferData[5] = 3;
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
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

void CWater::Render(CShader::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    glDisable(GL_CULL_FACE);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                m_pShaders[_eMode]->Set_Texture(m_pTextures[i]->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
            m_pShaders[_eMode]->Set_Texture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION), CShader::E_TEXTURE_SLOT_01);
            m_pShaders[_eMode]->Set_Texture(CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION), CShader::E_TEXTURE_SLOT_02);
        }
            break;
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    m_pShaders[_eMode]->Disable();
    glEnable(GL_CULL_FACE);
}