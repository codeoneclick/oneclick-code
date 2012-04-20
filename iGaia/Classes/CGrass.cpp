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
    /*m_iWidth = 32;
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

    m_pSingleElementVertexBuffer.m_pPositionData = new glm::vec3[k_ELEMENT_NUM_VERTEXES];
    m_pSingleElementVertexBuffer.m_pPositionData[0] = glm::vec3(-k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    m_pSingleElementVertexBuffer.m_pPositionData[1] = glm::vec3(-k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    m_pSingleElementVertexBuffer.m_pPositionData[2] = glm::vec3( k_ELEMENT_SIZE / 2, 0.0f, 0.0f);
    m_pSingleElementVertexBuffer.m_pPositionData[3] = glm::vec3( k_ELEMENT_SIZE / 2, k_ELEMENT_HEIGHT, 0.0f);
    
    m_pSingleElementVertexBuffer.m_pPositionData[4] = glm::vec3(0.0f, 0.0f, -k_ELEMENT_SIZE / 2);
    m_pSingleElementVertexBuffer.m_pPositionData[5] = glm::vec3(0.0f, k_ELEMENT_HEIGHT, -k_ELEMENT_SIZE / 2);
    m_pSingleElementVertexBuffer.m_pPositionData[6] = glm::vec3(0.0f, 0.0f,  k_ELEMENT_SIZE / 2);
    m_pSingleElementVertexBuffer.m_pPositionData[7] = glm::vec3(0.0f, k_ELEMENT_HEIGHT,  k_ELEMENT_SIZE / 2);
    
    m_pSingleElementVertexBuffer.m_pTexCoordData = new glm::vec2[k_ELEMENT_NUM_VERTEXES];
    m_pSingleElementVertexBuffer.m_pTexCoordData[0] = glm::vec2(0.0f,1.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[1] = glm::vec2(0.0f,0.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[2] = glm::vec2(1.0f,1.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[3] = glm::vec2(1.0f,0.0f);
    
    m_pSingleElementVertexBuffer.m_pTexCoordData[4] = glm::vec2(0.0f,1.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[5] = glm::vec2(0.0f,0.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[6] = glm::vec2(1.0f,1.0f);
    m_pSingleElementVertexBuffer.m_pTexCoordData[7] = glm::vec2(1.0f,0.0f);
    
    m_pHeightMapSetter = NULL;*/
}

CGrass::~CGrass(void)
{
    
}

void CGrass::Load(IResource::SResource _tResource)
{   
    /*m_pHeightMapSetter = CSceneMgr::Instance()->Get_HeightMapSetterRef();
    std::vector<glm::vec3> pElementsSourceData;
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = m_pHeightMapSetter->Get_HeightValueAtPoint(i, j);
            if(fHeight < 0.1f)
            {
                pElementsSourceData.push_back(glm::vec3(i, fHeight, j));
            }
        }
    }
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = pElementsSourceData.size() * k_ELEMENT_NUM_VERTEXES;
    pSource->m_iNumIndexes  = pElementsSourceData.size() * k_ELEMENT_NUM_INDEXES;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    
    glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    glm::vec2* pTextCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
    unsigned short* pIndexesBufferData = pSource->m_pIB->Get_Data();
    
    std::vector<glm::vec3>::iterator pElementsSourceDataBegin = pElementsSourceData.begin();
    std::vector<glm::vec3>::iterator pElementsSourceDataEnd   = pElementsSourceData.end();
    unsigned int iVertexesDataOffset = 0;
    unsigned int iIndexesDataOffset = 0;
    while (pElementsSourceDataBegin != pElementsSourceDataEnd)
    {
        for(unsigned int i = 0; i < k_ELEMENT_NUM_VERTEXES; ++i)
        {
            pPositionData[i + iVertexesDataOffset] = m_pSingleElementVertexBuffer.m_pPositionData[i] + (*pElementsSourceDataBegin);
            pTextCoordData[i +iVertexesDataOffset] = m_pSingleElementVertexBuffer.m_pTexCoordData[i];

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
    m_pMesh->Set_Source(pSource);
    m_pMesh->Get_VB()->CommitToRAM();
    m_pMesh->Get_VB()->CommitFromRAMToVRAM();
    m_pMesh->Get_IB()->CommitFromRAMToVRAM();*/
}

void CGrass::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
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

void CGrass::OnTouchEvent(void)
{
    
}

void CGrass::OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale)
{
    
}

void CGrass::Update()
{
    INode::Update();
}

void CGrass::Render(INode::E_RENDER_MODE _eMode)
{      
    /*glDisable(GL_CULL_FACE);
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
    
    glEnable(GL_CULL_FACE);*/
}
