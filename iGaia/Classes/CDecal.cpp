//
//  CDecal.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#include "CDecal.h"
#include "CSceneMgr.h"

CDecal::CDecal(void)
{
    
}

CDecal::~CDecal(void)
{
    
}

void CDecal::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    unsigned int iWidth = 7;
    unsigned int iHeight = 7;
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = iWidth * iHeight;
    pSourceData->m_iNumIndexes  = (iWidth - 1) * (iHeight - 1) * 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBuffer(pSourceData->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
    memset(pPositionData, 0x0, pSourceData->m_iNumVertexes * sizeof(glm::vec3));
    
    unsigned int index = 0;
    float fScale = 0.25f;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pPositionData[index] = glm::vec3(static_cast<float>(i) * fScale - 2.0f, 0.0f, static_cast<float>(j) * fScale - 2.0f);
            pTexCoordData[index] = glm::vec2(static_cast<float>(i) / static_cast<float>(iWidth), static_cast<float>(j) / static_cast<float>(iHeight));
            ++index;
        }
    }
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
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
    
    pSourceData->m_pVertexBuffer->Set_Mode(GL_STREAM_DRAW);
    pSourceData->m_pVertexBuffer->CommitToRAM();
    pSourceData->m_pVertexBuffer->CommitFromRAMToVRAM();
    pSourceData->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_SourceData(pSourceData);
}

void CDecal::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CDecal::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CDecal::Update()
{
    //INode::Update();
    /*unsigned int iWidth = 8;
    unsigned int iHeight = 8;
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    unsigned int index = 0;
    for(unsigned int i = 0; i < iWidth; ++i)
    {
        for(unsigned int j = 0; j < iHeight; ++j)
        {
            pPositionData[index].y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + pPositionData[index].x, m_vPosition.z + pPositionData[index].z) + 0.05f;
            ++index;
        }
    }*/
    
    int iRoundPositionX = m_vPosition.x;
    int iRoundPositionZ = m_vPosition.z;
    float* pHeightmapData = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_SourceData();
    unsigned int index = 0;
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    int iHeightmapWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeightmapHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    for(int i = -3; i <= 3; ++i)
    {
        for(int j = -3; j <= 3; ++j)
        {
            if((iRoundPositionX + i) < 0 || (iRoundPositionZ + j) < 0 || (iRoundPositionX + i) >= iHeightmapWidth || (iRoundPositionZ +j) > iHeightmapHeight)
            {
                pPositionData[index].x = iRoundPositionX;
                pPositionData[index].y = pHeightmapData[iRoundPositionX + iRoundPositionZ * iHeightmapWidth] + 0.1f;
                pPositionData[index].z = iRoundPositionZ;
            }
            else
            {
                pPositionData[index].x = iRoundPositionX + i;
                pPositionData[index].y = pHeightmapData[iRoundPositionX + i + (iRoundPositionZ + j) * iHeightmapWidth] + 0.1f;
                pPositionData[index].z = iRoundPositionZ + j;
            }
            index++;
        }
    }
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
}

void CDecal::Render(INode::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
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

            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode] ->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetCustomVector3(m_vPosition, "EXT_CenterPosition");
            m_pShaders[_eMode]->SetCustomFloat(glm::radians(m_vRotation.y), "EXT_Angle");
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode] ->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
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
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaders[_eMode] ->Disable();
}


