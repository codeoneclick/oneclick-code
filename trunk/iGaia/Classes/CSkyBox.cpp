//
//  CSkyBox.cpp
//  iGaia
//
//  Created by sergey sergeev on 4/26/12.
//
//

#include "CSkyBox.h"

#include "CSceneMgr.h"


CSkyBox::CSkyBox(void)
{

}

CSkyBox::~CSkyBox(void)
{
    
}

void CSkyBox::Load(IResource::SResource _tResource)
{     
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
    glm::vec3 m_vMin = glm::vec3( -1.0f, -1.0f, -1.0f);
    glm::vec3 m_vMax = glm::vec3(  1.0f,  1.0f,  1.0f);
    
    // Front
    pPositionData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
    pPositionData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
    pPositionData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
    pPositionData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pPositionData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pPositionData[8] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[9] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[10] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[11] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pPositionData[12] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[13] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[14] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pPositionData[15] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pPositionData[16] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[17] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[18] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[19] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pPositionData[20] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[21] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pPositionData[22] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[23] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    // Front
    pTexCoordData[0] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[1] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[2] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[3] = glm::vec2(0.0f, 0.0f);
    // Back
    pTexCoordData[4] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[5] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[6] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[7] = glm::vec2(0.0f, 0.0f);
    // Left
    pTexCoordData[8] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[9] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[10] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[11] = glm::vec2(0.0f, 0.0f);
    // Right
    pTexCoordData[12] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[13] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[14] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[15] = glm::vec2(0.0f, 0.0f);
    // Top
    pTexCoordData[16] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[17] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[18] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[19] = glm::vec2(0.0f, 0.0f);
    // Bottom
    pTexCoordData[20] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[21] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[22] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[23] = glm::vec2(0.0f, 0.0f);
    
    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSource->m_pIndexBuffer->Get_Data();
    
    // Front
    pIndexBufferData[0] = 0;
    pIndexBufferData[1] = 1;
    pIndexBufferData[2] = 2;
    pIndexBufferData[3] = 0;
    pIndexBufferData[4] = 2;
    pIndexBufferData[5] = 3;
    // Back
    pIndexBufferData[6] = 4;
    pIndexBufferData[7] = 5;
    pIndexBufferData[8] = 6;
    pIndexBufferData[9] = 4;
    pIndexBufferData[10] = 6;
    pIndexBufferData[11] = 7;
    // Left
    pIndexBufferData[12] = 8;
    pIndexBufferData[13] = 9;
    pIndexBufferData[14] = 10;
    pIndexBufferData[15] = 8;
    pIndexBufferData[16] = 10;
    pIndexBufferData[17] = 11;
    // Right
    pIndexBufferData[18] = 12;
    pIndexBufferData[19] = 13;
    pIndexBufferData[20] = 14;
    pIndexBufferData[21] = 12;
    pIndexBufferData[22] = 14;
    pIndexBufferData[23] = 15;
    // Top
    pIndexBufferData[24] = 16;
    pIndexBufferData[25] = 17;
    pIndexBufferData[26] = 18;
    pIndexBufferData[27] = 16;
    pIndexBufferData[28] = 18;
    pIndexBufferData[29] = 19;
    // Bottom
    pIndexBufferData[30] = 20;
    pIndexBufferData[31] = 21;
    pIndexBufferData[32] = 22;
    pIndexBufferData[33] = 20;
    pIndexBufferData[34] = 22;
    pIndexBufferData[35] = 23;
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pVertexBuffer->CommitFromRAMToVRAM();
    pSource->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
}

void CSkyBox::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
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

void CSkyBox::OnTouchEvent(void)
{
    
}

void CSkyBox::Update()
{
    INode::Update();
}

void CSkyBox::Render(INode::E_RENDER_MODE _eMode)
{      
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
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
            
            /*char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShader->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }*/
            m_pShader->SetTextureCube(m_pTextures[0]->Get_Handle(),CShader::k_TEXTURE_CUBE);
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
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}




