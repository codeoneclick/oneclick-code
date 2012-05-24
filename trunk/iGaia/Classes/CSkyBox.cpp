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

void CSkyBox::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{     
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 24;
    pSourceData->m_iNumIndexes  = 36;
    
    pSourceData->m_pVertexBuffer = new CVertexBuffer(pSourceData->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
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
    pTexCoordData[0] = glm::vec2(0.0f, 0.0f);
    pTexCoordData[1] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[2] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[3] = glm::vec2(0.0f, 1.0f);
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
    pTexCoordData[12] = glm::vec2(0.0f, 0.0f);
    pTexCoordData[13] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[14] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[15] = glm::vec2(0.0f, 1.0f);
    // Top
    pTexCoordData[16] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[17] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[18] = glm::vec2(0.0f, 1.0f);
    pTexCoordData[19] = glm::vec2(0.0f, 0.0f);
    // Bottom
    pTexCoordData[20] = glm::vec2(0.0f, 0.0f);
    pTexCoordData[21] = glm::vec2(1.0f, 0.0f);
    pTexCoordData[22] = glm::vec2(1.0f, 1.0f);
    pTexCoordData[23] = glm::vec2(0.0f, 1.0f);
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
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
    
    pSourceData->m_pVertexBuffer->CommitToRAM();
    pSourceData->m_pVertexBuffer->CommitFromRAMToVRAM();
    pSourceData->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_SourceData(pSourceData);
}

void CSkyBox::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CSkyBox::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CSkyBox::Update()
{
    INode::Update();
}

void CSkyBox::Render(INode::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
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
    glEnable(GL_DEPTH_TEST);
}




