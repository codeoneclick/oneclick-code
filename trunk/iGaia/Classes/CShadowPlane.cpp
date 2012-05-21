//
//  CShadowPlane.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/15/12.
//
//
/*
#include "CShadowPlane.h"
#include "CSceneMgr.h"

CShadowPlane::CShadowPlane(void)
{
    
}

CShadowPlane::~CShadowPlane(void)
{
    
}

void CShadowPlane::Load(IResource::SResource _tResource)
{
    unsigned int iWidth = 8;
    unsigned int iHeight = 8;
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = iWidth * iHeight;
    pSource->m_iNumIndexes  = (iWidth - 1) * (iHeight - 1) * 6;
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
    memset(pPositionData, 0x0, pSource->m_iNumVertexes * sizeof(glm::vec3));
    
    unsigned int index = 0;
    float fScale = 0.5f;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pPositionData[index] = glm::vec3(static_cast<float>(i) * fScale - 2.0f, 0.0f, static_cast<float>(j) * fScale - 2.0f);
            pTexCoordData[index] = glm::vec2(static_cast<float>(i) / static_cast<float>(iWidth), static_cast<float>(j) / static_cast<float>(iHeight));
            ++index;
        }
    }

    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSource->m_pIndexBuffer->Get_Data();
    index = 0;
    for(unsigned int i = 0; i < (iWidth - 1); ++i)
    {
        for(unsigned int j = 0; j < (iHeight - 1); ++j)
        {
            pIndexBufferData[index] = i + j * iWidth;
            index++;
            pIndexBufferData[index] = i + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * iWidth;
            index++;
            
            pIndexBufferData[index] = i + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + (j + 1) * iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * iWidth;
            index++;
        }
    }
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
}

void CShadowPlane::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
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

void CShadowPlane::OnTouchEvent(void)
{
    
}

void CShadowPlane::Update()
{
    INode::Update();
    unsigned int iWidth = 8;
    unsigned int iHeight = 8;
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    unsigned int index = 0;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pPositionData[index].y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + pPositionData[index].x, m_vPosition.z + pPositionData[index].z) + 0.25f;
            ++index;
        }
    }
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
}

void CShadowPlane::Render(INode::E_RENDER_MODE _eMode)
{      
    //glDisable(GL_DEPTH_TEST);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
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
        case INode::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_SHADOW_MAP:
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
    
    m_pShader->Disable();
    //glEnable(GL_DEPTH_TEST);
}

*/

