//
//  CParticleEmitter.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleEmitter.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoord.h"


CParticleEmitter::CParticleEmitter(void)
{
    m_iNumParticles = 16;
    m_pParticles = NULL;
}

CParticleEmitter::~CParticleEmitter(void)
{
    std::cout<<"[CParticleEmitter::~CParticleEmitter] delete"<<std::endl;
    SAFE_DELETE_ARRAY(m_pParticles);
}

void CParticleEmitter::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = m_iNumParticles * 4;
    pSourceData->m_iNumIndexes  = m_iNumParticles * 6;
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STREAM_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    //glm::vec3*   pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2*   pTexCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    //glm::u8vec4* pColorData = pSourceData->m_pVertexBuffer->GetOrCreate_ColorSourceData();
    
    m_pParticles = new SParticle[m_iNumParticles];
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        m_pParticles[index].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vColor = glm::u8vec4(0, 0, 0, 0);
        m_pParticles[index].m_fTime = 0.0f;
        m_pParticles[index].m_vSize = glm::vec2(0.5f, 0.5f);
        
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        
        pVertexBufferData[index * 4 + 0].m_vTexcoord = glm::vec2( 0.0f,  0.0f);
        pVertexBufferData[index * 4 + 1].m_vTexcoord = glm::vec2( 1.0f,  0.0f);
        pVertexBufferData[index * 4 + 2].m_vTexcoord = glm::vec2( 1.0f,  1.0f);
        pVertexBufferData[index * 4 + 3].m_vTexcoord = glm::vec2( 0.0f,  1.0f);
        
        /*pColorData[index * 4 + 0] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 1] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 2] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 3] = m_pParticles[index].m_vColor;*/
    }
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        pIndexBufferData[index * 6 + 0] = static_cast<unsigned short>(index * 4 + 0);
        pIndexBufferData[index * 6 + 1] = static_cast<unsigned short>(index * 4 + 1);
        pIndexBufferData[index * 6 + 2] = static_cast<unsigned short>(index * 4 + 2);
        
        pIndexBufferData[index * 6 + 3] = static_cast<unsigned short>(index * 4 + 0);
        pIndexBufferData[index * 6 + 4] = static_cast<unsigned short>(index * 4 + 2);
        pIndexBufferData[index * 6 + 5] = static_cast<unsigned short>(index * 4 + 3);
    }
    
    pSourceData->m_pVertexBuffer->Commit();
    pSourceData->m_pIndexBuffer->Commit();
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    m_pMesh->Set_Name("emitter");
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        float fOffset = _Get_RandomFromRange(0.0f, 0.33f);
        vPosition.x = fOffset;
        fOffset = _Get_RandomFromRange(0.0f, 0.33f);
        vPosition.z = fOffset;
        m_pParticles[i].m_vPosition = vPosition;
    }
}

float CParticleEmitter::_Get_RandomFromRange(float _fMin, float _fMax)
{
    float fRange = _fMax - _fMin;
    return _fMin + float(fRange * rand() / (RAND_MAX + 1.0f)); 
}

void CParticleEmitter::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
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

void CParticleEmitter::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CParticleEmitter::Update(void)
{
    INode::Update();
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        float fUpper = _Get_RandomFromRange(0.0f, 20.0f);
        vPosition.y += fUpper / 500.0f;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vRotation.y += fUpper;
        //m_pParticles[i].m_vRotation.z += fUpper;
        if(m_pParticles[i].m_vPosition.y >= 0.5f)
        {
            m_pParticles[i].m_vPosition.y = 0.0f;
        }
    }
    
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    //glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->GetOrCreate_PositionSourceData();
    //glm::u8vec4* pColorData = m_pMesh->Get_VertexBufferRef()->GetOrCreate_ColorSourceData();
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        glm::mat4x4 mRotationX = glm::rotate(glm::mat4(1.0f), m_pParticles[index].m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4x4 mRotationY = glm::rotate(mRotationX, m_pParticles[index].m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4x4 mRotationZ = glm::rotate(mRotationY, m_pParticles[index].m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4x4 mWorld = glm::translate(glm::mat4(1.0f), m_pParticles[index].m_vPosition) * mRotationZ;
        
        mWorld = pCamera->Get_BillboardMatrix(m_pParticles[index].m_vPosition);
                
        glm::vec4 vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
       
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        /*pColorData[index * 4 + 0] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 1] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 2] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 3] = m_pParticles[index].m_vColor;*/
    }
    m_pMesh->Get_VertexBufferRef()->Commit();
}

void CParticleEmitter::Render(CShader::E_RENDER_MODE _eMode)
{
    INode::Render(_eMode);
    
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
            m_pShaders[_eMode]->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            
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
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
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
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    m_pShaders[_eMode]->Disable();
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
}



