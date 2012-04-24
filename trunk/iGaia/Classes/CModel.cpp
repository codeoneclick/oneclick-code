
//  CModel.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CModel::CModel()
{
    
}

CModel::~CModel()
{
    
}

void CModel::Load(IResource::SResource _tResource)
{
    if(_tResource.m_eModel != IResource::E_STANDART_MODEL_NONE)
    {
        m_pMesh = CMeshComposite::Instance()->Get_Mesh(_tResource.m_eModel);
    }
    else
    {
        m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_tResource.m_sName, IResource::E_MGR_MESH, _tResource.m_eThread, this));
    }
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
    
    m_pShaderScreenNormalMap = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pShaderShadowMap = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_SHADOW_MAP);
}

void CModel::OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource)
{
    switch (_eType)
    {
        case IResourceLoaderDelegate::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<pResource->Get_Name()<<"\n";
            m_pMesh = static_cast<CMesh*>(pResource);
            m_pMesh->Get_VertexBufferRef()->CommitToRAM();
            m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
            m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
            break;
        case IResourceLoaderDelegate::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CModel::OnTouchEvent(void)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pBoundingBox->Get_Mesh()->Get_VertexBufferRef(), m_pBoundingBox->Get_Mesh()->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CModel::OnTouchEven] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    for(size_t index = 0; index < m_lDelegates.size(); index++)
    {
        m_lDelegates[index]->OnTouchEvent(m_pDelegateTarget);
    }
}

void CModel::OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale)
{
    if(m_pDelegateTarget != NULL)
    {
        m_pDelegateTarget->OnPhysicEvent(this, _vPosition, _vRotation, _vScale);
    }
}

void CModel::Update()
{
    INode::Update();
}

void CModel::Render(E_RENDER_MODE _eMode)
{     
    glCullFace(GL_BACK);
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
            m_pShader->SetVector2(m_vTexCoordOffset, CShader::k_TEXCOORD_OFFSET);
            
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
        case INode::E_RENDER_MODE_SHADOW_MAP:
        {           
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderShadowMap->Get_ProgramHandle());
            m_pShaderShadowMap->Enable();
            m_pShaderShadowMap->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaderShadowMap->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaderShadowMap->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
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
    glCullFace(GL_FRONT);
    
    if(m_pBoundingBox != NULL && INode::E_RENDER_MODE_SIMPLE == _eMode)
    {
        m_pBoundingBox->Render();
    }

}

