//
//  CParticleEmitter.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleEmitter.h"
#include "CSceneMgr.h"

CParticleEmitter::CParticleEmitter(void)
{
    m_iNumParticles = 64;
}

CParticleEmitter::~CParticleEmitter(void)
{
    
}

void CParticleEmitter::Load(IResource::SResource _tResource)
{
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = m_iNumParticles * 4;
    pSource->m_iNumIndexes  = m_iNumParticles * 6;
    
    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIndexBuffer->Get_Data();
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    glm::vec3*   pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2*   pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    glm::u8vec4* pColorData = pSource->m_pVertexBuffer->CreateOrReUse_ColorData();
    
    m_pParticles = new SParticle[m_iNumParticles];
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        m_pParticles[index].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vColor = glm::u8vec4(0, 0, 0, 0);
        m_pParticles[index].m_fTime = 0.0f;
        m_pParticles[index].m_vSize = glm::vec2(0.1f, 0.1f);
        
        pPositionData[index * 4 + 0] = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pPositionData[index * 4 + 1] = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        pPositionData[index * 4 + 2] = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        pPositionData[index * 4 + 3] = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);
        
        pTexCoordData[index * 4 + 0] = glm::vec2( 0.0f,  0.0f);
        pTexCoordData[index * 4 + 1] = glm::vec2( 1.0f,  0.0f);
        pTexCoordData[index * 4 + 2] = glm::vec2( 1.0f,  1.0f);
        pTexCoordData[index * 4 + 3] = glm::vec2( 0.0f,  1.0f);
        
        pColorData[index * 4 + 0] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 1] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 2] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 3] = m_pParticles[index].m_vColor;
    }
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        pIBData[index * 6 + 0] = static_cast<unsigned short>(index * 4 + 0);
        pIBData[index * 6 + 1] = static_cast<unsigned short>(index * 4 + 1);
        pIBData[index * 6 + 2] = static_cast<unsigned short>(index * 4 + 2);
        
        pIBData[index * 6 + 3] = static_cast<unsigned short>(index * 4 + 0);
        pIBData[index * 6 + 4] = static_cast<unsigned short>(index * 4 + 2);
        pIBData[index * 6 + 5] = static_cast<unsigned short>(index * 4 + 3);
    }
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
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
    m_pShaderScreenNormalMap = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
}

float CParticleEmitter::_Get_RandomFromRange(float _fMin, float _fMax)
{
    float fRange = _fMax - _fMin;
    return _fMin + float(fRange * rand() / (RAND_MAX + 1.0f)); 
}

void CParticleEmitter::Set_Shader(IResource::E_SHADER _eShader)
{
    m_pShader = CShaderComposite::Instance()->Get_Shader(_eShader);
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
    }
}

void CParticleEmitter::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
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

void CParticleEmitter::OnTouchEvent(void)
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
    
    glm::vec3* pPositionData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    glm::u8vec4* pColorData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_ColorData();
    
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
        pPositionData[index * 4 + 0] = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
       
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pPositionData[index * 4 + 1] = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pPositionData[index * 4 + 2] = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pPositionData[index * 4 + 3] = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        pColorData[index * 4 + 0] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 1] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 2] = m_pParticles[index].m_vColor;
        pColorData[index * 4 + 3] = m_pParticles[index].m_vColor;
    }
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
}

void CParticleEmitter::Render(E_RENDER_MODE _eMode)
{
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
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
        case INode::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderScreenNormalMap->Get_ProgramHandle());
            m_pShaderScreenNormalMap->Enable();
            m_pShaderScreenNormalMap->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaderScreenNormalMap->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaderScreenNormalMap->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
}



