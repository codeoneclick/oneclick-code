//
//  CGrass.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGrass.h"
#include "CSceneMgr.h"

const float CGrass::k_ELEMENT_SIZE = 0.5f;
const float CGrass::k_ELEMENT_HEIGHT = 0.5f;
const int CGrass::k_ELEMENT_NUM_INDEXES = 12;
const int CGrass::k_ELEMENT_NUM_VERTEXES = 8;

CGrass::CGrass(void)
{
    m_iWidth = 32;
    m_iHeight = 32;
    
    m_pSingleElementIndexBuffer = new unsigned short[k_ELEMENT_NUM_INDEXES];
    m_pSingleElementIndexBuffer[0] = 0;
    m_pSingleElementIndexBuffer[1] = 1;
    m_pSingleElementIndexBuffer[2] = 2;
    m_pSingleElementIndexBuffer[3] = 2;
    m_pSingleElementIndexBuffer[4] = 3;
    m_pSingleElementIndexBuffer[5] = 1;
    
    m_pSingleElementIndexBuffer[6]  = 4;
    m_pSingleElementIndexBuffer[7]  = 5;
    m_pSingleElementIndexBuffer[8]  = 6;
    m_pSingleElementIndexBuffer[9]  = 6;
    m_pSingleElementIndexBuffer[10] = 7;
    m_pSingleElementIndexBuffer[11] = 5;
    
    m_pSingleElementVertexBuffer = new CVertexBuffer(k_ELEMENT_NUM_VERTEXES);
    glm::vec3* pPositionData = m_pSingleElementVertexBuffer->CreateOrReUse_PositionData();

    pPositionData[0] = glm::vec3(-k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    pPositionData[1] = glm::vec3(-k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    pPositionData[2] = glm::vec3( k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    pPositionData[3] = glm::vec3( k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    
    pPositionData[4] = glm::vec3(0.0f, 0.0f, -k_ELEMENT_SIZE / 2);
    pPositionData[5] = glm::vec3(0.0f, k_ELEMENT_HEIGHT, -k_ELEMENT_SIZE / 2);
    pPositionData[6] = glm::vec3(0.0f, 0.0f,  k_ELEMENT_SIZE / 2);
    pPositionData[7] = glm::vec3(0.0f, k_ELEMENT_HEIGHT,  k_ELEMENT_SIZE / 2);
    
    glm::vec2* pTexCoordData = m_pSingleElementVertexBuffer->CreateOrReUse_TexCoordData();
    
    pTexCoordData[0] = glm::vec2(0.0f,1.0f);
    pTexCoordData[1] = glm::vec2(0.0f,0.0f);
    pTexCoordData[2] = glm::vec2(1.0f,1.0f);
    pTexCoordData[3] = glm::vec2(1.0f,0.0f);
    
    pTexCoordData[4] = glm::vec2(0.0f,1.0f);
    pTexCoordData[5] = glm::vec2(0.0f,0.0f);
    pTexCoordData[6] = glm::vec2(1.0f,1.0f);
    pTexCoordData[7] = glm::vec2(1.0f,0.0f);
    
    m_pHeightMapSetter = NULL;
}

CGrass::~CGrass(void)
{
    
}

void CGrass::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{   
    m_pHeightMapSetter = CSceneMgr::Instance()->Get_HeightMapSetterRef();
    std::vector<glm::vec3> pElementsSourceData;
    
    srand(time(NULL));
    
    for(unsigned int i = 1; i < (m_iWidth - 1); i += 1)
    {
        for(unsigned int j = 1; j < (m_iHeight - 1); j += 1)
        {
           
            float fRange = 0.9f - 0.1f;
            float fOffetX = 0.1f + float(fRange * rand() / (RAND_MAX + 1.0f));
            float fOffetY = 0.1f + float(fRange * rand() / (RAND_MAX + 1.0f));
            
            float fHeight = m_pHeightMapSetter->Get_HeightValue(i + fOffetX, j + fOffetY);
            if(fHeight < 1.25f && fHeight > 0.05f)
            {
                pElementsSourceData.push_back(glm::vec3(i + fOffetX, fHeight + 0.025f, j + fOffetY));
            }
        }
    }
    
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = pElementsSourceData.size() * k_ELEMENT_NUM_VERTEXES;
    pSourceData->m_iNumIndexes  = pElementsSourceData.size() * k_ELEMENT_NUM_INDEXES;
    
    pSourceData->m_pVertexBuffer = new CVertexBuffer(pSourceData->m_iNumVertexes);
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    
    glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTextCoordData = pSourceData->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
    unsigned short* pIndexesBufferData = pSourceData->m_pIndexBuffer->Get_Data();
    
    glm::vec3* pSingleElementPositionData = m_pSingleElementVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pSingleElementTextCoordData = m_pSingleElementVertexBuffer->CreateOrReUse_TexCoordData();
    
    std::vector<glm::vec3>::iterator pElementsSourceDataBegin = pElementsSourceData.begin();
    std::vector<glm::vec3>::iterator pElementsSourceDataEnd   = pElementsSourceData.end();
    unsigned int iVertexesDataOffset = 0;
    unsigned int iIndexesDataOffset = 0;
    while (pElementsSourceDataBegin != pElementsSourceDataEnd)
    {
        for(unsigned int i = 0; i < k_ELEMENT_NUM_VERTEXES; ++i)
        {
            pPositionData[i + iVertexesDataOffset] = pSingleElementPositionData[i] + (*pElementsSourceDataBegin);
            pTextCoordData[i +iVertexesDataOffset] = pSingleElementTextCoordData[i];
        }
        
        for(unsigned int i = 0; i < k_ELEMENT_NUM_INDEXES; ++i)
        {
            pIndexesBufferData[i + iIndexesDataOffset] = m_pSingleElementIndexBuffer[i] + iVertexesDataOffset;
        }
        
        iIndexesDataOffset += k_ELEMENT_NUM_INDEXES;
        iVertexesDataOffset += k_ELEMENT_NUM_VERTEXES;
        ++pElementsSourceDataBegin;
    }
    
    m_pMesh = new CMesh();
    m_pMesh->Set_SourceData(pSourceData);
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
}

void CGrass::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CGrass::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CGrass::Update()
{
    INode::Update();
}

void CGrass::Render(INode::E_RENDER_MODE _eMode)
{
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
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
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            
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
        case INode::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            
        }
            break;
        default:
            break;
    }
         
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaders[_eMode]->Disable();
    
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}
