//
//  CCrossBoxEffect.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CCrossBoxEffect.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"

const int CCrossBoxEffect::k_ELEMENT_NUM_INDEXES = 12;
const int CCrossBoxEffect::k_ELEMENT_NUM_VERTEXES = 8;

CCrossBoxEffect::CCrossBoxEffect(void)
{
    m_vSize = glm::vec2(1.0f, 1.0f);
    m_iTotalFrames = 0;
    m_iCurrentFrame = 0;
}

CCrossBoxEffect::~CCrossBoxEffect(void)
{
    
}

void CCrossBoxEffect::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = k_ELEMENT_NUM_VERTEXES;
    pSourceData->m_iNumIndexes  = k_ELEMENT_NUM_INDEXES;
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();

    pIndexBufferData[0] = 0;
    pIndexBufferData[1] = 1;
    pIndexBufferData[2] = 2;
    pIndexBufferData[3] = 2;
    pIndexBufferData[4] = 3;
    pIndexBufferData[5] = 1;
    
    pIndexBufferData[6]  = 4;
    pIndexBufferData[7]  = 5;
    pIndexBufferData[8]  = 6;
    pIndexBufferData[9]  = 6;
    pIndexBufferData[10] = 7;
    pIndexBufferData[11] = 5;
    
    pVertexBufferData[0].m_vPosition = glm::vec3(-m_vSize.x / 2, 0.0f, 0.0f);
    pVertexBufferData[1].m_vPosition = glm::vec3(-m_vSize.x / 2, m_vSize.y, 0.0f);
    pVertexBufferData[2].m_vPosition = glm::vec3( m_vSize.x / 2, 0.0f, 0.0f);
    pVertexBufferData[3].m_vPosition = glm::vec3( m_vSize.x / 2, m_vSize.y, 0.0f);
    
    pVertexBufferData[4].m_vPosition = glm::vec3(0.0f, 0.0f,     -m_vSize.x / 2);
    pVertexBufferData[5].m_vPosition = glm::vec3(0.0f, m_vSize.y,-m_vSize.x / 2);
    pVertexBufferData[6].m_vPosition = glm::vec3(0.0f, 0.0f,      m_vSize.x / 2);
    pVertexBufferData[7].m_vPosition = glm::vec3(0.0f, m_vSize.y, m_vSize.x / 2);
    
    pVertexBufferData[0].m_vTexcoord = glm::vec2(0.0f,1.0f);
    pVertexBufferData[1].m_vTexcoord = glm::vec2(0.0f,0.0f);
    pVertexBufferData[2].m_vTexcoord = glm::vec2(1.0f,1.0f);
    pVertexBufferData[3].m_vTexcoord = glm::vec2(1.0f,0.0f);
    
    pVertexBufferData[4].m_vTexcoord = glm::vec2(0.0f,1.0f);
    pVertexBufferData[5].m_vTexcoord = glm::vec2(0.0f,0.0f);
    pVertexBufferData[6].m_vTexcoord = glm::vec2(1.0f,1.0f);
    pVertexBufferData[7].m_vTexcoord = glm::vec2(1.0f,0.0f);
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_pFrames = new SFrame[m_iNumTextureChunks];
    m_iTotalFrames = m_iNumTextureChunks;
    
    unsigned int m_iNumX = m_vSizeTextureAtlas.x / m_vSizeTextureChunk.x;
    unsigned int m_iNumY = m_vSizeTextureAtlas.y / m_vSizeTextureChunk.y;
    
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iNumX; ++i)
    {
        for(unsigned int j = 0; j < m_iNumY; ++j)
        {
            if(index > m_iNumTextureChunks)
            {
                continue;
            }
            
            m_pFrames[index].m_vTexcoord[0].x = (m_vSizeTextureChunk.x * i) / m_vSizeTextureAtlas.x;
            m_pFrames[index].m_vTexcoord[0].y = (m_vSizeTextureChunk.y * (j + 1)) / m_vSizeTextureAtlas.y;
            
            m_pFrames[index].m_vTexcoord[1].x = (m_vSizeTextureChunk.x * i) / m_vSizeTextureAtlas.x;
            m_pFrames[index].m_vTexcoord[1].y = (m_vSizeTextureChunk.y * j) / m_vSizeTextureAtlas.y;
            
            m_pFrames[index].m_vTexcoord[2].x = (m_vSizeTextureChunk.x * (i + 1)) / m_vSizeTextureAtlas.x;
            m_pFrames[index].m_vTexcoord[2].y = (m_vSizeTextureChunk.y * (j + 1)) / m_vSizeTextureAtlas.y;
            
            m_pFrames[index].m_vTexcoord[3].x = (m_vSizeTextureChunk.x * (i + 1)) / m_vSizeTextureAtlas.x;
            m_pFrames[index].m_vTexcoord[3].y = (m_vSizeTextureChunk.y * j) / m_vSizeTextureAtlas.y;
            
            index++;
        }
    }
}

void CCrossBoxEffect::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CCrossBoxEffect::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CCrossBoxEffect::Update(void)
{
    INode::Update();
    
    m_iCurrentFrame++;
    if(m_iCurrentFrame >= m_iTotalFrames)
    {
        m_iCurrentFrame = 0;
    }
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    
    pVertexBufferData[0].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[0];
    pVertexBufferData[1].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[1];
    pVertexBufferData[2].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[2];
    pVertexBufferData[3].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[3];
    
    pVertexBufferData[4].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[0];
    pVertexBufferData[5].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[1];
    pVertexBufferData[6].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[2];
    pVertexBufferData[7].m_vTexcoord = m_pFrames[m_iCurrentFrame].m_vTexcoord[3];
    
    m_pMesh->Get_VertexBufferRef()->Commit();
}

void CCrossBoxEffect::Render(CShader::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    switch (_eMode)
    {
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CCrossBoxEffect::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
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
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CCrossBoxEffect::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
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
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    unsigned int iNumIndexes = m_pMesh->Get_IndexBufferRef()->Get_NumWorkingIndexes();
    glDrawElements(GL_TRIANGLES, iNumIndexes, GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    m_pShaders[_eMode]->Disable();
    
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}





